很有意思的一道github信息泄露题，原来这就是cloud的含金量

github中完全的删除一个敏感数据是很难的可以看这个

https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/removing-sensitive-data-from-a-repository

关键在这个？：: This article tells you how to make commits with sensitive data unreachable from any branches or tags in your repository on GitHub.com. However, those commits may still be accessible in any clones or forks of your repository, directly via their SHA-1 hashes in cached views on GitHub,

然后从activity可以查看到每个用户的commit，于是可以查看到关键信息

也可以用git-secret查看信息即可获取flag