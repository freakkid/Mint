using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace Todos
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class NewPage : Page
    {
        public NewPage()
        {
            this.InitializeComponent();
        }
        private ViewModels.TodoItemViewModel ViewModel;

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            ViewModel = ((ViewModels.TodoItemViewModel)e.Parameter);
            if (ViewModel.SelectedItem == null)
            {
                namedCreateButton();
            }
            else // 点击item后创建的页面
            {
                namedUpdateButton();
                title.Text = ViewModel.SelectedItem.title;
                description.Text = ViewModel.SelectedItem.description;
                image.Source = ViewModel.SelectedItem.bitMapImage;
                dueDatePicker.Date = ViewModel.SelectedItem.dueDate;
            }
            SystemNavigationManager.GetForCurrentView().BackRequested += CurrentView_BackRequested;
        }
        private void CurrentView_BackRequested(object sender, BackRequestedEventArgs e)
        {
            Frame.Navigate(typeof(MainPage), ViewModel);
        }
        private void CreateButton_Clicked(object sender, RoutedEventArgs e)
        {
            // check the textbox and datapicker
            // if ok
            string newTitle = title.Text;
            string newDescription = description.Text;
            DateTimeOffset dueDate = dueDatePicker.Date;
            if (newTitle == string.Empty || newDescription == string.Empty || dueDate < DateTime.Today.Date)
            {
                var i = new MessageDialog("Empty Message Or Early Datetime!").ShowAsync();
            }
            else
            {
                BitmapImage bitmapImage = image.Source as BitmapImage;
                if ((string)CreateButton.Content == "Create")
                {
                    ViewModel.AddTodoItem(newTitle, newDescription, bitmapImage, dueDate);
                }
                else
                {
                    ViewModel.UpdateTodoItem(ViewModel.SelectedItem.getId(), newTitle, newDescription, bitmapImage, dueDate);
                }
                Frame.Navigate(typeof(MainPage), ViewModel);
            }

        }

        private void CancelButton_Clicked(object sender, RoutedEventArgs e)
        {
            title.Text = string.Empty;
            description.Text = string.Empty;
            dueDatePicker.Date = DateTime.Today.Date;
        }

        private void DeleteButton_Clicked(object sender, RoutedEventArgs e)
        {
            if (ViewModel.SelectedItem != null)
            {
                ViewModel.RemoveTodoItem(ViewModel.SelectedItem.getId());
            }
            Frame.Navigate(typeof(MainPage), ViewModel);
        }

        private async void SelectButton_Click(object sender, RoutedEventArgs e)
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.ViewMode = PickerViewMode.Thumbnail;
            picker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            addPickerType(picker);

            StorageFile file = await picker.PickSingleFileAsync();

            if (file != null)
            {
                changeTheImage(file);
            }
        }

        private void addPickerType(FileOpenPicker picker)
        {
            picker.FileTypeFilter.Add(".jpg");
            picker.FileTypeFilter.Add(".jpeg");
            picker.FileTypeFilter.Add(".png");
            picker.FileTypeFilter.Add(".bmp");
            picker.FileTypeFilter.Add(".gif");
        }

        private async void changeTheImage(StorageFile file)
        {
            IRandomAccessStream fileStream = await file.OpenAsync(FileAccessMode.Read);
            BitmapImage bitmapImage = new BitmapImage();
            await bitmapImage.SetSourceAsync(fileStream);
            image.Source = bitmapImage;
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
