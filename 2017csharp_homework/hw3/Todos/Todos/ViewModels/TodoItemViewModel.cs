using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using Windows.UI.Xaml.Media.Imaging;

namespace Todos.ViewModels
{
    class TodoItemViewModel
    {
        private ObservableCollection<Models.TodoItem> allItems = new ObservableCollection<Models.TodoItem>();
        public ObservableCollection<Models.TodoItem> AllItems { get { return this.allItems; } }

        private Models.TodoItem selectedItem = default(Models.TodoItem);   // 选择当前的item
        public Models.TodoItem SelectedItem { get { return selectedItem; } set { this.selectedItem = value; } }

        public TodoItemViewModel()
        {
            addTestItems();
        }
        // 加入两个用来测试的item
        private void addTestItems()
        {
            BitmapImage newImageSource = new BitmapImage(new Uri("ms-appx:///Assets/background.jpg"));
            DateTimeOffset dueDate = DateTime.Today.Date;

            allItems.Add(new Models.TodoItem("123", "123", newImageSource, dueDate));
            allItems.Add(new Models.TodoItem("456", "456", newImageSource, dueDate));
        }

        public void AddTodoItem(string title, string description, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            allItems.Add(new Models.TodoItem(title, description, bitMapImage, dueDate));
        }

        public void RemoveTodoItem(string id)
        {
            int index = getIndexOfItemById(id);
            if (index != -1)
            {
                allItems.Remove(allItems[index]);
            }
            this.selectedItem = null;
        }

        public void UpdateTodoItem(string id, string title, string description, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            int index = getIndexOfItemById(id);
            if (index != -1)
            {
                allItems[index].UpdateTodoItem(title, description, bitMapImage, dueDate);
            }
            this.selectedItem = null;
        }

        private int getIndexOfItemById(string id)
        {
            for (int i = 0; i < allItems.Count; i++)
            {
                if (allItems[i].isIdEqual(id))// 判断id是否符合/删除
                {
                    return i;
                }
            }
            return -1;
        }
    }
}
