* 所有需要的包, 已经整理到pkg文件夹下, pkg文件夹下包括以下文件:

  * extract_changed
  * extract_modified
  * helper
  * preprocess
  * run
  * submission
  * vectorizer

* 全部是.py文件

* 请看清楚名字, 引用方法如下：

  ```
  在存放pkg文件夹的目录下（不要进入pkg文件夹）,在test文件中加入:
  from pkg.module import function
  或者直接用
  import pkg.module
  当然,这样引用的话,在test文件中使用方法有区别.
  ```

  ​