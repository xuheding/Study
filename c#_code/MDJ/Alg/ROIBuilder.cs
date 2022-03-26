using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using HalconDotNet;



namespace MDJ
{
    class ROIBuilder
    {
        public HTuple hv_ExpDefaultWinHandle;

        // Main procedure 
        private void action(out int ROIx1, out int ROIy1, out int ROIx2, out int ROIy2)
        {


            // Local iconic variables 

            HObject ho_Image, ho_ImageMedian, ho_ho_Rectangle;

            // Local control variables 

            HTuple hv_Width = null, hv_Height = null, hv_WindowHandle = new HTuple();
            HTuple hv_Row1 = null, hv_Column1 = null, hv_Row2 = null;
            HTuple hv_Column2 = null;
            // Initialize local and output iconic variables 
            HOperatorSet.GenEmptyObj(out ho_Image);
            HOperatorSet.GenEmptyObj(out ho_ImageMedian);
            HOperatorSet.GenEmptyObj(out ho_ho_Rectangle);
            ho_Image.Dispose();

            //HOperatorSet.ReadImage(out ho_Image, "D:/LabWork/Brick/dataset/2019_10_24/Image_20190926102120238.jpg");
            byte[] bytes;
            CameraParam.getImage(out bytes);

            if (CameraParam.channel == 1)
            {
                ho_Image = Image.Bytes2HObject(bytes.Where((num, index) => index > 1077).ToArray(), CameraParam.width, CameraParam.height);
            }
            else
            {
                ho_Image = Image.Bytes2HObject3(bytes, CameraParam.width, CameraParam.height);
            }

            ho_ImageMedian.Dispose();
            HOperatorSet.MedianImage(ho_Image, out ho_ImageMedian, "circle", 10, "mirrored");


            HOperatorSet.GetImageSize(ho_ImageMedian, out hv_Width, out hv_Height);
            //dev_open_window(...);
            HOperatorSet.DispObj(ho_ImageMedian, hv_ExpDefaultWinHandle);


            HOperatorSet.DrawRectangle1(hv_ExpDefaultWinHandle, out hv_Row1, out hv_Column1,
                out hv_Row2, out hv_Column2);
            ho_ho_Rectangle.Dispose();
            HOperatorSet.GenRectangle1(out ho_ho_Rectangle, hv_Row1, hv_Column1, hv_Row2,
                hv_Column2);
            HOperatorSet.DispObj(ho_ho_Rectangle, hv_ExpDefaultWinHandle);

            ROIx1 = (int)hv_Column1.D;
            ROIy1 = (int)hv_Row1.D;
            ROIx2 = (int)hv_Column2.D;
            ROIy2 = (int)hv_Row2.D;

            ho_Image.Dispose();
            ho_ImageMedian.Dispose();
            ho_ho_Rectangle.Dispose();

        }

        public void InitHalcon()
        {
            // Default settings used in HDevelop 
            HOperatorSet.SetSystem("width", 512);
            HOperatorSet.SetSystem("height", 512);
        }

        public void setROI(HTuple Window, out int ROIx1, out int ROIy1, out int ROIx2, out int ROIy2)
        {
            hv_ExpDefaultWinHandle = Window;
            action(out ROIx1, out ROIy1, out ROIx2, out ROIy2);
        }



    }
}
