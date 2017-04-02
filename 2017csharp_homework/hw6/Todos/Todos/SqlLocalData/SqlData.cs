using SQLitePCL;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Todos.SqlLocalData
{
    class SqlData
    {
        private static string datebaseName = "TodoItem.db";
        public SqlData()
        {
            var conn = getSqliteConn();
            using (var statement = conn.Prepare(SqlStatement.createDatebase))
            {
                statement.Step();
            }
        }
        private static SQLiteConnection getSqliteConn()
        {
            return new SQLiteConnection(datebaseName);
        }

        public static ObservableCollection<Models.TodoItem> getAllTodoItem()
        {
            ObservableCollection<Models.TodoItem> todoItemList = new ObservableCollection<Models.TodoItem>();
            var conn = getSqliteConn();
            var statement = conn.Prepare(SqlStatement.selectAllItems);
            while (statement.Step() == SQLiteResult.ROW)
            {
                todoItemList.Add(new Models.TodoItem((string)statement[0], (string)statement[1], (string)statement[2],
                                                            (string)statement[3], (string)statement[4]));
            }
            return todoItemList;
        }
        public static bool insertItem(string id, string title, string description, string imageUri, string dueDate)
        {
            var conn = getSqliteConn();
            try
            {
                using (var statement = conn.Prepare(SqlStatement.insertItem))
                {
                    statement.Bind(1, id);
                    statement.Bind(2, title);
                    statement.Bind(3, description);
                    statement.Bind(4, imageUri);
                    statement.Bind(5, dueDate);
                    statement.Step();
                }
            }
            catch (Exception)
            {
                return false;
            }
            return true;
        }
        public static void updateItemById(string id, string title, string description, string imageUri, string dueDate)
        {
            var conn = getSqliteConn();
            using (var statement = conn.Prepare(SqlStatement.updateItem))
            {
                statement.Bind(1, title);
                statement.Bind(2, description);
                statement.Bind(3, imageUri);
                statement.Bind(4, dueDate);
                statement.Bind(5, id);
                statement.Step();
            }
        }

        public static void deleteItem(string id)
        {
            var conn = getSqliteConn();
            using (var statement = conn.Prepare(SqlStatement.deleteItem))
            {
                statement.Bind(1, id);
                statement.Step();
            }
        }
    }

    public static class SqlStatement
    {
        public static string createDatebase = @"CREATE TABLE IF NOT EXISTS
                                            TodoItem (id            STRING PRIMARY KEY NOT NULL,
                                                      title         VARCHAR(140) NOT NULL,
                                                      description   TEXT,
                                                      imageUri      VARCHAR(300),
                                                      dueDate       VARCHAR(140));";

        public static string insertItem = @"INSERT INTO TodoItem (id, title, description, imageUri, dueDate)
                                                        VALUES (?, ?, ?, ?, ?);";

        public static string selectAllItems = @"SELECT id, title, description, imageUri, dueDate FROM TodoItem";

        public static string updateItem = @"UPDATE TodoItem set title=?, description=?, imageUri=?, dueDate=? WHERE id=?";

        public static string deleteItem = @"DELETE FROM TodoItem WHERE id=?";

    }
}
