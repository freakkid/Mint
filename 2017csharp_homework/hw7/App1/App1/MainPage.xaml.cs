using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace App1
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            province.Text = city.Text = company.Text = errorMessage.Text = String.Empty;
            queryAsync(phone.Text);
        }

        async void queryAsync(string phone)
        {
            string url = "http://apis.juhe.cn/mobile/get?phone=" + phone + "&dtype=json&key=08f389bf615cf7263d593cf7f086708f";
            HttpClient client = new HttpClient();
            string result = await client.GetStringAsync(url);
            // 因为实体类型结果不可知，先使用匿名类型获得resultcode
            var resultCodeEntity = new { resultcode = String.Empty, reason = String.Empty};
            resultCodeEntity = JsonConvert.DeserializeAnonymousType(result, resultCodeEntity);

            if (resultCodeEntity.resultcode == "200")
            {
                var resultEntity = new { province = String.Empty, city = String.Empty, company = String.Empty };
                var succesSresultEntity = new { resultcode = String.Empty, result = resultEntity, reason = String.Empty };
                succesSresultEntity = JsonConvert.DeserializeAnonymousType(result, succesSresultEntity);
                province.Text = succesSresultEntity.result.province;
                city.Text = succesSresultEntity.result.city;
                company.Text = succesSresultEntity.result.company;
            }
            else
            {
                errorMessage.Text = resultCodeEntity.reason;
            }

        }


    }
}
