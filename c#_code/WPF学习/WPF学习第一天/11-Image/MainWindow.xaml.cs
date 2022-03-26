using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _11_Image
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //1.相对路径
            //imgPic.Source = new BitmapImage(new Uri("img/1.jpg", UriKind.Relative));


            //绝对路径
            //2.WPF支持两种授权：application:///和siteforigin:///
            //pack URI方案 pack://授权/路径
            //授权 指定包含部件的程序包的类型，而路径 则指定不见在程序包中的位置
            //siteforigin 图片文件  生成:内容  application ---资源、内容
            //imgPic.Source = new BitmapImage(new Uri("pack://application:,,,/img/1.jpg", UriKind.Absolute));


            //3.
            imgPic.Source = new BitmapImage(new Uri(AppDomain.CurrentDomain.BaseDirectory + "img/1.jpg", UriKind.Absolute));//并且要设置图片属性，始终赋值,资源选择内容。这个会调用，bin_debug目录下图片
        }
    }
}
