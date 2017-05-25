# Resource (Xaml篇)


FrameworkElement.Resources，即页面资源，为单一页面作配置，由于各种工具都继承自FrameworkElement,因此可以在Resourece标签中进行自定义

一般建议将资源定义放在Page中，方便查找管理

想必各位已经发现homework2有代码是重复的，像我这么懒的人，遇到重复的代码懒到不想去复制粘贴，并且如果出现需要更改的情况，会相当的麻烦！于是Resource应运而生啦，假如不用Resource：
```
<Button Content="OK" Foreground="Black" Background="Yellow" Margin="54,292,0,84"/>
<Button Content="OK" Foreground="Black" Background="Yellow" Margin="45,177,0,199"/>
```

![p7](Picture/02-07.png)

用上Resource:
```
<Page.Resources>
    <Style TargetType="Button">
        <Setter Property="Content" Value="Aha?"/>
        <Setter Property="Foreground" Value="Black"/>
        <Setter Property="Background" Value="Brown"/>
        <Setter Property="VerticalAlignment" Value="Top"/>
    </Style>
</Page.Resources>

<Button Margin="139,118,0,258" Content="WHY"  VerticalAlignment="Bottom"/>
<Button HorizontalAlignment="Left"/>
```

![p8](Picture/02-08.png)

结论：Resource可以解决重复代码的问题，而且实际属性可以覆盖资源的属性，非常棒！

嗯，到这里就结束啦？啊等一下，万一我需要的按钮有两种样式，那该怎么办？
那就用两个Source！加个关键字x:Key
```
<Page.Resources>
    <Style TargetType="Button" x:Key="Normal">
        <Setter Property="Content" Value="Aha?"/>
        <Setter Property="Foreground" Value="Black"/>
        <Setter Property="Background" Value="Brown"/>
        <Setter Property="VerticalAlignment" Value="Top"/>
    </Style>
    
    <Style TargetType="Button" x:Key="Yellow">
        <Setter Property="Content" Value="Nani?"/>
        <Setter Property="Foreground" Value="Black"/>
        <Setter Property="Background" Value="Brown"/>
        <Setter Property="VerticalAlignment" Value="Center"/>
    </Style>
</Page.Resources>
```
```
<Button VerticalAlignment="Bottom" Style="{StaticResource Normal}"/>
<Button Style="{StaticResource Yellow}"/>
```
![p9](Picture/02-09.png)

注意下：Key不可重复~

不过缺点就是上面的Resource有重复的代码，所以把YellowColor的Style改成
```
    <Style TargetType="Button" x:Key="Yellow">
        <Setter Property="Content" Value="Nani?"/>
        <Setter Property="Style" Value="{StaticResource Hello}"/>
    </Style>
```
嗯，没卵用的:)

正确的做法是用BaseOn继承父类的属性和方法，也就是
```
    <Style TargetType="Button" x:Key="Yellow" BaseOn="{StaticResource Normal}">
        <Setter Property="Content" Value="Nani?"/>
    </Style>
```
呐，是不是很棒！

参考一篇博客写的，写的比较简略，还没有人家写的好，不过不管啦~

[Reference](http://www.it165.net/pro/html/201311/7923.html)