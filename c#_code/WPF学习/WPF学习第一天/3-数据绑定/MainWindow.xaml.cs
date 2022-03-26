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
//事件驱动和数据驱动
//事件驱动：点击按钮这种
//数据驱动：通过值对窗体的更新


//数据绑定：
//1.首先在xaml文件中，添加绑定的变量
//2.在MainWindow()中添加this.DataContext给 绑定的变量所在的类
//3.对类   继承接口，实现接口，调用Invoke，使得变量更新到窗体中


//好处：
//以前，如果要换控件，那么后台的逻辑相应的部分都要重写，比较麻烦
//现在，可以通过属性绑定来实现，一个属性对应一种行为，只需要将属性绑定到控件上即可，这样就可以快速更换控件
namespace _3_数据绑定
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        MainViewModel mainViewModel=null;
        public MainWindow()
        {
            InitializeComponent();
            mainViewModel = new MainViewModel();
            this.DataContext = mainViewModel;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            mainViewModel.Value = "100";
        }
    }
}
