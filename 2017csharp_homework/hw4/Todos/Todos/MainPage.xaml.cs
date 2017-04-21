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
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Newtonsoft.Json;


//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace Todos
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public bool isSuspend = false;  // 判断是否挂起状态
        public MainPage()
        {
            this.InitializeComponent();
            var viewTitleBar = Windows.UI.ViewManagement.ApplicationView.GetForCurrentView().TitleBar;
            viewTitleBar.BackgroundColor = Windows.UI.Colors.CornflowerBlue;
            viewTitleBar.ButtonBackgroundColor = Windows.UI.Colors.CornflowerBlue;
        }

        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(NewPage), "");
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            if (e.NavigationMode == NavigationMode.New)
            {
                ApplicationData.Current.LocalSettings.Values.Remove("TheWorkInProgress");
            }
            else
            {
                if (ApplicationData.Current.LocalSettings.Values.ContainsKey("TheWorkInProgress"))
                {
                    var composite = ApplicationData.Current.LocalSettings.Values["TheWorkInProgress"] as ApplicationDataCompositeValue;
                    upCheckBox.IsChecked = stringToDataType.ToIsChecked(composite["upCheckBox"].ToString());
                    upLine.Visibility = stringToDataType.ToVisibility(composite["upLine"].ToString());
                    downCheckBox.IsChecked = stringToDataType.ToIsChecked(composite["downCheckBox"].ToString());
                    downLine.Visibility = stringToDataType.ToVisibility(composite["downLine"].ToString());

                    // Done with it, so remove it
                    ApplicationData.Current.LocalSettings.Values.Remove("TheWorkInProgress");
                }
            }
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            bool suspending = ((App)App.Current).isSuspend;
            if (suspending)
            {
                ApplicationDataContainer localSetting = ApplicationData.Current.LocalSettings;
                ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
                composite["upCheckBox"] = upCheckBox.IsChecked.ToString();
                composite["upLine"] = upLine.Visibility.ToString();
                composite["downCheckBox"] = downCheckBox.IsChecked.ToString();
                composite["downLine"] = downLine.Visibility.ToString();

                localSetting.Values["TheWorkInProgress"] = composite;
            }
                
        }
        // 将字符串转换成其他数据类型
        public class stringToDataType
        {
            public static bool? ToIsChecked(String strValue)
            {
                if (strValue == ((bool?)true).ToString())
                {
                    return true;
                }
                else if (strValue == ((bool?)false).ToString())
                {
                    return false;
                }
                else
                {
                    return null;
                }
            }

            public static Visibility ToVisibility(String strValue)
            {
                if (strValue == Visibility.Visible.ToString())
                {
                    return Visibility.Visible;
                }
                else
                {
                    return Visibility.Collapsed;
                }
            }
        }

    }

            
 
}


