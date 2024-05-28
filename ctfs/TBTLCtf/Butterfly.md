怎么感觉自己最近被打击的手都软了hhh还是要硬一点，菜就菜咯，慢慢弥补回去

先打开网页发现js里面有混淆后的js代码

把混淆后的js丢进在线解混淆的网站后发现有如下关键部分

```javascript
indexedDB.deleteDatabase("strangeStorage");
var request = indexedDB.open("strangeStorage", 1);
request.onupgradeneeded = function (event) {
    var db = event.target.result;
    var objectStore = {
        "keyPath": 'id',
        "autoIncrement": true
    };
    var flagStore = db.createObjectStore("FLAG", objectStore);
    var indexProps = {
        unique: false
    };
    flagStore.createIndex("letter", "letter", indexProps);
};
request.onsuccess = function (event) {
    var db = event.target.result;
    var transaction = db.transaction(["FLAG"], "readwrite");
    var objectStore = transaction.objectStore("FLAG");
    enc = ["UW=(X4 ... A`MK[v5itlMJw-h|G/='];
    for (const key in enc) {
        var character = enc[key][key].charCodeAt();
        var encodeCharCode = (character * character + 3 * character + 1 - (character + 1) * (character + 1)) * (2 * (key + 1) / (key + 1)) >> 1;
        objectStore.add({
            'letter': String.fromCharCode(encodeCharCode)
        });
    }
};
code = 'CryptoJS.AES.decrypt(CIPHERTEXT, KEY).toString(CryptoJS.enc.Utf8)';
var _0x1b9dd8 = {
    "code": code
};
localStorage.setItem("execute", JSON.stringify(_0x1b9dd8));
sessionStorage.setItem("KEY", atob("c2VjcmV0IGtleSBpcyB2ZXJ5IHNlY3VyZQ=="));

```

然后逆向解码即可获取flag

学会了commonjs的导入js库

exp.js如下

```javascript
const CryptoJS = require('crypto-js');
flag = ""
enc = ["UW=(X4s}@(BFLzW1(2}vGpzzgQNy;&L4H??)(5Q+40sB|^/s2 ... J2AdBFnA`MK[v5itlMJw-h|G/='];
for (const key in enc) {
    var character = enc[key][key].charCodeAt();
    var encodeCharCode = (character * character + 3 * character + 1 - (character + 1) * (character + 1)) * (2 * (key + 1) / (key + 1)) >> 1;
    flag += String.fromCharCode(encodeCharCode);
}
key = atob("c2VjcmV0IGtleSBpcyB2ZXJ5IHNlY3VyZQ==");
var decrypted = CryptoJS.AES.decrypt(flag, key).toString(CryptoJS.enc.Utf8);
console.log(decrypted);
```

