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

/// <summary>
/// 
/// app.config 配置文件 连接字符串 配置信息
/// App.xaml 设置应用程序起始文件，系统级资源
/// MainWindow.xaml.cs  Window---WPF应用程序界面与Xaml设计文件
/// MainWindow.xaml.cs  --xaml 窗口文件的后台代码文件
/// 
/// StartupUri="MainWindow.xaml"指定起始文件
/// <Application.Resources> 定义整个WPF应用程序的相关资源
/// 
/// 一个xaml文件至少要有连个命名控件 1.默认命名控件 2.带x前缀
/// </summary>
namespace _6_WPF应用程序组成和APP
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
    }
}
