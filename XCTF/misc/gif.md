将图片转化为二进制  白代表0 黑代表1

面向chatgpt编程

```python
from PIL import Image
import os
flag = ''
# 文件夹路径
folder_path = "C://Users//86186//Desktop//ctf//misc//dbbc971bf4da461fb8939ed8fc9c4c9d//gif"

# 自定义排序函数
def get_numeric_part(filename):
    # 提取文件名中的数字部分
    numeric_part = ''.join(filter(str.isdigit, filename))
    return int(numeric_part) if numeric_part else -1

# 遍历文件夹中的图片，并按数字顺序排序
for filename in sorted(os.listdir(folder_path), key=get_numeric_part):
    if filename.endswith(".jpg") or filename.endswith(".png") or filename.endswith(".jpeg"):
        # 图片路径
        image_path = os.path.join(folder_path, filename)

        # 打开图片
        image = Image.open(image_path)

        # 获取图片的RGB值
        rgb_values = image.getpixel((0, 0))  # 这里获取左上角像素的RGB值，可以根据需要修改
        if rgb_values[2] == 255:
            flag += '0'
        else:
            flag += '1'
binary_string = flag
# 将二进制字符串分割成8位一组
binary_list = [binary_string[i:i+8] for i in range(0, len(binary_string), 8)]

# 将每个8位二进制字符串转换为整数，并再转换为对应的ASCII字符
ascii_string = ''.join(chr(int(binary, 2)) for binary in binary_list)

print(ascii_string)
```