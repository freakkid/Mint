* S1
    + 在点击获得随机数并计算出结果之后，鼠标不离开buttn，可以继续点击单个蓝色按钮获得新随机数，继续进行新计算
* S2
    + 机器人点击时不允许用户点击

    + 机器人点击时，用户可以点击@让机器人重新开始点击
    
    + 显示计算结果后，可以继续点击单个蓝色按钮获得新随机数，继续进行新计算，也可以点击中间的@进行机器人点击

* S3
    + 同上

* S4
    + 同上

* S5
    + 气泡上方的message显示的是正在请求随机数的那个按扭的message

    + 随机失败用
    ```
    Math.round(Math.random())
    ```
    获得随机数0或1，从而判断是否失败，随机失败的概率大约为0.5
    
    + 若随机失败，则“message为原定message的否定形式”，五句话的否定形式如下（如果我没理解错题意的话qaq）：
    ```
    A：这不是个天大的秘密+currentSum
    B：我知道+currentSum
    C：你知道+currentSum
    D：他知道+currentSum
    E：才不怪+currentSum
    大气泡：楼主异步调用战斗力不感人，目测不超过+currentSum
    ```

    + 是在请求随机数之前随机失败，因此随机失败返回的currentSum是加上随机数之前的值

* S2-S5采用callback，S5使用了ta发在群上的$.Deferred()方法catch错误

* S5代码有点冗余但我想不到什么好办法精简了qaq

* At last, thanks for reviewing!