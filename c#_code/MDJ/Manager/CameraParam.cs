using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.IO;
using MvCamCtrl.NET;
using System.Windows;
using Microsoft.Kinect;
using System.Windows.Media.Imaging;
using System.Windows.Media;

namespace MDJ
{

    static class CameraParam
    {
        enum TriggerMode
        {
            Off = 0,
            On = 1,
        };

        enum ExposureAutoMode
        {
            Off = 0,
            Once = 1,
            Continous = 2,
        };

        enum CameraStatus
        {
            Off = 0,
            On = 1
        };

        enum KinectStatus
        {
            Off = 0,
            On = 1
        };

        static string sn = null;//工业相机sn号（no use）
        static float exp = 2000;//工业相机曝光时间
        static float gain = 0;//工业相机增益
        static TriggerMode trigger = TriggerMode.Off;//工业相机触发模式
        static ExposureAutoMode exposureAuto = ExposureAutoMode.Off;//工业相机曝光模式


        static CameraStatus cameraStatus = CameraStatus.Off;//工业相机开闭状态
        public static MyCamera device = null;//创建工业相机对象
        static int nRet = -1;//工业相机错误码
        public static int width = 2048;
        public static int height = 1920;
        public static int channel = 3;
        public static int ROIx1, ROIy1, ROIx2, ROIy2 = -1;



        public static KinectSensor myKinect = null;//创建kinect对象
        static KinectStatus kinectStatus = KinectStatus.Off;//创建kinect对象
        public static int k_width = 640;//kinect对象的宽度
        public static int k_height = 480;//kinect对象的高度
        public static byte[] deepBackground;
        public static short[] depthDataShort;



        static public void CameraParamSetting(
            string expt = null,
            string gaint = null,
            string triggert = null,
            string auto = null)
        {
            if (expt != null)
                exp = Convert.ToSingle(expt);
            if (gaint != null)
                gain = Convert.ToSingle(gaint);
            if (triggert != null)
            {
                if (triggert == "On")
                {
                    trigger = TriggerMode.On;
                }
                else
                {
                    trigger = TriggerMode.Off;
                }
            }

            if (auto != null)
            {
                if (auto == "On")
                {
                    exposureAuto = ExposureAutoMode.Continous;
                }
                else
                {
                    exposureAuto = ExposureAutoMode.Off;
                }
            }

        }

        static public void kinectOpen()
        {
            int cnt = KinectSensor.KinectSensors.Count;
            if (cnt <= 0)
            {
                MessageBox.Show("请检查Kinect设备的连接", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                kinectStatus = KinectStatus.Off;
                return;
            }
            //kinect启动

            try
            {
                myKinect = KinectSensor.KinectSensors[0];
                //kinect启动
                myKinect.DepthStream.Enable(DepthImageFormat.Resolution640x480Fps30);
                myKinect.Start();
                k_width = myKinect.DepthStream.FrameWidth;
                k_height = myKinect.DepthStream.FrameHeight;

                MessageBox.Show("连接成功！");
                kinectStatus = KinectStatus.On;
            }
            catch
            {
                kinectStatus = KinectStatus.Off;
                MessageBox.Show("Kinect访问受限或未准备", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }

        static public void kinectBackgroundGrab(out byte[] depthData)
        {
            depthData = new byte[myKinect.DepthStream.FramePixelDataLength];
            using (DepthImageFrame newframe = myKinect.DepthStream.OpenNextFrame(10))
            {
                depthDataShort = new short[myKinect.DepthStream.FramePixelDataLength];
                newframe.CopyPixelDataTo(depthDataShort);
                for (int i = 0; i < depthDataShort.Length; i++)
                {
                    //depthData[i] = (byte)(255 - (depthDataShort[i] >> DepthImageFrame.PlayerIndexBitmaskWidth) * ((float)255 / (short.MaxValue / (Math.Pow(2, DepthImageFrame.PlayerIndexBitmaskWidth)))) / 0.7);
                    //depthData[i] = (byte)((depthDataShort[i] >> DepthImageFrame.PlayerIndexBitmaskWidth) % 255);
                    depthData[i] = (byte)((depthDataShort[i] >> (DepthImageFrame.PlayerIndexBitmaskWidth)) % 255);

                }
            }
            deepBackground = depthData;
        }

        static public int deepLoader(int x, int y)
        {



            int i0 = (y - 10) * CameraParam.k_width + x - 10;
            int i1 = (y - 10) * CameraParam.k_width + x;
            int i2 = (y - 10) * CameraParam.k_width + x + 10;
            int i3 = y * CameraParam.k_width + x - 10;
            int i4 = y * CameraParam.k_width + x;
            int i5 = y * CameraParam.k_width + x + 10;
            int i6 = (y + 10) * CameraParam.k_width + x - 10;
            int i7 = (y + 10) * CameraParam.k_width + x;
            int i8 = (y + 10) * CameraParam.k_width + x + 10;

            //int i = y * CameraParam.k_width + x;
            int[] deep = new int[21*21];
            using (DepthImageFrame newframe = myKinect.DepthStream.OpenNextFrame(10))
            {
                short[] depthDataTemp = new short[myKinect.DepthStream.FramePixelDataLength];
                newframe.CopyPixelDataTo(depthDataTemp);
                //deep[0] = ((depthDataShort[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i1] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i2] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i3] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i4] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i5] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i6] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i7] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    + (depthDataShort[i8] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth)
                //    )/9;
                for (int i = -10; i <= 10; i++)
                {
                    for (int j = -10; j <= 10; j++)
                    {
                        deep[(i+10)*21+(j+10)]= (depthDataShort[(y+i) * CameraParam.k_width + (x+j)] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[(y + i) * CameraParam.k_width + (x + j)] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                    }
                }

                //deep[0] = (depthDataShort[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i0] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[1] = (depthDataShort[i1] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i1] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[2] = (depthDataShort[i2] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i2] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[3] = (depthDataShort[i3] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i3] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[4] = (depthDataShort[i4] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i4] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[5] = (depthDataShort[i5] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i5] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[6] = (depthDataShort[i6] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i6] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[7] = (depthDataShort[i7] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i7] >> DepthImageFrame.PlayerIndexBitmaskWidth);
                //deep[8] = (depthDataShort[i8] >> DepthImageFrame.PlayerIndexBitmaskWidth) - (depthDataTemp[i8] >> DepthImageFrame.PlayerIndexBitmaskWidth);

                Array.Sort(deep);
            }
            if (deep[21 * 21/2] < 0)
            {
                return 0;
            }
            return deep[21 * 21 / 2];
        }



        static public void kinectGrab(out byte[] depthData)
        {
            depthData = new byte[myKinect.DepthStream.FramePixelDataLength];
            using (DepthImageFrame newframe = myKinect.DepthStream.OpenNextFrame(10))
            {
                short[] depthDataTemp = new short[myKinect.DepthStream.FramePixelDataLength];
                newframe.CopyPixelDataTo(depthDataTemp);
                for (int i = 0; i < depthDataTemp.Length; i++)
                {
                    depthData[i] = (byte)(255 - (depthDataTemp[i] >> DepthImageFrame.PlayerIndexBitmaskWidth) * ((float)255 / (short.MaxValue / (Math.Pow(2, DepthImageFrame.PlayerIndexBitmaskWidth)))) / 0.7);
                }
            }
        }



        static public void kinectClose()
        {
            if (kinectStatus == KinectStatus.Off)
            {
                return;
            }

            myKinect.Stop();
            kinectStatus = KinectStatus.Off;
        }



        static public void cameraOpen()
        {
            uint nTLayerType = MyCamera.MV_GIGE_DEVICE | MyCamera.MV_USB_DEVICE;
            MyCamera.MV_CC_DEVICE_INFO_LIST stDevList = new MyCamera.MV_CC_DEVICE_INFO_LIST();
            nRet = MyCamera.MV_CC_EnumDevices_NET(nTLayerType, ref stDevList);
            if (MyCamera.MV_OK != nRet)
            {
                MessageBox.Show("网口问题，可能是防火墙导致", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            Console.WriteLine("The number of devices found: " + Convert.ToString(stDevList.nDeviceNum));
            if (0 == stDevList.nDeviceNum)
            {
                MessageBox.Show("没有发现相机", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            MyCamera.MV_CC_DEVICE_INFO stDevInfo;
            stDevInfo = (MyCamera.MV_CC_DEVICE_INFO)Marshal.PtrToStructure(stDevList.pDeviceInfo[0], typeof(MyCamera.MV_CC_DEVICE_INFO));
            device = new MyCamera();

            nRet = device.MV_CC_CreateDevice_NET(ref stDevInfo);
            if (MyCamera.MV_OK != nRet)
            {
                MessageBox.Show("创建设备失败", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            //打开设备
            nRet = device.MV_CC_OpenDevice_NET(MyCamera.MV_ACCESS_Exclusive, 0);
            if (MyCamera.MV_OK != nRet)
            {
                MessageBox.Show("打开相机失败", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            cameraStatus = CameraStatus.On;
            MvCamCtrl.NET.MyCamera.MVCC_INTVALUE hv_height = new MvCamCtrl.NET.MyCamera.MVCC_INTVALUE();
            MvCamCtrl.NET.MyCamera.MVCC_INTVALUE hv_width = new MvCamCtrl.NET.MyCamera.MVCC_INTVALUE();
            MvCamCtrl.NET.MyCamera.MVCC_INTVALUE hv_channel = new MvCamCtrl.NET.MyCamera.MVCC_INTVALUE();


            nRet = device.MV_CC_GetIntValue_NET("WidthMax", ref hv_width);
            nRet = device.MV_CC_GetIntValue_NET("HeightMax", ref hv_height);
            nRet = device.MV_CC_GetIntValue_NET("DeviceStreamChannelCount", ref hv_channel);

            width = (int)hv_width.nCurValue;
            height = (int)hv_height.nCurValue;
            channel = (int)hv_channel.nCurValue;

            MessageBox.Show("打开相机成功");
            return;

        }


        static public void paramSetting()
        {
            if (cameraStatus == CameraStatus.Off)
            {
                MessageBox.Show("尚未连接到相机，请点击“相机连接”按钮", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            nRet = device.MV_CC_SetFloatValue_NET("ExposureTime", exp);
            nRet = device.MV_CC_SetFloatValue_NET("Gain", gain);
            nRet = device.MV_CC_SetEnumValue_NET("ExposureAuto", (uint)exposureAuto);
            nRet = device.MV_CC_SetIntValue_NET("AutoExposureTimeLowerLimit", 300);


            //nRet = device.MV_CC_SetEnumValue_NET("TriggerMode", (uint)trigger);

            if (MyCamera.MV_OK != nRet)
            {
                MessageBox.Show("数据格式错误", "参数写入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            //...其他处理


            MessageBox.Show("参数设定成功");
            return;

        }


        static public void cameraClose()
        {
            try
            {
                nRet = device.MV_CC_CloseDevice_NET();
                cameraStatus = CameraStatus.Off;
                if (MyCamera.MV_OK != nRet)
                {
                    Console.WriteLine("Close device failed{0:x8}", nRet);
                    return;
                }

                //销毁句柄，释放资源
                nRet = device.MV_CC_DestroyDevice_NET();
                if (MyCamera.MV_OK != nRet)
                {
                    Console.WriteLine("Destroy device failed:{0:x8}", nRet);
                }
            }
            catch
            {
                return;
            }

        }


        static public void getImage(out byte[] data)
        {
            data = null;
            if (cameraStatus == CameraStatus.Off)
            {
                MessageBox.Show("尚未连接到相机，请点击“相机连接”按钮", "相机载入错误", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            //开启抓图
            nRet = device.MV_CC_StartGrabbing_NET();
            if (MyCamera.MV_OK != nRet)
            {
                Console.WriteLine("Start grabbing failed:{0:x8}", nRet);
                return;
            }
            // ch:获取包大小 || en: Get Payload Size
            MyCamera.MVCC_INTVALUE stParam = new MyCamera.MVCC_INTVALUE();
            nRet = device.MV_CC_GetIntValue_NET("PayloadSize", ref stParam);
            if (MyCamera.MV_OK != nRet)
            {
                Console.WriteLine("Get PayloadSize failed:{0:x8}", nRet);
                return;
            }
            uint nBufSize = stParam.nCurValue;

            IntPtr pBufForDriver = Marshal.AllocHGlobal((int)nBufSize);
            uint nSaveSize = 1024 * 1024 * 60;//此处用户需要根据不同相机的分辨率自主分配内存大小
            IntPtr pBufForSave = Marshal.AllocHGlobal((int)nSaveSize);
            int nCount = 0;
            MyCamera.MV_FRAME_OUT_INFO_EX FrameInfo = new MyCamera.MV_FRAME_OUT_INFO_EX();



            int _maxCount = 1;
            if (exposureAuto == ExposureAutoMode.Continous)
            {
                _maxCount = 2;
            }


            while (nCount++ != _maxCount)
            {
                //获取一帧图像
                nRet = device.MV_CC_GetOneFrameTimeout_NET(pBufForDriver, nBufSize, ref FrameInfo, 2000);
                //device.MV_CC_GetOneFrameEx_NET(pBufForDriver, nBufSize, ref FrameInfo);
                //if (exposureAuto == ExposureAutoMode.Continous)
                //{
                //    MyCamera.MVCC_FLOATVALUE exposeTime = new MyCamera.MVCC_FLOATVALUE();
                //    nRet = device.MV_CC_GetFloatValue_NET("ExposureTime", ref exposeTime);
                //    exp = exposeTime.fCurValue;
                //    Console.WriteLine("exposetime:" + exp.ToString());
                //}

                if (MyCamera.MV_OK == nRet && nCount == _maxCount)
                {
                    MyCamera.MV_SAVE_IMAGE_PARAM_EX stSaveParam = new MyCamera.MV_SAVE_IMAGE_PARAM_EX();
                    stSaveParam.enImageType = MyCamera.MV_SAVE_IAMGE_TYPE.MV_Image_Bmp; stSaveParam.enPixelType = FrameInfo.enPixelType;
                    stSaveParam.pData = pBufForDriver;
                    stSaveParam.nDataLen = FrameInfo.nFrameLen;
                    stSaveParam.nHeight = FrameInfo.nHeight;
                    stSaveParam.nWidth = FrameInfo.nWidth;
                    stSaveParam.pImageBuffer = pBufForSave;
                    stSaveParam.nBufferSize = nSaveSize;
                    stSaveParam.nJpgQuality = 80;
                    nRet = device.MV_CC_SaveImageEx_NET(ref stSaveParam);
                    if (MyCamera.MV_OK != nRet)
                    {
                        Console.WriteLine("Save Image failed:{0:x8}", nRet);
                        continue;
                    }
                    // 将图像数据保存到本地文件                       
                    data = new byte[stSaveParam.nImageLen];
                    Marshal.Copy(pBufForSave, data, 0, (int)stSaveParam.nImageLen);
                    FileStream pFile = new FileStream("frame" + nCount.ToString() + ".bmp", FileMode.Create);
                    pFile.Write(data, 0, data.Length);
                    pFile.Close();
                }
                else
                {
                    Console.WriteLine("No data:{0:x8}", nRet);
                }
            }
            Marshal.FreeHGlobal(pBufForDriver);
            Marshal.FreeHGlobal(pBufForSave);

            //...其他处理
            //停止抓图
            nRet = device.MV_CC_StopGrabbing_NET();
            if (MyCamera.MV_OK != nRet)
            {
                Console.WriteLine("Stop grabbing failed{0:x8}", nRet);
                return;
            }
        }

    }
}
