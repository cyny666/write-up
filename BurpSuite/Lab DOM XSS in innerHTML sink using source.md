#### DOM型

- CTF比赛中出现的场景：动态执行JavaScript语句，更改dom树结构

This lab contains a [DOM-based cross-site scripting](https://portswigger.net/web-security/cross-site-scripting/dom-based) vulnerability in the search blog functionality. It uses an `innerHTML` assignment, which changes the HTML contents of a `div` element, using data from `location.search`.

To solve this lab, perform a [cross-site scripting](https://portswigger.net/web-security/cross-site-scripting) attack that calls the `alert` function.

构造这个即可

```html
<img src=1 onerror=alert(1)>
```



不得不说一分题目还是挺简单的，下次做就熟悉了