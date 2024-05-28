---
title: easy_tables
date: 2023-12-21 15:52:25
categories:
  - WriteUp
tags:
  - Misc
---

比较懒直接放exp吧

照着别人的wp手敲一份感觉对于python的理解都变深了好多，感觉比重新构建一个数据库简单的多

```python
import csv
import time
# 分别打开四个csv文件
lists = ['users','permissions','tables','actionlog']
with open('users.csv', 'r', encoding="utf-8") as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    users = list_of_csv
with open('permissions.csv', 'r', encoding='utf-8') as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    permissions = list_of_csv
with open('tables.csv', 'r', encoding='utf-8') as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    tables = list_of_csv
with open('actionlog.csv', 'r', encoding='utf-8') as read_obj:
    csv_reader = csv.reader(read_obj)
    list_of_csv = list(csv_reader)
    actionlog = list_of_csv

name_ti = 0
per_ti = 0
flag = ''
for log in actionlog[1:]:
    log_id = log[0]
    log_name = log[1]
    log_time = log[2].split(' ')[1]
    log_opt = log[3]

    for users_A in users[1:]:
        users_id = users_A[0]
        users_name = users_A[1]
        users_per = users_A[3]
        if users_name == log_name:
            name_ti = 0

            for per_A in permissions[1:]:
                per_id = per_A[0]
                per_qx = per_A[2]
                per_table = per_A[3]

                if users_per == per_id:
                    log_opt_list = log_opt.split(' ')
                    per_table_list = per_table.split(',')
                    # 对每个表进行遍历
                    for tb in tables[1:]:
                        print(tb)
                        tb_id = tb[0]
                        tb_name = tb[1]
                        tb_time = tb[2].split(",")
                        #先找出操作的表
                        #且操作的表应该在可允许的表中
                        if tb_name in log_opt_list:
                            if tb_id in per_table_list:
                                if log_opt_list[0] in per_qx:
                                    try:
                                        tb_time_1 = tb_time[0].split('~')
                                        tb_time_2 = tb_time[1].split('~')
                                        if tb_time_1[0] < log_time < tb_time_1[1] or tb_time_2[0] < log_time < \
                                        tb_time_2[1]:
                                            pass
                                        else:
                                            print('编号:',log_id,"账户不在规定时间内操作",
                                                  users_id+'_'+per_id+'_'+tb_id+'_'+log_id)
                                            flag +=users_id+'_'+per_id+'_'+tb_id+'_'+log_id
                                    except:
                                        tb_time = tb_time[0].split("~")
                                        if tb_time[0] < log_time < tb_time[1]:
                                            pass
                                        else:
                                            print('编号:', log_id, '账户不在规定时间内操作操作',
                                                  users_id + '_' + per_id + '_' + tb_id + '_' + log_id)
                                            flag += users_id + '_' + per_id + '_' + tb_id + '_' + log_id + ','
                                else:
                                    print('编号:', log_id, '为对表执行不属于其权限的操作',
                                          users_id + '_' + per_id + '_' + tb_id + '_' + log_id)
                                    flag += users_id + '_' + per_id + '_' + tb_id + '_' + log_id + ','
                            else:
                                print('编号:', log_id, '为对不可操作的表执行操作',
                                      users_id + '_' + per_id + '_' + tb_id + '_' + log_id)
                                flag += users_id + '_' + per_id + '_' + tb_id + '_' + log_id + ','
                            break
                    break
            break
        else:
            name_ti += 1
        if name_ti == len(users[1:]):
            print('编号:', log_id, '为不存在用户操作', '0_0_0_' + log_id)
            flag += '0_0_0_' + log_id + ','
            name_ti = 0
flag = flag.split(',')
flag = sorted(flag)
flag = ','.join(str(fla) for fla in flag)
print(flag)
```



