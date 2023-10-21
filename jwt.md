JWT的全称是JSON Web Token。遵循JSON格式，跨域认证解决方案。声明被存储在客户端，而不是服务器内存中。服务器不保存任何用户信息，只保存密钥信息，通过使用特定加密算法验证token，通过token验证用户身份。基于token的身份验证可以替代传统的cookie+session身份验证方法

jwt由三部分组成：header、payload、signature

### header

header部分最常用的两个字段是alg和typ，alg指定了token加密使用的算法（最常用的为HMAC'和RSA算法），typ声明类型为JWT

### payload

payload则为用户数据以及一些元数据有关的声明，用以声明权限。

### signature

signature的功能是保护token完整性；生成方式是将header和payload两个部分链接，然后通过header部分指定的算法，计算签名

抽象成公式就是

```
signature = HMAC-SHA256(base64urlEncode(header) + '.' + base64urlEncode(payload), secret_key
```

`注意：`编码header和payload时使用的编码方式为`base64urlencode`，`base64url`编码是`base64`的修改版，为了方便在网络中传输使用了不同的编码表，它不会在末尾填充”=”号，并将标准Base64中的”+”和”/“分别改成了”-“和”-“。

JWT中最常用的两种算法为HMAC和RSA

HMAC是密钥相关的哈希运算消息认证码的缩写，它是一种对称加密算法，使用相同的密钥对传输信息进行加解密

RSA则是一种非对称加密算法，使用私钥加密明文，公钥解密密文。

