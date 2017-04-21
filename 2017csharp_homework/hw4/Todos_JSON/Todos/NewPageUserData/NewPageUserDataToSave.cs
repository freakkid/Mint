using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Media;

namespace Todos.NewPageUserData
{
    class NewPageUserDataToSave
    {
        public string titleTextBox;
        public string detailsTextBox;
        public ImageSource image;
        public DateTimeOffset datePicker;

        public NewPageUserDataToSave(string titletextbox, string detailstextbox, ImageSource t_image, DateTimeOffset datapicker)
        {
            titleTextBox = titletextbox;
            detailsTextBox = detailstextbox;
            // image = t_image;
            datePicker = datapicker;
        }

        public string SerializeUserData()
        {
            return JsonConvert.SerializeObject(this);
        }

        public static NewPageUserDataToSave DeserializeUserData(object serializeComposite)
        {
            return JsonConvert.DeserializeObject<NewPageUserDataToSave>(serializeComposite.ToString());
        }
    }
}
