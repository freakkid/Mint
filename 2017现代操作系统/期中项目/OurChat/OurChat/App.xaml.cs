﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Notifications;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using SQLitePCL;
using System.Threading.Tasks;
using Windows.ApplicationModel.VoiceCommands;
using Windows.Storage;
using Windows.Data.Xml.Dom;

namespace OurChat
{
    /// <summary>
    /// 提供特定于应用程序的行为，以补充默认的应用程序类。
    /// </summary>
    sealed partial class App : Application
    {

        public static SQLiteConnection conn;

        /// <summary>
        /// 初始化单一实例应用程序对象。这是执行的创作代码的第一行，
        /// 已执行，逻辑上等同于 main() 或 WinMain()。
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            this.Suspending += OnSuspending;

            // 创建数据库表
            conn = new SQLiteConnection("OurChat.db");
            string sql = @"CREATE TABLE IF NOT EXISTS
                                  UserItem (Username VARCHAR(140) PRIMARY KEY NOT NULL,
                                            Password VARCHAR(140) NOT NULL,
                                            Avataruri VARCHAR(200) NOT NULL
                           );";
            using (var statement = conn.Prepare(sql)) {
                statement.Step();
            }
            // 启动通知队列
            TileUpdateManager.CreateTileUpdaterForApplication().EnableNotificationQueue(true);
            XmlToTileNotification();
        }

        private void XmlToTileNotification()
        {
            TileUpdater updater = TileUpdateManager.CreateTileUpdaterForApplication();
            updater.Clear();
            XmlDocument ch_doc = getXmlDocument();        // 加载xml
            XmlNodeList ch_bindingNodeList = ch_doc.GetElementsByTagName("binding");

            if (ch_bindingNodeList != null)
            {
                XmlNodeList textNodeList = ch_bindingNodeList[1].SelectNodes("text");
                textNodeList[0].InnerText = "图灵机器人";
            }
            updateTileNotification(ch_doc);    // 更新通知队列

            XmlDocument eg_doc = getXmlDocument();        // 加载xml
            XmlNodeList eg_bindingNodeList = eg_doc.GetElementsByTagName("binding");
            if (eg_bindingNodeList != null)
            {
                XmlNodeList textNodeList = eg_bindingNodeList[1].SelectNodes("text");
                textNodeList[0].InnerText = "TuRing Robot";
            }
            updateTileNotification(eg_doc);    // 更新通知队列
        }

        private void updateTileNotification(XmlDocument doc)
        {
            TileNotification tileNotification = new TileNotification(doc);
            TileUpdater updater = TileUpdateManager.CreateTileUpdaterForApplication();
            updater.Update(tileNotification);
        }

        private XmlDocument getXmlDocument()
        {
            string titleString = File.ReadAllText("tile.xml");
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(titleString);
            return doc;
        }



        /// <summary>
        /// 在应用程序由最终用户正常启动时进行调用。
        /// 将在启动应用程序以打开特定文件等情况下使用。
        /// </summary>
        /// <param name="e">有关启动请求和过程的详细信息。</param>
        protected override async void OnLaunched(LaunchActivatedEventArgs e)
        {

            var storageFile = await
            Windows.Storage.StorageFile.GetFileFromApplicationUriAsync(new
            Uri("ms-appx:///VoiceCommands.xml"));



            await Windows.ApplicationModel.VoiceCommands.VoiceCommandDefinitionManager.
            InstallCommandDefinitionsFromStorageFileAsync(storageFile);

            Frame rootFrame = Window.Current.Content as Frame;

            // 不要在窗口已包含内容时重复应用程序初始化，
            // 只需确保窗口处于活动状态
            if (rootFrame == null)
            {
                // 创建要充当导航上下文的框架，并导航到第一页
                rootFrame = new Frame();

                rootFrame.NavigationFailed += OnNavigationFailed;

                if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    //TODO: 从之前挂起的应用程序加载状态
                }

                // 将框架放在当前窗口中
                Window.Current.Content = rootFrame;
            }

            if (e.PrelaunchActivated == false)
            {
                if (rootFrame.Content == null)
                {
                    // 当导航堆栈尚未还原时，导航到第一页，
                    // 并通过将所需信息作为导航参数传入来配置
                    // 参数
                    rootFrame.Navigate(typeof(MainPage), e.Arguments);
                }
                // 确保当前窗口处于活动状态
                Window.Current.Activate();
            }

            TileUpdateManager.CreateTileUpdaterForApplication().EnableNotificationQueue(true);

            Windows.UI.Core.SystemNavigationManager.GetForCurrentView().BackRequested += OnBackRequested;

        }

        /// <summary>
        /// 导航到特定页失败时调用
        /// </summary>
        ///<param name="sender">导航失败的框架</param>
        ///<param name="e">有关导航失败的详细信息</param>
        void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        /// <summary>
        /// 在将要挂起应用程序执行时调用。  在不知道应用程序
        /// 无需知道应用程序会被终止还是会恢复，
        /// 并让内存内容保持不变。
        /// </summary>
        /// <param name="sender">挂起的请求的源。</param>
        /// <param name="e">有关挂起请求的详细信息。</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            //TODO: 保存应用程序状态并停止任何后台活动
            deferral.Complete();
        }

        private void OnBackRequested(object sender, Windows.UI.Core.BackRequestedEventArgs e) {
            Frame rootFrame = Window.Current.Content as Frame;
            if (rootFrame == null)
                return;
            if (rootFrame.CanGoBack && e.Handled == false) {
                e.Handled = true;
                rootFrame.GoBack();
            }
        }
        private async Task InsertVoiceCommands()
        {
            await VoiceCommandDefinitionManager.InstallCommandDefinitionsFromStorageFileAsync(
            await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///VoiceCommands.xml")));
        }
        protected override void OnActivated(IActivatedEventArgs args)
        {
            base.OnActivated(args);
            // 如果程序不是因为语音命令而激活的，就不处理
            if (args.Kind != ActivationKind.VoiceCommand) return;

            //将参数转为语音指令事件对象
            var vcargs = (VoiceCommandActivatedEventArgs)args;
            // 分析被识别的命令
            var res = vcargs.Result;
            // 获取被识别的命令的名字
            var cmdName = res.RulePath[0];
            Type navType = null;
            string propertie = null;
            //判断用户使用的是哪种语音指令
            switch (cmdName)
            {
                case "OpenMainPage":
                    navType = typeof(MainPage);
                    break;
                default:
                    break;
            }
            //获取页面引用
            var root = Window.Current.Content as Frame;
            if (root == null)
            {
                root = new Frame();
                Window.Current.Content = root;
            }
            root.Navigate(navType, propertie);

            // 确保当前窗口处于活动状态
            Window.Current.Activate();
        }
    }
}
