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

namespace _10_CheckBox
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
            //MessaeBox.Show(ChkSport.IsChecked.ToString());

            //获取窗口中所有勾选的CheckBox的Content
            string strContents = "";
            foreach (UIElement ele in grid1.Children)
            {
                if (ele is CheckBox)
                {
                    CheckBox chk = ele as CheckBox;
                    if (chk.IsChecked == true)
                    {
                        if (strContents != "")
                        {
                            strContents += ".";
                        }
                        strContents += chk.Content.ToString();
                    }
                }
            }
            MessageBox.Show(strContents);

        
        }


        private void Btn_Click(object sender, RoutedEventArgs e)
        {   
            //在窗体中用程序添加CheckBox
            string[] names = { "体育1", "唱歌1", "跳舞1", "绘画1" };
            for (int i = 0; i < names.Length; i++)
            {
                CheckBox chk = new CheckBox();
                chk.Content = names[i];
                chk.HorizontalAlignment = HorizontalAlignment.Left;
                chk.VerticalAlignment = VerticalAlignment.Top;
                chk.Margin = new Thickness(40 + i * 80, 60, 0, 0);
                grid1.Children.Add(chk);
            }
        }
    }
}
