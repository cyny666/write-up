是一个RAR文件，用WinRAR文件解压的时候显示secret.png解压头格式错误

然后查找相关文献

![image-20230927112920293](./assets/image-20230927112920293.png)

后面应该是一个文件块74而不是一个字块，手动修改为74然后解压，用ps分层加stegsolve解密即可获得二维码