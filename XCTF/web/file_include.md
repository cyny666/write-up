发现文件包含漏洞，然后用dirsearch直接扫到发现该目录下有flag.php目标文件，于是目标就一直放在如何读取这个文件下：

尝试普通的filename=php://filter/resource发现没有返回值 这时选取了默认的过滤器，会将敏感信息过滤

然后修改过滤器的种类发现成功读取http://61.147.171.105:51570/?filename=php://filter/convert.iconv.utf8.utf16/resource=flag.php