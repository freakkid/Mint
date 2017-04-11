using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using Windows.Data.Xml.Dom;
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

namespace Appxml
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
            string url = "http://apis.juhe.cn/mobile/get?phone=" + phone + "&dtype=xml&key=08f389bf615cf7263d593cf7f086708f";
            HttpClient client = new HttpClient();
            string result = await client.GetStringAsync(url);
            
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(result);

            XmlNodeList resultCodeList = doc.GetElementsByTagName("resultcode");
            IXmlNode resultCodeNode = resultCodeList.Item(0);
            string resultCode = resultCodeNode.InnerText;

            if (resultCode == "200")
            {
                XmlNodeList provinceList = doc.GetElementsByTagName("province");
                IXmlNode provinceNode = provinceList.Item(0);
                province.Text = provinceNode.InnerText;

                XmlNodeList cityList = doc.GetElementsByTagName("city");
                IXmlNode cityNode = cityList.Item(0);
                city.Text = cityNode.InnerText;

                XmlNodeList companyList = doc.GetElementsByTagName("company");
                IXmlNode companyNode = companyList.Item(0);
                company.Text = companyNode.InnerText;
            }
            else
            {
                XmlNodeList reasonList = doc.GetElementsByTagName("reason");
                IXmlNode reasonNode = reasonList.Item(0);
                errorMessage.Text = reasonNode.InnerText;
            }
        }
    }
}
