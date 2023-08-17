介绍一下Robots协议吧：

Robots协议，也称为爬虫协议、机器人协议等，其全称为“网络爬虫排除标准（Robots Exclusion Protocol）”。网站通过Robots协议告诉搜索引擎哪些页面可以抓取，哪些页面不能抓取。也既是Robots的用法有两种，一种是告诉搜索引擎哪些页面你不能抓（默认其他的就可以抓）；一种是告诉搜索引擎你只能抓取哪些页面（默认其他的不可以抓）。

User-agent:*

*是一个通配符，表示所有的搜索引擎种类

Disallow:/admin/

这表示禁止搜索引擎爬寻admin目录下的内容

Disallow:*?*

这表示禁止搜索引擎爬寻包含?的网页

Sitemap:sitemap.xml

这里通过Sitemap指定固定的网站地图页面。目前对此表示支持的搜索引擎公司有Google, Yahoo, Ask and MSN。而中文搜索引擎公司，显然不在这个圈子内。这样做的好处就是，站长不用到每个搜索引擎的站长工具或者相似的站长部分，去提交自己的sitemap文件，搜索引擎的蜘蛛自己就会抓取robots.txt文件，读取其中的sitemap路径，接着抓取其中相链接的网页。