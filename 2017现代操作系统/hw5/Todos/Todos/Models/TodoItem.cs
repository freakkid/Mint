using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Media.Imaging;

namespace Todos.Models
{
    class TodoItem
    {
        private string id;

        public string title { get; set; }

        public string description { get; set; }

        public bool? completed { get; set; }

        public BitmapImage bitMapImage { get; set; }

        public DateTimeOffset dueDate { get; set; }

        public TodoItem(string title, string description, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            this.id = Guid.NewGuid().ToString(); // 生成id
            this.UpdateTodoItem(title, description, bitMapImage, dueDate);
            this.completed = false; // 默认为未完成 未完成-----> 直线不可见
        }
        // 更新item ，id不变
        public void UpdateTodoItem(string title, string description, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            this.title = title;
            this.description = description;
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
    }
}
