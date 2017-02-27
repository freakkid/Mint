# c#零碎笔记

1. 被迫升级了win10和强装了vs
2. 

---------

1.字符串
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

+ 

2.数组
+ using System.Linq;
+ 首元素 array.First()
+ >// 第一个满足条件的元素
   int firstLagerFive = numbers.First(number => number > 5);
+ 
    
3.异常
+ catch方法：

    >try{}
    
    >catch (NullReferenceException e)
    
    >{
        Console.WrileLine(e.Message);
    }

+ ArgumentOutRangeException  // 数组下标错误
+ 