using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.UI.Popups;
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
        private bool isVedio = false; // 判断正在播放的文件的类型
        public MainPage()
        {
            this.InitializeComponent();
            media.AutoPlay = false;  // 程序刚启动不能自动播放
            isVedio = false;        // 默认播放Assets中的音频文件
            CommandBar.ClosedDisplayMode = AppBarClosedDisplayMode.Compact;  // 显示控制栏的按钮
            media.Volume = 0.2;     // 默认音量
        }

        private void Play_Click(object sender, RoutedEventArgs e)
        {
            media.Play();
            if (!isVedio)
            {
                Storyborad.Begin();
            }
            else   // 如果是视频文件，则停止播放动画，避免不必要的cpu消耗
            {
                Storyborad.Stop();
            }

        }

        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            media.Stop();
            Storyborad.Stop();
        }

        private void Pause_Click(object sender, RoutedEventArgs e)
        {
            media.Pause();
            if (!isVedio)
            {
                Storyborad.Pause();
            }
        }

        private void FullScreen_Click(object sender, RoutedEventArgs e)
        {
            media.IsFullWindow = !media.IsFullWindow;
            // 播放视频且全屏，最小化控制面板的按钮，避免挡住视频影响用户体验
            if (media.IsFullWindow && isVedio)
            {
                CommandBar.ClosedDisplayMode = AppBarClosedDisplayMode.Minimal;
            }
            else
            {
                CommandBar.ClosedDisplayMode = AppBarClosedDisplayMode.Compact;
            }
        }

        private async void SelectFile_Click(object sender, RoutedEventArgs e)
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.ViewMode = PickerViewMode.Thumbnail;
            picker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            addPickerType(picker);

            StorageFile file = await picker.PickSingleFileAsync();

            if (file != null)
            {
                changeMediaFile(file);
            }
        }

        private void addPickerType(FileOpenPicker picker)
        {
            picker.FileTypeFilter.Add(".wmv");
            picker.FileTypeFilter.Add(".mp3");
            picker.FileTypeFilter.Add(".mp4");
            picker.FileTypeFilter.Add(".wma");
            picker.FileTypeFilter.Add(".mkv");
        }

        private async void changeMediaFile(StorageFile file)
        {
            var fileStream = await file.OpenAsync(FileAccessMode.Read);
            media.SetSource(fileStream, file.ContentType);
            media.AutoPlay = true;    // 用户选择一个文件后即可自动播放，无需点击Play
            // 如果媒体文件为视频文件
            if (isVedioFile(file.FileType))
            {
                isVedio = true;
                // 如果是播放视频且全屏播放，则最小化控制面板的按钮，控制面板按钮避免挡住视频影响用户体验
                if (media.IsFullWindow)
                {
                    CommandBar.ClosedDisplayMode = AppBarClosedDisplayMode.Minimal;
                }
            }
            else
            {
                isVedio = false;
                CommandBar.ClosedDisplayMode = AppBarClosedDisplayMode.Compact;
            }
        }

        // 根据文件后缀名判断文件是否是视频文件
        private bool isVedioFile(string fileType)
        {
            return fileType == ".mp4" || fileType == ".wmv" || fileType == ".mkv";
        }


        private void media_MediaOpened(object sender, RoutedEventArgs e)
        {
            // 设置进度条长度与媒体文件播放长度一致
            mediaSlider.Maximum = media.NaturalDuration.TimeSpan.TotalSeconds;
            // 设置进度条的值，从0开始 
            mediaSlider.Value = 0;
        }

        private void media_MediaEnded(object sender, RoutedEventArgs e)
        {
            // 文件播放结束后，可以自动重新播放，即单曲循环模式
            media.Play();
        }

        // 播放媒体文件失败，弹出消息框提示用户
        private void media_MediaFailed(object sender, ExceptionRoutedEventArgs e)
        {
            var i = new MessageDialog("Sorry, unable to play!").ShowAsync();
        }

    }
}
