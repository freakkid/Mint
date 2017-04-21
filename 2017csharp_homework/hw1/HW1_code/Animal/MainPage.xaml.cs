using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace Animal
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private delegate void AnimalSaying(object sender);//声明一个委托
        private event AnimalSaying Say;//委托声明一个事件


        public MainPage()
        {
            this.InitializeComponent();
        }

        interface Animal
        {
            //方法
            void saying(object sender);
            //属性
            string Name { get; }
        }

        class cat : Animal
        {
            TextBlock word;
            public const string name = "cat";

            public cat(TextBlock w)
            {
                this.word = w;
            }
            public void saying(object sender)
            {
                this.word.Text += speakWords(name);
            }
            public string Name
            {
                get { return name; }
            }
        }

        class dog : Animal
        {
            TextBlock word;
            public const string name = "dog";

            public dog(TextBlock w)
            {
                this.word = w;
            }
            public void saying(object sender)
            {
                this.word.Text += speakWords(name);
            }
            public string Name
            {
                get { return name; }
            }
        }

        class pig : Animal
        {
            TextBlock word;
            public const string name = "pig";

            public pig(TextBlock w)
            {
                this.word = w;
            }
            public void saying(object sender)
            {
                this.word.Text += speakWords(name);
            }
            public string Name
            {
                get { return name; }
            }
        }

        // 返回动物讲的话,eg. "Cat: I am a cat."
        public static string speakWords(string animalName)
        {
            return String.Format("{0}: I am a {1}\n",
                        capitalizeString(animalName), animalName);
        }

        // 使得字符串首字符大写,eg. cat  -----> Cat
        private static string capitalizeString(string strToCapitalize)
        {
            if (String.IsNullOrEmpty(strToCapitalize))
                return strToCapitalize;
            else
                return strToCapitalize[0].ToString().ToUpper() +
                                                strToCapitalize.Substring(1);
        }

        private enum animals { dog, cat, pig };   // 动物的枚举
        private cat c;
        private dog d;
        private pig p;
        bool isFirstTime = true;

        private void Speak_Click(object sender, RoutedEventArgs e)
        {   
            if (isFirstTime)
            {
                doSomeInitialWork();
            }

            generateRandomAnimal();

            Say(this);
        }

        private void OK_Click(object sender, RoutedEventArgs e)
        {
            if (isFirstTime)
            {
                doSomeInitialWork();
            }

            bool isSpeakAble = true;
            generateAnimalByInputText(ref isSpeakAble);

            clearInputTextbox();  

            if (isSpeakAble)
                Say(this);
        }


        // 第一次输入的初始化工作
        private void doSomeInitialWork()
        {
            words.Text = String.Empty;
            c = new cat(words);
            d = new dog(words);
            p = new pig(words);

            isFirstTime = false;
        }

        // 随机获取动物
        private void generateRandomAnimal()
        {
            switch (getRandomAnimalNumber())
            {
                case (int)animals.dog:
                    Say = new AnimalSaying(d.saying);
                    break;
                case (int)animals.cat:
                    Say = new AnimalSaying(c.saying);
                    break;
                case (int)animals.pig:
                    Say = new AnimalSaying(p.saying);
                    break;
            }
        }

        // 产生随机数以产生随机动物
        private static int getRandomAnimalNumber()
        {
            return (new Random()).Next(0, getLengthOfAnimalsEnum()); // 随机数的获取与动物数量相关
        }

        // 根据input（Textbox）获取动物
        private void generateAnimalByInputText(ref bool isSpeakAble)
        {
            generateAnimalByAnimalName(input.Text, ref isSpeakAble);
        }
        
        // 根据动物名获取动物
        private void generateAnimalByAnimalName(string aniamlName,
                                                        ref bool isSpeakAble)
        {
            switch (aniamlName)
            {
                case dog.name:
                    Say = new AnimalSaying(d.saying);
                    break;
                case cat.name:
                    Say = new AnimalSaying(c.saying);
                    break;
                case pig.name:
                    Say = new AnimalSaying(p.saying);
                    break;
                default:
                    isSpeakAble = false;
                    break;
            }
        }

        // 得到animal的枚举变量的数量（即animal的个数）
        private static int getLengthOfAnimalsEnum() {
            return Enum.GetNames(typeof(animals)).Length;
        }
        
        // 清除输入textbox的文本
        private void clearInputTextbox()
        {
            input.Text = String.Empty;
        }

    }
}


