using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
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
    /// BackgroundWindow.xaml 的交互逻辑
    /// </summary>
    public partial class BackgroundWindow : Window
    {

        byte[] depthData;


        public BackgroundWindow()
        {
            InitializeComponent();
        }

        private void kinectLinkClick(object sender, RoutedEventArgs e)
        {
            CameraParam.kinectOpen();
        }

        private void backgroundLoadClick(object sender, RoutedEventArgs e)
        {

        }

        private void confirmButtonClick(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        public static Bitmap ToGrayBitmap(byte[] rawValues, int width, int height)
        {
            Bitmap bmp = new Bitmap(width, height, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);
            BitmapData bmpData = bmp.LockBits(new System.Drawing.Rectangle(0, 0, width, height),
             ImageLockMode.WriteOnly, System.Drawing.Imaging.PixelFormat.Format8bppIndexed);

            int stride = bmpData.Stride;
            int offset = stride - width;
            IntPtr iptr = bmpData.Scan0;
            int scanBytes = stride * height;

            int posScan = 0, posReal = 0;
            byte[] pixelValues = new byte[scanBytes];

            for (int x = 0; x < height; x++)
            {
                for (int y = 0; y < width; y++)
                {
                    pixelValues[posScan++] = rawValues[posReal++];
                }
                posScan += offset;
            }

            System.Runtime.InteropServices.Marshal.Copy(pixelValues, 0, iptr, scanBytes);
            bmp.UnlockBits(bmpData);

            ColorPalette tempPalette;
            using (Bitmap tempBmp = new Bitmap(1, 1, System.Drawing.Imaging.PixelFormat.Format8bppIndexed))
            {
                tempPalette = tempBmp.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                tempPalette.Entries[i] = System.Drawing.Color.FromArgb(i, i, i);
            }

            bmp.Palette = tempPalette;

            return bmp;

        }

        private void realtimeGrabClick(object sender, RoutedEventArgs e)
        {
            if (CameraParam.myKinect == null)
            {
                MessageBox.Show("请先连接上Kinect设备", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                depthData = null;
                return;
            }

            CameraParam.kinectBackgroundGrab(out depthData);

            kinectVideo.Source = BitmapSource.Create(CameraParam.k_width, CameraParam.k_height, // image dimensions
                                96, 96, // resolution - 96 dpi for video frames
                                PixelFormats.Gray8, // video format
                                null, // palette - none
                                depthData, // video data
                                CameraParam.k_width  // stride
                                );
            Bitmap saveImage = ToGrayBitmap(depthData, CameraParam.k_width, CameraParam.k_height);
            saveImage.Save("realtime.png");

            MessageBox.Show("图片已设置为背景并保存至根目录下");
        }
    }
}
