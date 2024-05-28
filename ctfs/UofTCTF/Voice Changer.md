总感觉自己太浮躁了，没有仔细的审web就直接去看wp了，什么眼高手低

又是一道command injection的题目，什么哈工大遗题，

先看返回包

![image-20240209120308531](C:/Users/86186/AppData/Roaming/Typora/typora-user-images/image-20240209120308531.png)

这里采用了命令拼接的方法，然后即可用${whoami}来代替pitch

即可用命令替代的方式来获取最终flag