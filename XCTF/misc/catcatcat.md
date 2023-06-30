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