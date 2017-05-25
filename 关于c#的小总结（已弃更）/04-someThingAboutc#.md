# c#零碎笔记

1. 被迫升级了win10和强装了vs
2. 先零碎地学习C#的各种东西

---------

1.[字符串](https://msdn.microsoft.com/en-us/library/system.string(v=vs.110).aspx)
+ 字符串长度:s.Length 
+ String.IsNullOrEmpty(s)
+ String.Format("(\\"{0}\\") is neither null nor empty", s);
+ 字符串中某字符的第一个和最后一个的位置
    > int startIndex = s.IndexOf(charRange);

    > int endIndex = s.LastIndexOf(charRange);

+ 获取子字符串：
    > s.Substring(startIndex, length);
    > s.Substring(startIndex);

+ 字符串是否相同
    > s.Equals(s1);

+ String.Format("{0,-3}", i); // 格式
+ String.Join(sep, nums); // sep: 分隔的字符串；nums: 字符串数组

2.数字
+ 最大值最小值： Int32.MaxValue Int32.MinValue // System.Int32
+ Math.Pow()    // using System;
+ 数字的字符串表达
    >"{0} > {1:E}" // 指数形式

+ 数字转字符串 : num.ToString()  字符串转数字 : int.Parse(str_num)
+ [encoding](https://msdn.microsoft.com/en-us/library/ezftk57x(v=vs.110).aspx)



3.数组
+ using System.Linq;
+ 首元素 array.First()
+ >// 第一个满足条件的元素
   int firstLagerFive = numbers.First(number => number > 5);
+ 

4.ArrayList // using System.Collections
+ ArrayList list1 = new ArrayList();
    + list1.add(item);
    + list1[index] = x;     // 修改
    + list1.RemoveAt(0);    // 移除
    + list1.Insert(0, item);
+ ArrayList把所有插入其中的数据当作为object类型来处理;在存储或检索值类型时通常发生装箱和取消装箱操作，带来很大的性能耗损
    * 装箱：就是将值类型的数据打包到引用类型的实例中
        > object obj = (object)i;

    * 拆箱：就是从引用数据中提取值类型
        > string i = (string)obj;

5.List<T>
+ list.Skip(n); // 跳过n个元素再返回剩下的元素
    
5.异常
+ catch方法：

    >try{}
    
    >catch (NullReferenceException e)
    
    >{
        Console.WrileLine(e.Message);
    }

+ ArgumentOutRangeException  // 数组下标错误
+ OverflowException // 运算溢出 ：MinValue/MaxValue
+ System.FormatException: 输入字符串的格式不正确



6.数据类型
+ sbyte 
    * -128~127 有符号8位整数 // System.sbyte
    * sbyte sByte1 = 127;
    * 重载的时候要强制转换
    * 存在从 sbyte 到 short、int、long、float、double 或 decimal 的预定义隐式转换
    * sbyte z = x + y;  // 编译错误：= 右边的算术表达式为int
        + 更改: sbyte z = (sbyte)(x + y);
    * sbyte x = 3.0; // 错误
        + 更改: sbyte x = (sbyte)3.0;

+ var
    * 必须在定义时初始化eg. var s = "abc"，初始化完成就不能再赋予与初始化值类型不同的值
    * 局部变量
    * var 定义变量和object不同，它在效率上和使用强类型方式定义变量完全一样
    * 


