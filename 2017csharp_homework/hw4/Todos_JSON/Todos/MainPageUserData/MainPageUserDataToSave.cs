using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;

namespace Todos.MainPageUserData
{
    public class MainPageUserDataToSave
    {
        public bool? upCheckBox;
        public Visibility upLine;
        public bool? downCheckBox;
        public Visibility downLine;

        public MainPageUserDataToSave(bool? upcheckbox, Visibility upline, bool? downcheckbox, Visibility downline)
        {
            upCheckBox = upcheckbox;
            upLine = upline;
            downCheckBox = downcheckbox;
            downLine = downline;
        }

        public string SerializeUserData()
        {
            return JsonConvert.SerializeObject(this);
        }

        public static MainPageUserDataToSave DeserializeUserData(object serializeComposite)
        {
            return JsonConvert.DeserializeObject<MainPageUserDataToSave>(serializeComposite.ToString());
        }
    }
}
