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
/// RadioButton（单选按钮）控件介绍
///     同一组单选按钮，它们是互斥关系
///     设置一个组名，不同组名的单选按钮，它们不具有互斥的关系
/// </summary>
namespace _9_RadioButton
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

        //对每个RadioButton都用这个方法来注册
        //调用的时候sender就是每个RadioButton对象，调用每个RadioButton各自的Content属性
        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
           
            MessageBox.Show((sender as RadioButton).Content.ToString());
        }

        //动态地添加控件
        //还可以在打开窗体后，再进行加载RadioButton (其他控件也可以采用这种方式)
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            //首先要找到它的父容器，所以首先要对Grid取一个Name
            //然后创建一个RadioButton对象，并赋值属性
            RadioButton rbtn = new RadioButton();
            rbtn.Content = "主任";
            rbtn.GroupName = "role";
            rbtn.IsChecked = false;
            rbtn.HorizontalAlignment = HorizontalAlignment.Left;
            rbtn.VerticalAlignment = VerticalAlignment.Top;
            rbtn.Margin = new Thickness(320, 101, 0, 0);

            //将RadioButton对象添加到父级的grid下面
            grid.Children.Add(rbtn);
        }
    }
}
