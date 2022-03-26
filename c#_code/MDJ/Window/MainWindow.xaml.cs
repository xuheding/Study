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
using System.IO;
using System.Drawing;
using HalconDotNet;
using System.Collections.ObjectModel;


namespace MDJ
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private static ObservableCollection<PointData> List = new ObservableCollection<PointData>();
        WriteableBitmap wbm;
        Core core = null;


        public void tempRecevie(HTuple temp)
        {
            core = new Core();
            core.BrickTemplate = temp;
        }

        public MainWindow()
        {
            InitializeComponent();
            UserList.ItemsSource = List;
            List.Clear();
        }

        public void startLoading()
        {
            
        }

        private void resetImage()
        {
            wbm = new WriteableBitmap(3072, 2048, 96, 96, PixelFormats.Rgb24, null);
            img1.Source = wbm;
        }


        private void backgroundButtonClick(object sender, RoutedEventArgs e)
        {
            BackgroundWindow window = new BackgroundWindow();
            window.Show();
        }


        private void brickButtonClick(object sender, RoutedEventArgs e)
        {
            ShowWindow window = new ShowWindow();
            window.tempSend = tempRecevie;
            window.Show();
        }


        private void CamParamButtonClick(object sender, RoutedEventArgs e)
        {
            CameraSetting window = new CameraSetting();
            window.Show();
        }


        private void testButtonClick(object sender, RoutedEventArgs e)
        {
            if (core == null)
            {
                MessageBox.Show("应先设置模板", "模板载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            if (CameraParam.device == null)
            {
                MessageBox.Show("应先连接上工业相机", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            if (CameraParam.myKinect == null)
            {
                MessageBox.Show("应先连接上kinect相机", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            byte[] bytes;
            CameraParam.getImage(out bytes);

            HObject ho_showImage;
            HOperatorSet.GenEmptyObj(out ho_showImage);
            HObject ho_Image;
            HOperatorSet.GenEmptyObj(out ho_Image);

            if (CameraParam.channel == 1)
            {
                ho_Image = Image.Bytes2HObject(bytes.Where((num, index) => index > 1077).ToArray(), CameraParam.width, CameraParam.height);
                core.param2d(ref List, ho_Image, out ho_showImage);
                ho_Image.Dispose();
            }
            else
            {
                core.param2d(ref List, Image.Bytes2HObject3(bytes, CameraParam.width, CameraParam.height), out ho_showImage);
            }

            ImageBytes image = Image.HObject2Bytes3(ho_showImage);

            resetImage();
            Global.writeImage(wbm, new Int32Rect(0, 0, CameraParam.width, CameraParam.height), image.bytes, CameraParam.width * 3);
            ho_showImage.Dispose();
            ho_Image.Dispose();
        }

        private void startButtonClick(object sender, RoutedEventArgs e)
        {
            if (core == null)
            {
                MessageBox.Show("应先设置模板", "模板载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            if (CameraParam.device == null)
            {
                MessageBox.Show("应先连接上工业相机", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            if (CameraParam.myKinect == null)
            {
                MessageBox.Show("应先连接上kinect相机", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            byte[] bytes;
            CameraParam.getImage(out bytes);
            HObject ho_showImage;
            HObject ho_Image;
            HOperatorSet.GenEmptyObj(out ho_showImage);
            HOperatorSet.GenEmptyObj(out ho_Image);
            if (CameraParam.channel == 1)
            {
                ho_Image = Image.Bytes2HObject(bytes.Where((num, index) => index > 1077).ToArray(), CameraParam.width, CameraParam.height);
                core.param2d(ref List, ho_Image, out ho_showImage);
                ho_Image.Dispose();
            }
            else
            {
                core.param2d(ref List, Image.Bytes2HObject3(bytes, CameraParam.width, CameraParam.height), out ho_showImage);
            }
            ImageBytes image = Image.HObject2Bytes3(ho_showImage);
            resetImage();
            Global.writeImage(wbm, new Int32Rect(0, 0, CameraParam.width, CameraParam.height), image.bytes, CameraParam.width * 3);
            ho_showImage.Dispose();
            ho_Image.Dispose();
        }

        private void stopButtonClick(object sender, RoutedEventArgs e)
        {
            CameraParam.cameraClose();
            CameraParam.kinectClose();
        }

        private void mainWindowClosed(object sender, EventArgs e)
        {
            CameraParam.cameraClose();
            CameraParam.kinectClose();
            Application.Current.Shutdown();
        }

        private void DecParamButtonClick(object sender, RoutedEventArgs e)
        {
            DetectSetting window = new DetectSetting();
            window.Show();
        }

        private void HelpButtonClick(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process proc = new System.Diagnostics.Process();
            proc.StartInfo.FileName = "https://www.showdoc.cc/p/96bb22fd4f8f5d817070b6635cd3037a";
            proc.Start();
        }
    }
}
