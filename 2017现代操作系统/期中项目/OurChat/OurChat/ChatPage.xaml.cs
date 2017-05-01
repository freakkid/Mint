using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Navigation;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using SQLitePCL;
using Windows.UI.Popups;
using Windows.ApplicationModel.DataTransfer;
using Windows.Data.Xml.Dom;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace OurChat {
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class ChatPage : Page {

        public ObservableCollection<Content> content = new ObservableCollection<Content>();
        private string username;
        private ImageSource user_avatar;
        private Content selectContent;

        public ChatPage() {
            this.InitializeComponent();
            this.content.Add(new Content { message = "你好，我是Turing", name = "left", time = DateTime.Now, code = "100000" });
        }

        //获取上个页面传入的用户名
        protected override void OnNavigatedTo(NavigationEventArgs e) {
            if (e.Parameter.GetType() == typeof(UserItem))
            {
                UserItem user = (UserItem)(e.Parameter);
                username = user.username;
                user_avatar = new BitmapImage(user.avatarUri);
                DataTransferManager.GetForCurrentView().DataRequested += OnShareDataRequested;
            }
        }

        private void clear_Click(object sender, RoutedEventArgs e) {
            content.Clear();
        }

        private void disconnect_Click(object sender, RoutedEventArgs e) {
            Frame.Navigate(typeof(MainPage));
        }

        private void Send_OnClick(object sender, RoutedEventArgs e) {
            string massage = send_text.Text;
            content.Add(new Content() { message = massage, name = "right", time = DateTime.Now, username = username, user_avatar = user_avatar});
            send_text.Text = "";
            SendMessage(massage);
        }

        public async void SendMessage(string message) {
            string content = await GetAnswer("http://www.tuling123.com/openapi/api?key=785afc93b0f846989b31fd4b5ceeffe5&info=" + message);
            JObject jsonobj = JObject.Parse(content);
            string code = jsonobj["code"].ToString();
            Debug.WriteLine(code);
            if (code == "100000") { // 文本类
                string text = jsonobj["text"].ToString();
                this.content.Add(new Content { message = text, name = "left", time = DateTime.Now, code = "100000" });
            } else if (code == "200000")// 链接类
              {
                string text = jsonobj["text"].ToString();
                string url = jsonobj["url"].ToString();
                this.content.Add(new Content { message = text, url = url, name = "left", time = DateTime.Now, code = "200000" });
            } else if (code == "302000")// 新闻类
              {
                string text = jsonobj["text"].ToString();
                string json = jsonobj["list"].ToString();
                List<mList> newslist = JsonConvert.DeserializeObject<List<mList>>(json);
                this.content.Add(new Content { message = text, list = newslist, name = "left", time = DateTime.Now, code = "302000" });
            } else if (code == "308000")// 菜谱类
              {
                string text = jsonobj["text"].ToString();
                string json = jsonobj["list"].ToString();
                List<mList> newslist = JsonConvert.DeserializeObject<List<mList>>(json);
                this.content.Add(new Content { message = text, list = newslist, name = "left", time = DateTime.Now, code = "308000" });
            }

        }

        private async Task<string> GetAnswer(string uri) {
            string content = "";
            return await Task.Run(() => {
                HttpClient httpClient = new HttpClient();
                HttpResponseMessage response;
                response = httpClient.GetAsync(new Uri(uri)).Result;
                if (response.StatusCode == HttpStatusCode.OK)
                    content = response.Content.ReadAsStringAsync().Result;
                else {
                    content = "好像网络有问题呢..";
                }
                return content;
            });
        }

        private async void voice_Click(System.Object sender, RoutedEventArgs e)
        {
            // Create an instance of SpeechRecognizer.
            var speechRecognizer = new Windows.Media.SpeechRecognition.SpeechRecognizer();

            // Compile the dictation grammar by default.
            await speechRecognizer.CompileConstraintsAsync();

            // Start recognition.
            Windows.Media.SpeechRecognition.SpeechRecognitionResult speechRecognitionResult = await speechRecognizer.RecognizeWithUIAsync();
            send_text.Text = speechRecognitionResult.Text;
        }

        private void ItemsStackPanel_RightTapped(object sender, RightTappedRoutedEventArgs e)
        {
            MenuFlyout myFlyout = new MenuFlyout();
            MenuFlyoutItem firstItem = new MenuFlyoutItem { Text = "Share" };
            myFlyout.Items.Add(firstItem);
            firstItem.Click += share_Click;
            //if you only want to show in left or buttom 
            //myFlyout.Placement = FlyoutPlacementMode.Left;
            FrameworkElement senderElement = sender as FrameworkElement;
            //the code can show the flyout in your mouse click 
            myFlyout.ShowAt(sender as UIElement, e.GetPosition(sender as UIElement));

            selectContent = (e.OriginalSource as TextBlock)?.DataContext as Content;
        }

        private void share_Click(object sender, RoutedEventArgs e)
        {
            DataTransferManager.ShowShareUI();
        }

        private void OnShareDataRequested(DataTransferManager sender, DataRequestedEventArgs args)
        {
            if (selectContent == null)
            {
                var i = new MessageDialog("请右键点击第一句话分享！");
                var result = i.ShowAsync();
            }
            else
            {
                args.Request.Data.SetText(selectContent.message);
                args.Request.Data.Properties.Title = "图灵机器人聊天记录分享";
                args.Request.Data.Properties.Description = "Send by :" + username;
            }
        }
    }
}
