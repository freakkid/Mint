using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace OurChat {
    class UserItem
    {

        public string username { get; set; }

        public string password { get; set; }

        public Uri avatarUri { get; set; }
        public ImageSource imageSource { get; set; }

        public UserItem(string username, string password, Uri avatarUri)
        {
            this.username = username;
            this.password = password;
            this.avatarUri = avatarUri;
            imageSource = new BitmapImage(avatarUri);
        }

    }
}
