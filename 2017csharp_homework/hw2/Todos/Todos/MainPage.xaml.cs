using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Core;
using Windows.UI.Xaml.Shapes;

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
            var viewTitleBar = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView().TitleBar;
            viewTitleBar.BackgroundColor = Windows.UI.Colors.CornflowerBlue;
            viewTitleBar.ButtonBackgroundColor = Windows.UI.Colors.CornflowerBlue;
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            Frame rootFrame = Window.Current.Content as Frame;
            if (Frame.CanGoBack)
            {
                SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                           AppViewBackButtonVisibility.Visible;
            }
            else
            {
                SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
                           AppViewBackButtonVisibility.Collapsed;
            }
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(NewPage), "");
        }

        private void checkBox1_Checked(object sender, RoutedEventArgs e)
        {
            if (isCheckBox1NotChecked())
            {
                collapsedTheLine1();
            }
            else
            {
                visibleTheLine1();
            }
        }

        private void checkBox2_Checked(object sender, RoutedEventArgs e)
        {
            if (isCheckBox2NotChecked())
            {
                collapsedTheLine2();
            }
            else
            {
                visibleTheLine2();
            }
        }
        private bool isCheckBox1NotChecked()
        {
            return isNotChecked(checkBox1);
        }

        private bool isCheckBox2NotChecked()
        {
            return isNotChecked(checkBox2);
        }

        private bool isNotChecked(CheckBox checkBox)
        {
            return checkBox.IsChecked == false;
        }

        private void visibleTheLine1()
        {
            visibleTheLine(line1);
        }

        private void visibleTheLine2()
        {
            visibleTheLine(line2);
        }

        private void collapsedTheLine1()
        {
            collapsedTheLine(line1);
        }

        private void collapsedTheLine2()
        {
            collapsedTheLine(line2);
        }

        private void visibleTheLine(Line line)
        {
            line.Visibility = Visibility.Visible;
        }

        private void collapsedTheLine(Line line)
        {
            line.Visibility = Visibility.Collapsed;
        }
    }
}
