唯一做出来的web题（为了做出这道题甚至自学了seleuinm，但是输在自己最喜欢的jwt了:sob:）

第一问直接无脑穷举：

```python
# coding: utf-8
import requests
import re
emojs = [
    '💃','👼','🐐','🐟','💏','👣','🐧','👀','💃','🐥','🐯','💈','🐳','🐬','🐛','👬','🐲','🐩','🐪','🐗','👟','👕','🐙','👻','👀','💍','👋','💋','👣','👝','👦','🐲','🐭','👦','👬','🐝','💁','💄','👇','🐴','🐝','👫','🐒','🐧','🐩','👎','👇','🐴','👎','👽','🐻','👎','💈','👜','👄','👟','👻','🐞','🐿','💅','💊','👼','💀','👊',
    '👙','👔','🐳','👯','💈','👘','💇','🐢','👓','🐜','👌','👦','🐙','🐹','🐙',
    '👲','👨','🐮','🐕','👲','💄','🐵','👒','👥','🐖','🐲','🐷','🐿','🐸','👜','👔','🐵','👛','💄','👇','🐫','💀','🐙','👆', '🐻', '🐦', '👞', '🐤', '👋', '👫', '👙', '👇', '💁', '🐸', '👟', '💈', '🐩', '🐗', '👐', '👰', '🐴', '👕', '🐗', '🐙', '👸', '🐢', '🐴', '🐨', '💎', '👙', '👒', '👹', '👵', '👅', '👁', '👬', '💉', '🐬', '👵', '🐶', '👅', '🐿', '👰', '👋', '🐯', '🐝', '👿', '💅', '🐔', '🐪', '👠', '👞', '👓', '🐲', '👼', '🐧', '👠', '👠', '👾', '👊', '👣', '👽', '👕', '👋', '🐴', '🐫', '🐲', '👋',
    '👰', '👞', '🐽', '👳', '🐹', '👓', '🐓', '👂', '👐', '👳', '👣', '🐲', '🐪', '👥', '👣', '💅', '👧', '👞', '🐞', '🐒', '🐖', '👓', '👛', '🐥', '🐳', '👘', '👜', '👼', '🐮', '💉', '👟', '🐣', '👸', '🐛', '👉', '👝', '👃', '👸', '🐴', '👗', '💃', '💆', '🐙', '👱', '👯', '👣', '👚'
    '🐰', '🐼', '👕', '👈', '🐰', '💋', '🐛', '🐕', '🐺', '👆', '👽', '🐪', '👗', '👲', '👔', '🐵', '💇', '🐓', '💅', '🐒', '🐾', '🐩', '💀', '👽',
    '👣', '👐', '🐮', '🐛', '🐻', '🐤', '🐡', '👌', '👠', '🐲', '🐵', '👠', '🐛', '💎', '💂', '💎', '🐭', '👏', '👁', '👓', '🐛', '👖', '👢', '🐺',
    '💉', '🐔', '🐓', '👤', '👫', '🐛', '🐗', '👍', '👯', '🐽', '👥', '👤', '👑', '👅', '👸', '👌', '👊', '👚', '👠', '🐫', '🐘', '👒', '👄', '💆',
    '👽', '🐱', '🐵', '👵', '👧', '🐠', '👺', '🐾', '👭', '👫', '👎', '🐦', '💍', '🐲', '🐚', '👪', '🐧', '👪', '👬', '👣', '💎', '👘', '🐬', '👾',
    '🐑', '👫', '👫', '👓', '🐴', '👦', '👊', '👂', '🐘', '💋', '👮', '👖', '👙', '👛', '👟', '👊', '👁', '💁', '🐬', '🐺', '👯', '🐪', '👘', '👢',
    '🐞', '👣', '🐝', '🐦', '👍', '👓', '👢', '🐺', '💆', '🐨', '👡', '💇', '🐤', '👼', '🐨', '👬', '🐯', '🐚', '🐣', '🐞', '🐞', '👤', '👇', '👐',
    '🐿', '👶', '💂', '💌', '🐛', '👫', '🐬', '👶', '👶', '🐼', '💏', '👄', '👓', '🐵', '👴', '👢', '💉', '🐱', '👩', '👀', '👻', '🐣', '🐮', '👈',
    '🐺', '👤', '🐜', '🐵', '🐽', '🐔', '🐗', '👭', '🐲', '🐼', '🐞', '👆', '👢', '👴', '👱', '👹', '👓', '💄', '💃', '👈', '🐻', '👦', '👦', '👰',
 '   🐺', '🐯', '👣', '🐦', '👴', '💇', '💊', '👜', '🐾', '👸',]
emojs = list(set(emojs))
obj = '💈💅👼💁👦👗💊💊👱👇👔💆'
for i in range(13,65):
    for emoj in emojs:
        url = 'http://prob14.geekgame.pku.edu.cn/level2?guess=' + obj + emoj
        headers = {
            'Host': 'prob14.geekgame.pku.edu.cn',
            'Upgrade-Insecure-Requests': '1',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.5938.132 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7',
            'Accept-Encoding': 'gzip, deflate, br',
            'Accept-Language': 'zh-CN,zh;q=0.9',
            'Cookie': 'PLAY_SESSION=eyJhbGciOiJIUzI1NiJ9.eyJkYXRhIjp7ImxldmVsIjoiMiIsInJlbWFpbmluZ19ndWVzc2VzIjoiNiIsInRhcmdldCI6Ilx1RDgzRFx1REM3Qlx1RDgzRFx1REM4Nlx1RDgzRFx1REM2MFx1RDgzRFx1REM2OVx1RDgzRFx1REM3Q1x1RDgzRFx1REM0Nlx1RDgzRFx1REM3RVx1RDgzRFx1REM4QVx1RDgzRFx1REM0OFx1RDgzRFx1REM1NFx1RDgzRFx1REM4MFx1RDgzRFx1REM2Mlx1RDgzRFx1REM2Mlx1RDgzRFx1REM3NVx1RDgzRFx1REM3Nlx1RDgzRFx1REM1NFx1RDgzRFx1REM2OVx1RDgzRFx1REM4Nlx1RDgzRFx1REM0Nlx1RDgzRFx1REM1M1x1RDgzRFx1REM3Rlx1RDgzRFx1REM4OFx1RDgzRFx1REMzRlx1RDgzRFx1REM1Rlx1RDgzRFx1REM0N1x1RDgzRFx1REM0NFx1RDgzRFx1REM1MVx1RDgzRFx1REM1M1x1RDgzRFx1REM1Nlx1RDgzRFx1REM3M1x1RDgzRFx1REM2N1x1RDgzRFx1REM2Mlx1RDgzRFx1REM1NFx1RDgzRFx1REM1OFx1RDgzRFx1REM1QVx1RDgzRFx1REM3RFx1RDgzRFx1REM3NVx1RDgzRFx1REM4NFx1RDgzRFx1REM4M1x1RDgzRFx1REM4OFx1RDgzRFx1REM0OFx1RDgzRFx1REM0MVx1RDgzRFx1REM4OVx1RDgzRFx1REM0M1x1RDgzRFx1REM3QVx1RDgzRFx1REM3OFx1RDgzRFx1REM1NFx1RDgzRFx1REM1Q1x1RDgzRFx1REM0NFx1RDgzRFx1REM3M1x1RDgzRFx1REM1Q1x1RDgzRFx1REM4MFx1RDgzRFx1REM1MVx1RDgzRFx1REM3NFx1RDgzRFx1REM0MVx1RDgzRFx1REM3Mlx1RDgzRFx1REM0NFx1RDgzRFx1REM3Qlx1RDgzRFx1REM3OFx1RDgzRFx1REM4Nlx1RDgzRFx1REM3QVx1RDgzRFx1REM1Qlx1RDgzRFx1REM1Nlx1RDgzRFx1REM0OSJ9LCJuYmYiOjE2OTc0NDg3NzgsImlhdCI6MTY5NzQ0ODc3OH0.djbGgovDYyaB54BV3UjkaxiURS2yPzRPna2nonBII_Q',
            'Connection': 'close'
        }
        response = requests.get(url, headers=headers)
        lines = response.text.split('\n')
        content = lines[18]
        count = content.count('🟩')
        if count == i:
            obj += emoj
            print(url)
            break
    print('第',i,'个字符结束')

```

然后第二问发现其只需要8次，理论上这种游戏是做不出来答案的，于是分析session（jwt）

解密后如下

```json
{
  "data": {
    "level": "2",
    "remaining_guesses": "8",
    "target": "💈👑👑👱👴👘👸👇👲👂👅👿👆👅💆👧👡👜👅👥👪👾💀👡👷💃👨💇👥👈👂👺💈👲💃👵💈👓💄👒💅👅💆💆👝💇💇👾👲💊👦👷👽👸👑👱👢👡👕👇👅👷👦👦"
  },
  "nbf": 1698199847,
  "iat": 1698199847
}
```

把这个提交即可获得答案

第三问主要是复用cookie然后求解（妈的感觉都不是常规游戏方法做出来、看看隔壁扫雷）