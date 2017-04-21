using System;
using System.Collections.Generic;
using System.IO;

using System.Text;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Data.Xml.Dom;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Notifications;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;
using Windows.ApplicationModel.DataTransfer;
using Windows.Storage;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace Todos
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            this.ViewModel = new ViewModels.TodoItemViewModel();
            // 启动通知队列
            TileUpdateManager.CreateTileUpdaterForApplication().EnableNotificationQueue(true);
            XmlToTileNotification();
        }
        ViewModels.TodoItemViewModel ViewModel { get; set; }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // 页面跳转导航:当导航事件参数是ViewModels
            if (e.Parameter.GetType() == typeof(ViewModels.TodoItemViewModel))
            {
                this.ViewModel = (ViewModels.TodoItemViewModel)(e.Parameter);
                // 清楚原来队列内容，实现更新
                TileUpdater updater = TileUpdateManager.CreateTileUpdaterForApplication();
                updater.Clear();
                XmlToTileNotification();
            }
        }

        private void XmlToTileNotification()
        {
            int viewModelNum = ViewModel.AllItems.Count(); // item的数量
            int tileNotificationNum = ViewModel.AllItems.Count() >= 5 ? 5 : ViewModel.AllItems.Count();
            // 只获得最新添加的5个item的信息
            for (int i = viewModelNum - tileNotificationNum; i < viewModelNum; i++)
            {
                XmlDocument doc = getXmlDocument();        // 加载xml
                XmlNodeList bindingNodeList = doc.GetElementsByTagName("binding"); 

                if (bindingNodeList != null)
                {
                    for (int j = 0; j < bindingNodeList.Length; j++)
                    {
                        XmlNodeList textNodeList = bindingNodeList[j].SelectNodes("text");
                        textNodeList[0].InnerText = ViewModel.AllItems[i].title;
                        textNodeList[1].InnerText = ViewModel.AllItems[i].description;
                    }
                }
                updateTileNotification(doc);    // 更新通知队列
            }
        }

        private XmlDocument getXmlDocument()
        {
            string titleString = File.ReadAllText("title.xml");
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(titleString);
            return doc;
        }

        private void updateTileNotification(XmlDocument doc)
        {
            TileNotification tileNotification = new TileNotification(doc);
            TileUpdater updater = TileUpdateManager.CreateTileUpdaterForApplication();
            updater.Update(tileNotification);
        }

        private void TodoItem_ItemClicked(object sender, ItemClickEventArgs e)
        {
            // 点击一个item后，跳转item的那个页面
            ViewModel.SelectedItem = (Models.TodoItem)(e.ClickedItem);
            namedUpdateButton();
            // 把这个被点击的item传递进新的页面中去
            if (this.ActualWidth < 800)
            {
                Frame.Navigate(typeof(NewPage), ViewModel);
            }
            else
            {
                Models.TodoItem toDoItem = ViewModel.SelectedItem;
                titleTextBox.Text = toDoItem.title;
                detailsTextBox.Text = toDoItem.description;
                rectangleImage.Source = toDoItem.bitMapImage;
                dueDatePicker.Date = toDoItem.dueDate;
            }
        }

        private void ShareAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            // 被点击的Item
            dynamic context = e.OriginalSource;
            ViewModel.SelectedItem = (Models.TodoItem)context.DataContext;

            DataTransferManager dataTransferManager = DataTransferManager.GetForCurrentView();
            dataTransferManager.DataRequested += 
                new TypedEventHandler<DataTransferManager, DataRequestedEventArgs>(this.DataRequested);
            DataTransferManager.ShowShareUI();
        }

        private void DataRequested(DataTransferManager sender, DataRequestedEventArgs e)
        {
            DataRequest request = e.Request;
            request.Data.Properties.Title = ViewModel.SelectedItem.title;
            request.Data.Properties.Description = ViewModel.SelectedItem.description;
            request.Data.SetBitmap(Windows.Storage.Streams.RandomAccessStreamReference.CreateFromUri(
                                                            new Uri("ms-appx:///Assets/background.jpg")));
        }

        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            if (this.ActualWidth < 800) // 按下"+"的按钮后，且屏宽不超过800， 跳转到新的页面
            {
                Frame.Navigate(typeof(NewPage), ViewModel);
            }
            else
            {
                namedCreateButton();
                restoreInformaion();
            }
        }
        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {

            if (titleTextBox.Text == string.Empty || detailsTextBox.Text == string.Empty || dueDatePicker.Date < DateTime.Today.Date)
            {
                var i = new MessageDialog("Empty Message Or Early Datetime!").ShowAsync();
            }
            else
            {
                BitmapImage newImageSource = rectangleImage.Source as BitmapImage;
                if (this.ViewModel.SelectedItem == null || (string)CreateButton.Content == "Create")
                {
                    this.ViewModel.AddTodoItem(titleTextBox.Text, detailsTextBox.Text, newImageSource, dueDatePicker.Date);
                }
                else
                {
                    this.ViewModel.UpdateTodoItem(ViewModel.SelectedItem.getId(), titleTextBox.Text, detailsTextBox.Text, newImageSource, dueDatePicker.Date);
                    namedCreateButton();
                }
                Frame.Navigate(typeof(MainPage), ViewModel);
            }
        }
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            restoreInformaion();
        }
        private void restoreInformaion()
        {
            titleTextBox.Text = string.Empty;
            detailsTextBox.Text = string.Empty;
            dueDatePicker.Date = DateTime.Today.Date;
        }
        private void namedUpdateButton()
        {
            CreateButton.Content = "Update";
        }

        private void namedCreateButton()
        {
            CreateButton.Content = "Create";
        }
    }
}
