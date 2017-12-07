
* S5
    + 气泡上方的message显示的是正在请求随机数的那个按扭的message

    + 随机失败用
    ```
    Math.round(Math.random())
    ```
    获得随机数0或1，从而判断是否失败，随机失败的概率大约为0.5
    
    + 若随机失败，则“message为原定message的否定形式”，五句话的否定形式如下（如果我没理解错题意的话qaq）：
    ```
    A：这不是个天大的秘密
    B：我知道
    C：你知道
    D：他知道
    E：才不怪
    大气泡：楼主异步调用战斗力不感人，目测不超过xxx
    ```


* At last, thanks for reviewing!