感觉距离大佬的路还是很远，这里主要是使用了python的[pyshark](https://github.com/KimiNewt/pyshark)模块来分析流量包

然后提取value值就可以了

```python
import pyshark,re
cap = pyshark.FileCapture('sqlshark.pcap',display_filter='http')
last_packet = None
last_text = ''
result = {}
def extract(text):
    a = re.search(r'Value.*frOm (\d*).*in\((\d*)\).*#', text)
    key,value = a.group(1),a.group(2)
    result[key] = value
    print(key,value)
for packet in cap:
    text = str(packet.layers[-1:][0])
    if 'success' in text and last_packet is not None:
        extract(last_text)
    last_packet = packet
    last_text = text
for c in result:
    print(chr(int(result[c])),end='')
```