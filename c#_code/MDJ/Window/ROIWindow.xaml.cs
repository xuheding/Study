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
using HalconDotNet;


namespace MDJ
{
    /// <summary>
    /// ROIWindow.xaml 的交互逻辑
    /// </summary>
    public partial class ROIWindow : Window
    {
        ROIBuilder roiBuilder = new ROIBuilder();
        int ROIx1_, ROIy1_, ROIx2_, ROIy2_ = -1;

        public ROIWindow()
        {
            InitializeComponent();
            ROIx1_ = CameraParam.ROIx1;
            ROIy1_ = CameraParam.ROIy1;
            ROIx2_ = CameraParam.ROIx2;
            ROIy2_ = CameraParam.ROIy2;
        }

        private void loadButtonClick(object sender, RoutedEventArgs e)
        {
            roiBuilder.setROI(HalconWindow.HalconWindow, out ROIx1_, out ROIy1_, out ROIx2_, out ROIy2_);
        }

        private void resetButtonClick(object sender, RoutedEventArgs e)
        {
            ROIx1_ = -1;
            ROIy1_ = -1;
            ROIx2_ = -1;
            ROIy2_ = -1;
            MessageBox.Show("ROI已清除");
        }

        private void confirmButtonClick(object sender, RoutedEventArgs e)
        {
            CameraParam.ROIx1 = ROIx1_;
            CameraParam.ROIy1 = ROIy1_;
            CameraParam.ROIx2 = ROIx2_;
            CameraParam.ROIy2 = ROIy2_;
            //把ROI信息传递给CameraParam全局类
            this.Close();
        }
    }
}
