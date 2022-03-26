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
/// 可以在xaml的window下 输入FontSize可以设置字体
/// </summary>
namespace WPFNET5
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //MainViewModel mainViewModel = null;
        public MainWindow()
        {
            InitializeComponent();
            //mainViewModel = new MainViewModel(this);
            this.DataContext = new MainViewModel();//这句话的意思，就是让我们从这个新的对象里面去找绑定的数据
        }


        ////但是这样写又影响整体结构,我们把它写到单独的一类中去，利用面向对象的思想
        //private string _value;
        //public string Value 
        //{
        //    get 
        //    {
        //        return _value;
        //    }
        //    set   //直接在属性里面进行封装，下面只需要调用this.Value=100即可
        //    {
        //        _value = value;
        //        this.tbName.Text = value;
        //        if (value == "100")
        //        {
        //            this.tbName.Foreground = Brushes.Orange;
        //        }

        //    } 
        //}//可以输入prop+2次Tab，快速输出代码片段

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //业务逻辑  -》计算数据  -》 数据结果显示  -》设置数据状态

            //MessageBox.Show("Hello");  
            //this.tbName.Text = "Jovan";


            //string value = "100";
            //this.tbName.Text = value;
            //string usrName = this.tbName.Text;
            //if (usrName == "100")
            //{
            //    this.tbName.Foreground = Brushes.Orange;//把TextBox的前景色（字体）变成橘黄色
            //    MessageBox.Show("确认通过");
            //}


            //this.Value = "100";
            //mainViewModel.Value = "100";

        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
