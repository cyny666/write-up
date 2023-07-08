只能说，看错了顺序的笨蛋

```python
import base64
import codecs

miwen = 'a1zLbgQsCESEIqRLwuQAyMwLyq2L5VwBxqGA3RQAyumZ0tmMvSGM2ZwB4tws'
flag1 = codecs.decode(miwen, 'rot13')
reversed_str = flag1[::-1]
flag2 = base64.b64decode(reversed_str)
flag3 = flag2.decode('utf-8')
flag4 = ''
for s in flag3:
    ascii_value = ord(s)
    new_ascii_value = ascii_value - 1
    flag4 += chr(new_ascii_value)
true_flag = flag4[::-1]
print(true_flag)
```

