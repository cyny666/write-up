很有意思的一道题

先看js源码

```js
const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  if (req.method == "GET") return res.send("Bad!");
  res.cookie('flag', process.env.FLAG ?? "flag{fake_flag}")
  res.send('Winner!')
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})

```

主要是app.get()和req.method=="GET"的绕过，误打误撞试了一下所有的method然后获得了flag

正确的解法：

先用Option试一下可以的method

发现返回了GET、HEAD，

而[HEAD](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/HEAD) *method is identical to* [GET](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/GET) *method, but the server does not return a message-body in the response.*
*This can be used to obtain meta-information about the entity implied by the request without transferring the entity-body itself.*
*Express automatically maps the* `HEAD` *method to the* `.get()` *method.*

express会自动把HEAD转化为GET，所以实现了绕过

其实想到method的漏洞点了但是没有想通透