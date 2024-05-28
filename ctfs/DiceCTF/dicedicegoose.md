游戏题目都逃不过F12的命运，直接F12分析源码

```js
 function win(history) {
    const code = encode(history) + ";" + prompt("Name?");

    const saveURL = location.origin + "?code=" + code;
    displaywrapper.classList.remove("hidden");

    const score = history.length;

    display.children[1].innerHTML = "Your score was: <b>" + score + "</b>";
    display.children[2].href =
      "https://twitter.com/intent/tweet?text=" +
      encodeURIComponent(
        "Can you beat my score of " + score + " in Dice Dice Goose?",
      ) +
      "&url=" +
      encodeURIComponent(saveURL);

    if (score === 9) log("flag: dice{pr0_duck_gam3r_" + encode(history) + "}");
  }
```

然后发现要求score等于9的时候会给flag，然后开始思考如何构造一个score=9的history，然后发现直上直下是可以的。

var myVariable = [
    [
        [0, 1],
        [9, 9]
    ],
    [
        [1, 1],
        [9, 8]
    ]
    [
        [2, 1],
        [9, 7]
    ]
    [
        [3, 1],
        [9, 6]
    ]
    [
        [4, 1],
        [9, 5]
    ]
    [
        [5, 1],
        [9, 4]
    ]
    [
        [6, 1],
        [9, 3]
    ]
    [
        [7, 1],
        [9, 2]
    ]
    [
        [8, 1],
        [9, 1]
    ]
];

即可获取flag