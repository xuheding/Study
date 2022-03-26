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

namespace _2_窗口数据模型封装
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
 
        MainViewModel mainViewModel;//定义封装的对象
        public MainWindow()
        {
            InitializeComponent();
            mainViewModel = new MainViewModel(this);//实例化对象
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            mainViewModel.Value = "100";//设置对象Value的值为“100”
        }
    }
}
//但是这样子做还是有问题，因为对每个类，都要传入MainWindow对象，不太方便，需要数据绑定