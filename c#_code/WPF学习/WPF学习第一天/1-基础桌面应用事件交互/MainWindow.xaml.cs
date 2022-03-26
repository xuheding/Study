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

namespace _1_基础桌面应用事件交互
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //业务逻辑  -》计算数据  -》 数据结果显示  -》设置数据状态


            //首先对文本框命名为tbName
            //可以在xaml的windows下输入FontSize设置字体

            this.tbName.Text = "100";
            string usrName = this.tbName.Text;
            if (usrName == "100")
            {
                this.tbName.Foreground = Brushes.Orange;//将文本框的前景色设置为橘黄色
                MessageBox.Show("登录成功");
            }
        }
    }
}
