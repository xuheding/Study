using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace MDJ
{
    /// <summary>
    /// CameraSetting.xaml 的交互逻辑
    /// </summary>
    public partial class CameraSetting : Window
    {

        public CameraSetting()
        {
            InitializeComponent();

        }



        private void cameraOpen(object sender, RoutedEventArgs e)
        {

            CameraParam.CameraParamSetting(Exp.Text, Gin.Text, Trig.Text, Auto.Text);
            CameraParam.cameraOpen();

        }

        private void paramSetting(object sender, RoutedEventArgs e)
        {
            CameraParam.CameraParamSetting(Exp.Text, Gin.Text, Trig.Text, Auto.Text);

            CameraParam.paramSetting();
        }



        private void cameraClose(object sender, RoutedEventArgs e)
        {
            CameraParam.cameraClose();
        }

        private void ROISetting(object sender, RoutedEventArgs e)
        {
            if (CameraParam.device == null)
            {
                MessageBox.Show("相机载入错误");
                return;
            }
            ROIWindow roiWindow = new ROIWindow();
            roiWindow.Show();
        }
    }
}
