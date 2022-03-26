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
using System.Windows.Shapes;
using HalconDotNet;




namespace MDJ
{
    /// <summary>
    /// Window1.xaml 的交互逻辑
    /// </summary>
    public partial class ShowWindow : Window
    {

        public delegate void TempSend(HTuple temp);
        public TempSend tempSend;
        public HTuple template = null;


        private string tempdir=null;

        public ShowWindow()
        {
            InitializeComponent();
        }

        private void halconGridLoaded(object sender, RoutedEventArgs e)
        {
            var Width = HalconGrid.ActualWidth;
        }

        private void loadButtonClick(object sender, EventArgs e)
        {
            System.Windows.Forms.OpenFileDialog openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            openFileDialog1.InitialDirectory = "D:\\";
            openFileDialog1.Filter = "pic files (*.png)|*.png|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                tempdir = openFileDialog1.FileName;
            }
            TemplateBuilder newTemp = new TemplateBuilder();
            if (tempdir == null)
            {
                MessageBox.Show("应先设置模板路径", "模板载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                if (tempdir.Split('.').Last() == "hobj")
                    HOperatorSet.ReadTuple(tempdir,out template);//TODO:轮廓信息没有保存
                else
                    template = newTemp.setTemplate(HalconWindow.HalconWindow, tempdir);
            }
        }


        private void resetButtonClick(object sender, EventArgs e)
        {
            TemplateBuilder newTemp = new TemplateBuilder();
            if (tempdir == null)
            {
                MessageBox.Show("应先设置模板路径", "模板载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
            }
            else
            {
                template = newTemp.setTemplate(HalconWindow.HalconWindow, tempdir);
            }
        }

        private void confirmButtonClick(object sender, EventArgs e)
        {
            tempSend(template);
            this.Close();
        }

        private void saveButtonClick(object sender, RoutedEventArgs e)
        {
            if (template == null)
                return;
            System.Windows.Forms.SaveFileDialog saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            saveFileDialog1.InitialDirectory = "D:\\";
            saveFileDialog1.Filter = "hobj files (*.hobj)|*.hobj";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;
            if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                tempdir = saveFileDialog1.FileName;
            }
            HOperatorSet.WriteTuple(template, tempdir);
        }

        private void loadButtonClick(object sender, RoutedEventArgs e)
        {

        }
    }
}
