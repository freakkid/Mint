using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage.Pickers;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Popups;
using Windows.UI.Xaml.Media.Imaging;
using Windows.Storage.Streams;

namespace Todos
{
    public sealed partial class NewPage : Page
    {
        public NewPage()
        {
            this.InitializeComponent();
            var viewTitleBar = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView().TitleBar;
            viewTitleBar.BackgroundColor = Windows.UI.Colors.CornflowerBlue;
            viewTitleBar.ButtonBackgroundColor = Windows.UI.Colors.CornflowerBlue;
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            Frame rootFrame = Window.Current.Content as Frame;

            if (rootFrame.CanGoBack)
            {
                SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                    AppViewBackButtonVisibility.Visible;
            }
            else
            {
                SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                    AppViewBackButtonVisibility.Collapsed;
            }
            var i = new MessageDialog("Welcome!").ShowAsync();
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
                // bigImage.Source = await GetImageAsync(file);
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
            bigImage.Source = bitmapImage;
        }

        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            if (isTitleEmptyText())
            {
                sendBlankTitleError();
            }
            else if (isDetailEmptyText())
            {
                sendBlankDetailError();
            }
            else if (isEarlyDate())
            {
                sendEarlyDateError();
            }
            else
            {
                sendCreateSuccessMessage();
            }
        }

        private bool isTitleEmptyText()
        {
            return isEmptyText(TitleText.Text);
        }

        private bool isDetailEmptyText()
        {
            return isEmptyText(DetailText.Text);
        }

        private bool isEmptyText(string stringToCheck)
        {
            return stringToCheck == string.Empty;
        }

        private bool isEarlyDate()
        {
            return DateTime.Today.Date > DueDatePicker.Date;
        }

        private void sendBlankTitleError()
        {        
            var i = new MessageDialog("Title can't be blank").ShowAsync();
        }

        private void sendBlankDetailError()
        {
            var i = new MessageDialog("Detail can't be blank").ShowAsync();
        }

        private void sendEarlyDateError()
        {
            var i = new MessageDialog("Date should not be ealier than today").ShowAsync();
        }

        private void sendCreateSuccessMessage()
        {
            var i = new MessageDialog("Create Success!").ShowAsync();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            restoreSettings();
        }

        private void restoreSettings()
        {
            TitleText.Text = string.Empty;
            DetailText.Text = string.Empty;
            DueDatePicker.Date = DateTime.Today.Date;
        }

    }
}
