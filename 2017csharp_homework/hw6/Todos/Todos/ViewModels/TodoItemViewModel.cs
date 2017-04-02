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
        private ObservableCollection<Models.TodoItem> allItems;
        public ObservableCollection<Models.TodoItem> AllItems { get { return this.allItems; } }

        private Models.TodoItem selectedItem = default(Models.TodoItem);   // 选择当前的item
        public Models.TodoItem SelectedItem { get { return selectedItem; } set { this.selectedItem = value; } }

        public TodoItemViewModel()
        {
            allItems = SqlLocalData.SqlData.getAllTodoItem();  // 从数据库获取数据
        }

        public void AddTodoItem(string title, string description, Uri imageUri, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            Models.TodoItem todoItem = new Models.TodoItem(title, description, imageUri, bitMapImage, dueDate);
            allItems.Add(todoItem);
            string imageUriString = String.Empty;
            imageUriString = Models.TodoItem.uriToString(imageUri);
            SqlLocalData.SqlData.insertItem(todoItem.getId(), title, description, Models.TodoItem.uriToString(imageUri), Models.TodoItem.dateTimeOffsetToStrinng(dueDate));
        }

        public void RemoveTodoItem(string id)
        {
            int index = getIndexOfItemById(id);
            if (index != -1)
            {
                allItems.Remove(allItems[index]);
                SqlLocalData.SqlData.deleteItem(id);
            }
            this.selectedItem = null;
        }

        public void UpdateTodoItem(string id, string title, string description, Uri imageUri, BitmapImage bitMapImage, DateTimeOffset dueDate)
        {
            int index = getIndexOfItemById(id);
            if (index != -1)
            {          
                SqlLocalData.SqlData.updateItemById(id, title, description, Models.TodoItem.uriToString(imageUri), Models.TodoItem.dateTimeOffsetToStrinng(dueDate));
                allItems[index].UpdateTodoItem(title, description, imageUri, bitMapImage, dueDate);
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
