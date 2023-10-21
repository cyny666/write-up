来到注册界面发现需要输入那个invite code 原本想爆破（也可能有点慢），后来发现可以抓包修改判定

抓到的包如下

```php
POST /register HTTP/1.1
Host: 61.147.171.105:51369
Content-Length: 56
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.5845.111 Safari/537.36
Content-Type: text/plain;charset=UTF-8
Accept: */*
Origin: http://61.147.171.105:51369
Referer: http://61.147.171.105:51369/register.html
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Connection: close

{"username":"admin","password":"123456","isAdmin":false}
```

然后了解到JavaScript的原型链污染

大概就是如下

```javascript
var a = {number : 520}
var b = {number : 1314}
b.__proto__.number=520 
var c= {}
c.number
```

我们这里调用`b.number`时，它的具体调用过程是如下所示的

```javascript
1、在b对象中寻找number属性
2、当在b对象中没有找到时，它会在b.__proto__中寻找number属性
3、如果仍未找到，此时会去b.__proto__.__proto__中寻找number属性
```

复制

也就是说，它从自身开始寻找，然后一层一层向上递归寻找，直到找到或是递归到`null`为止，此机制被称为`JavaScript继承链`，我们这里的污染的属性是在`b.__proto__`中，而我们的`b`对象本身就有`number`，所以其值并未改变。

> ​         二、为什么新建的值为空的c对象，调用`c.number`竟然有值而且为我们设定的520

当明白上个问题时，这个问题也就迎刃而解了，我们这里的`c`对象虽然是空的，但`JavaScript继承链`的机制就会使它继续递归寻找，此时也就来到了`c.__proto__`中寻找`number`属性，我们刚刚进行了原型链污染，它的`c.__proto__`其实就是`Object.protoype`，而我们进行污染的`b.__proto__`也是`Object.prototype`，所以此时它调用的`number`就是我们刚刚污染的属性，所以这也就是为什么`c .number=520`