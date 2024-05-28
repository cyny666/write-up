很有意思的一道js题目

```js
const users = [...Array(100_000)].map(() => ({ user: `user-${crypto.randomUUID()}`, pass: crypto.randomBytes(8).toString("hex") }));
db.exec(`INSERT INTO users (id, username, password) VALUES ${users.map((u,i) => `(${i}, '${u.user}', '${u.pass}')`).join(", ")}`);

const isAdmin = {};
const newAdmin = users[Math.floor(Math.random() * users.length)];
isAdmin[newAdmin.user] = true;

app.use(express.urlencoded({ extended: false }));
app.use(express.static("public"));

app.post("/api/login", (req, res) => {
    const { user, pass } = req.body;

    const query = `SELECT id FROM users WHERE username = '${user}' AND password = '${pass}';`;
    try {
        const id = db.prepare(query).get()?.id;
        if (!id) {
            return res.redirect("/?message=Incorrect username or password");
        }

        if (users[id] && isAdmin[user]) {
            return res.redirect("/?flag=" + encodeURIComponent(FLAG));
        }
        return res.redirect("/?message=This system is currently only available to admins...");
    }
    catch {
        return res.redirect("/?message=Nice try...");
    }
});
```

看到是拼接sql语句于是可以构造1' or 1=1 #

注意这里后面的or 1=1 要改成id=1主要是为了防止筛选出多个id然后报错

然后即可想办法满足这个 isAdmin[user]

这里用JavaScript的原型链污染，

isAdmin. 

isAdmin.\_\_proto\__             isAdmin.constructor           isAdmin.hasOwnProperty        isAdmin.isPrototypeOf         isAdmin.propertyIsEnumerable   isAdmin.toLocaleString        isAdmin.toString              isAdmin.valueOf

然后即可输入isAdmin.\_\_proto\__来实现isAdmin[user]=true

这里纠正一下这几种写法都是相同的(表示python的字典写少了)：

```
Foo.prototype
foo["__proto__"]
foo.__proto__
foo.constructor.prototype
```

然后即可构造成功

