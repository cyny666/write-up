```python
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator

# 打开文件并读取数据
with open('C:/Users/86186/Desktop/c280d387-a16e-427b-a53f-ed5c9636420b/CatchCat.txt', 'r') as file:
    lines = file.readlines()

# 提取纬度和经度
latitudes = []
longitudes = []

for line in lines:
    if line.startswith('$GPGGA'):
        parts = line.split(',')
        lat = float(parts[2]) if parts[3] == 'N' else -float(parts[2])
        lon = float(parts[4]) if parts[5] == 'E' else -float(parts[4])
        latitudes.append(lat)
        longitudes.append(lon)

# 绘制散点图
plt.figure(figsize=(6, 10))  # 宽度为6英寸，高度为8英寸
plt.scatter(longitudes, latitudes)

x_major_locator = MultipleLocator(0.004)
# 把x轴的刻度间隔设置为0.1
y_major_locator = MultipleLocator(1)
# 把y轴的刻度间隔设置为0.05

ax = plt.gca()
# ax为两条坐标轴的实例
ax.xaxis.set_major_locator(x_major_locator)
# 把x轴的主刻度设置为0.1的倍数
ax.yaxis.set_major_locator(y_major_locator)
# 把y轴的主刻度设置为0.05的倍数

plt.xlim(10856.5, 10857)
# 把x轴的刻度范围设置为0到1
plt.ylim(3415.9, 3416.55)
# 把y轴的刻度范围设置为0到0.7

plt.show()
```

对于画图有了新的理解