源码审计题目

源码如下

```js
const express = require("express");
const path = require("path");
const TAFFY = require("taffydb").taffy;
process.env.FLAG = 'flag{test}';
const db = TAFFY([
    {"username": "admin", "comments": process.env.FLAG},
    {"username": "randomuser", "comments": "This is a test comment"},
]);
console.log(db().get())


const app = express();
app.use(express.json());

app.get("/", (req, res) => {
    res.sendFile(path.join(__dirname, "/index.html"));

});

app.post("/addData", (req, res) => {
    const { data, username } = req.body;
    // validation
    if (!username || typeof username !== "string" || username == "admin") {
        return res.status(400).send("Invalid username!");
    }

    if (!data || typeof data !== "object" || Array.isArray(data)) {
        return res.status(400).send("Invalid data!");
    }

    for (const key in data) {
        if (typeof data[key] !== "string") {
            return res.status(400).send("Invalid data!");
        }
    }

    // set username to data
    data["username"] = username;

    db.insert(data);
    res.status(200).send("Data added successfully!");
});

app.post("/getData", (req, res) => {
    const { username, filters } = req.body;

    // validation
    if (!username || typeof username !== "string" || username == "admin") {
        return res.status(403).send("Invalid username!");
    }

    if (!filters || typeof filters !== "object" || Array.isArray(filters)) {
        return res.status(400).send("Invalid filters!");
    }

    for (const key in filters) {
        if (typeof filters[key] !== "string") {
            return res.status(400).send("Invalid data!");
        }
    }

    // add username to filters
    filters["username"] = username;

    const data = db(filters).get();
    res.status(200).send(JSON.stringify(data));
});


app.listen(3000, () => {
    console.log("Server is running on port 3000");
});

```

本身各种逻辑没有问题，只能去找其他问题了，发现了返回渲染时候的xss，但是xss并不可以窃取process.env.FLAG，所以应该思考其他办法

源码中有一个新奇的库为taffydb

然后google搜索taffydb的漏洞发现第一个

https://security.snyk.io/vuln/SNYK-JS-TAFFY-546521

然后发现就是filter的条件可以部分满足

于是直接构造exp，可以本地运行获取id

![image-20240508003000643](C:/Users/86186/Desktop/write-up/ctfs/squ1rrelCTF/assets/image-20240508003000643.png)