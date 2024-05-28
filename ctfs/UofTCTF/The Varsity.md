感觉这种题在现实生活中会比较常见，感觉很容易被疏忽

为什么自己试了1' or 1=1 --+就可以正确后没想过9 ' or 1=1 --+ 

主要是一个逻辑漏洞

```js
if (req.body.issue < 0) {
        return res.status(400).json({ message: "Invalid issue number" });
      }

      if (decoded.subscription !== "premium" && issue >= 9) {
        return res
          .status(403)
          .json({ message: "Please subscribe to access this issue" });
      }

      issue = parseInt(issue);

      if (Number.isNaN(issue) || issue > articles.length - 1) {
        return res.status(400).json({ message: "Invalid issue number" });
      }

```

这里对于req.issue进行查找

然后是先判断Issue是否大于9，然后再用parseInt解析

而parseInt解析是可以解析特殊字符的，所以可以构造

9 ' or 1=1 --+

即可获取

这题的混淆项就是一直再考虑jwt怎么绕过这些问题

