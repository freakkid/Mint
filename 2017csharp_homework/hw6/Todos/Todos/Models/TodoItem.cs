using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI.Popups;
using Windows.UI.Xaml.Media.Imaging;

namespace Todos.Models
{
    class TodoItem
    {
        public static string defalutImagePath = "ms-appx:///Assets/background.jpg";
        private string id;

        public string title { get; set; }

        public string description { get; set; }

        public bool? completed { get; set; }

        public BitmapImage bitMapImage { get; set; }

        public Uri imageUri { get; set; }

        public DateTimeOffset dueDate { get; set; }

        public TodoItem(string title, string description, Uri imageUri, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            this.id = Guid.NewGuid().ToString(); // 生成id
            UpdateTodoItem(title, description, imageUri, bitMapImage, dueDate);
            this.completed = false; // 默认为未完成 未完成-----> 直线不可见
        }
        // 更新item，id不变
        public void UpdateTodoItem(string title, string description, Uri imageUri, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            this.title = title;
            this.description = description;
            this.imageUri = imageUri;
            this.bitMapImage = bitMapImage;
            this.dueDate = dueDate;
        }
        // 写一个函数判断id是否符合bool
        public bool isIdEqual(string idToCheck)
        {
            return idToCheck == getId();
        }
        public string getId()
        {
            return id;
        } 
        // 从数据库获得item数据 或 将数据转换后保存到数据库
        public TodoItem(string id, string title, string description, string imageUriString, string dueDate)
        {
            this.id = id;
            this.title = title;
            this.description = description;
            this.imageUri = stringToUri(imageUriString);
            if (imageUriString == defalutImagePath) // 如果是默认背景图片
            {
                this.bitMapImage = new BitmapImage(this.imageUri);
            }
            else                                    // 用户自行选择的图片
            {
                stringPathToBitmapImage(imageUri.LocalPath);
            }
            this.dueDate = stringToDateTimeOffset(dueDate);
            this.completed = false;
        }
        // 用户自行选择的图片，从路径获得图片
        private void stringPathToBitmapImage(string path)
        {
            BitmapImage image = new BitmapImage(new Uri(path));
            this.bitMapImage = image;
        }
        public static Uri stringToUri(string uriString)
        {
            return new Uri(uriString);
        }
        public static string uriToString(Uri imageUri)
        {
            return imageUri.ToString();
        }
        public static string dateTimeOffsetToStrinng(DateTimeOffset dueDate)
        {
            return dueDate.ToString();
        }
        public static DateTimeOffset stringToDateTimeOffset(string dataTimeString)
        {
            return DateTimeOffset.Parse(dataTimeString);
        }
        
    }
}
