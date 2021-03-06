﻿#pragma checksum "D:\Workplace\Mint\2017现代操作系统\期中项目\OurChat\OurChat\ChatPage.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "4896BA80F97DDD7E41653CC5CC17A529"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace OurChat
{
    partial class ChatPage : 
        global::Windows.UI.Xaml.Controls.Page, 
        global::Windows.UI.Xaml.Markup.IComponentConnector,
        global::Windows.UI.Xaml.Markup.IComponentConnector2
    {
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks"," 14.0.0.0")]
        private static class XamlBindingSetters
        {
            public static void Set_Windows_UI_Xaml_Controls_ItemsControl_ItemsSource(global::Windows.UI.Xaml.Controls.ItemsControl obj, global::System.Object value, string targetNullValue)
            {
                if (value == null && targetNullValue != null)
                {
                    value = (global::System.Object) global::Windows.UI.Xaml.Markup.XamlBindingHelper.ConvertValue(typeof(global::System.Object), targetNullValue);
                }
                obj.ItemsSource = value;
            }
        };

        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks"," 14.0.0.0")]
        private class ChatPage_obj1_Bindings :
            global::Windows.UI.Xaml.Markup.IComponentConnector,
            IChatPage_Bindings
        {
            private global::OurChat.ChatPage dataRoot;
            private bool initialized = false;
            private const int NOT_PHASED = (1 << 31);
            private const int DATA_CHANGED = (1 << 30);

            // Fields for each control that has bindings.
            private global::Windows.UI.Xaml.Controls.ListView obj5;

            public ChatPage_obj1_Bindings()
            {
            }

            // IComponentConnector

            public void Connect(int connectionId, global::System.Object target)
            {
                switch(connectionId)
                {
                    case 5:
                        this.obj5 = (global::Windows.UI.Xaml.Controls.ListView)target;
                        break;
                    default:
                        break;
                }
            }

            // IChatPage_Bindings

            public void Initialize()
            {
                if (!this.initialized)
                {
                    this.Update();
                }
            }
            
            public void Update()
            {
                this.Update_(this.dataRoot, NOT_PHASED);
                this.initialized = true;
            }

            public void StopTracking()
            {
            }

            public bool SetDataRoot(global::System.Object newDataRoot)
            {
                if (newDataRoot != null)
                {
                    this.dataRoot = (global::OurChat.ChatPage)newDataRoot;
                    return true;
                }
                return false;
            }

            public void Loading(global::Windows.UI.Xaml.FrameworkElement src, object data)
            {
                this.Initialize();
            }

            // Update methods for each path node used in binding steps.
            private void Update_(global::OurChat.ChatPage obj, int phase)
            {
                if (obj != null)
                {
                    if ((phase & (NOT_PHASED | (1 << 0))) != 0)
                    {
                        this.Update_content(obj.content, phase);
                    }
                }
            }
            private void Update_content(global::System.Collections.ObjectModel.ObservableCollection<global::OurChat.Content> obj, int phase)
            {
                if ((phase & ((1 << 0) | NOT_PHASED )) != 0)
                {
                    XamlBindingSetters.Set_Windows_UI_Xaml_Controls_ItemsControl_ItemsSource(this.obj5, obj, null);
                }
            }
        }
        /// <summary>
        /// Connect()
        /// </summary>
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks"," 14.0.0.0")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void Connect(int connectionId, object target)
        {
            switch(connectionId)
            {
            case 2:
                {
                    this.voice = (global::Windows.UI.Xaml.Controls.Button)(target);
                    #line 56 "..\..\..\ChatPage.xaml"
                    ((global::Windows.UI.Xaml.Controls.Button)this.voice).Click += this.voice_Click;
                    #line default
                }
                break;
            case 3:
                {
                    this.send_text = (global::Windows.UI.Xaml.Controls.TextBox)(target);
                }
                break;
            case 4:
                {
                    this.send = (global::Windows.UI.Xaml.Controls.Button)(target);
                    #line 60 "..\..\..\ChatPage.xaml"
                    ((global::Windows.UI.Xaml.Controls.Button)this.send).Click += this.Send_OnClick;
                    #line default
                }
                break;
            case 6:
                {
                    global::Windows.UI.Xaml.Controls.ItemsStackPanel element6 = (global::Windows.UI.Xaml.Controls.ItemsStackPanel)(target);
                    #line 35 "..\..\..\ChatPage.xaml"
                    ((global::Windows.UI.Xaml.Controls.ItemsStackPanel)element6).RightTapped += this.ItemsStackPanel_RightTapped;
                    #line default
                }
                break;
            case 7:
                {
                    this.clear = (global::Windows.UI.Xaml.Controls.AppBarButton)(target);
                    #line 18 "..\..\..\ChatPage.xaml"
                    ((global::Windows.UI.Xaml.Controls.AppBarButton)this.clear).Click += this.clear_Click;
                    #line default
                }
                break;
            case 8:
                {
                    this.disconnect = (global::Windows.UI.Xaml.Controls.AppBarButton)(target);
                    #line 19 "..\..\..\ChatPage.xaml"
                    ((global::Windows.UI.Xaml.Controls.AppBarButton)this.disconnect).Click += this.disconnect_Click;
                    #line default
                }
                break;
            default:
                break;
            }
            this._contentLoaded = true;
        }

        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks"," 14.0.0.0")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public global::Windows.UI.Xaml.Markup.IComponentConnector GetBindingConnector(int connectionId, object target)
        {
            global::Windows.UI.Xaml.Markup.IComponentConnector returnValue = null;
            switch(connectionId)
            {
            case 1:
                {
                    global::Windows.UI.Xaml.Controls.Page element1 = (global::Windows.UI.Xaml.Controls.Page)target;
                    ChatPage_obj1_Bindings bindings = new ChatPage_obj1_Bindings();
                    returnValue = bindings;
                    bindings.SetDataRoot(this);
                    this.Bindings = bindings;
                    element1.Loading += bindings.Loading;
                }
                break;
            }
            return returnValue;
        }
    }
}

