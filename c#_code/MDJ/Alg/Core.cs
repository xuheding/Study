using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using HalconDotNet;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Drawing.Imaging;

namespace MDJ
{
    class Core
    {
        public HTuple BrickTemplate = null;

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


        public void param2d(ref ObservableCollection<PointData> List, HObject src, out HObject outImage)
        /*
        param:
        ref ObservableCollection<PointData> List:传入的显示层表格句柄，用于结果输出
        HObject src：即时采集得到的工业相机图像
        out HObject outImage：用于结果演示的图像
        */
        {
            HObject ho_ModelContours, ho_testImage, ho_testImageMedian, ho_greenTestImageMedian;
            HObject ho_ModelTrans = null;
            HObject ho_UnionContours = null;
            HObject ho_Region = null;

            // Local control variables 

            HTuple hv_WindowHandle = new HTuple();
            HTuple hv_Row2 = null, hv_model = BrickTemplate;
            HTuple hv_Column2 = null;

            HTuple hv_Angle = null, hv_Scale = null, hv_Score = null;
            HTuple hv_I = null, hv_HomMat2DIdentity = new HTuple();
            HTuple hv_HomMat2DTranslate = new HTuple(), hv_HomMat2DRotate = new HTuple();
            HTuple hv_HomMat2DScale = new HTuple(), hv_PointerRed = new HTuple();
            HTuple hv_PointerGreen = new HTuple(), hv_PointerBlue = new HTuple();
            HTuple hv_Type = new HTuple(), hv_Width1 = new HTuple();
            HTuple hv_Height1 = new HTuple();
            // Initialize local and output iconic variables 
            HOperatorSet.GenEmptyObj(out ho_UnionContours);
            HOperatorSet.GenEmptyObj(out ho_Region);
            HOperatorSet.GenEmptyObj(out ho_greenTestImageMedian);

            HOperatorSet.GenEmptyObj(out ho_ModelContours);
            HOperatorSet.GenEmptyObj(out ho_testImage);
            HOperatorSet.GenEmptyObj(out ho_testImageMedian);
            HOperatorSet.GenEmptyObj(out ho_ModelTrans);
            HOperatorSet.GetShapeModelContours(out ho_ModelContours, BrickTemplate, 1);
            HOperatorSet.Rgb1ToGray(src, out ho_testImage);//TODO test

            //byte[] deepmap;
            //CameraParam.kinectGrab(out deepmap);

            HOperatorSet.MedianImage(ho_testImage, out ho_testImageMedian, "circle", 3,
                "mirrored");
            HOperatorSet.FindScaledShapeModel(ho_testImageMedian, BrickTemplate, (new HTuple(-180)).TupleRad()
                , (new HTuple(360)).TupleRad(), 0.8, 1.5, Global.detectAcc, 5, 0.5, "least_squares", 5,
                0.8, out hv_Row2, out hv_Column2, out hv_Angle, out hv_Scale, out hv_Score);
            HOperatorSet.CopyImage(ho_testImageMedian, out ho_greenTestImageMedian);

            List.Clear();


            //for (int i = 0; i < deepmap.Length; i++)
            //{
            //    if (deepmap[i] >= 250 || (CameraParam.deepBackground)[i] >= 250)
            //        deepmap[i] = 255;
            //    else
            //        deepmap[i] = (byte)Math.Max(0, deepmap[i] - (CameraParam.deepBackground)[i]);
            //}


            //Bitmap saveImage = ToGrayBitmap(deepmap, CameraParam.k_width, CameraParam.k_height);
            //saveImage.Save("realtime2.png");


            for (hv_I = 0; (int)hv_I <= (int)((new HTuple(hv_Score.TupleLength())) - 1); hv_I = (int)hv_I + 1)
            {
                if (CameraParam.ROIx1!=-1&& CameraParam.ROIx2 != -1 && CameraParam.ROIy1 != -1 && CameraParam.ROIy2 != -1)
                {
                    if (hv_Column2[hv_I].D < CameraParam.ROIx1 || hv_Column2[hv_I].D > CameraParam.ROIx2 ||
                        hv_Row2[hv_I].D < CameraParam.ROIy1 || hv_Row2[hv_I].D > CameraParam.ROIy2)
                        continue;
                }

                /*一号机*/
                //double ord = 7.09951505e-06 * hv_Column2[hv_I].D + 8.19850479e-06 * (CameraParam.height - hv_Row2[hv_I].D) + 1.00000000e+00;//TODO:变换矩阵的硬编码
                //double newy = (7.93161488e-04 * hv_Column2[hv_I].D + 2.43820992e-01 * (CameraParam.height - hv_Row2[hv_I].D) - 1.70155575e+01) / ord;
                //double newx = (-2.37869618e-01 * hv_Column2[hv_I].D + 1.23898976e-03 * (CameraParam.height - hv_Row2[hv_I].D) + 6.55736062e+02) / ord;

                /*二号机*/
                //double ord = 4.94865660e-06 * hv_Column2[hv_I].D - 4.72544516e-06 * (CameraParam.height - hv_Row2[hv_I].D) + 1.00000000e+00;//TODO:变换矩阵的硬编码
                //double newy = (-1.39250876e-03 * hv_Column2[hv_I].D - 1.17860302e-01 * (CameraParam.height - hv_Row2[hv_I].D) + 3.46023944e+02) / ord;
                //double newx = (1.19612226e-01 * hv_Column2[hv_I].D - 3.10153083e-03 * (CameraParam.height - hv_Row2[hv_I].D) + 1.48334677e+02) / ord;

                /*二号机*/
                //double ord = -4.78898795e-06 * hv_Column2[hv_I].D - 2.14220995e-05 * (CameraParam.height - hv_Row2[hv_I].D) + 1.00000000e+00;//TODO:变换矩阵的硬编码
                //double newy = (-4.56232717e-03 * hv_Column2[hv_I].D - 1.69739637e-01 * (CameraParam.height - hv_Row2[hv_I].D) + 4.06122577e+02) / ord;
                //double newx = (1.62061006e-01 * hv_Column2[hv_I].D - 8.00225962e-03 * (CameraParam.height - hv_Row2[hv_I].D) + 7.69763072e+01) / ord;
                double ord = -1.24080815e-04 * hv_Column2[hv_I].D - 4.59316882e-05 * (CameraParam.height - hv_Row2[hv_I].D) + 1.00000000e+00;//TODO:变换矩阵的硬编码
                double newy = (-4.07999396e-02 * hv_Column2[hv_I].D + 1.58650884e-01 * (CameraParam.height - hv_Row2[hv_I].D) + 7.54977524e+01) / ord;
                double newx = (-2.18555552e-01 * hv_Column2[hv_I].D - 1.14939788e-02 * (CameraParam.height - hv_Row2[hv_I].D) + 5.69874991e+02) / ord;
                double height = 0;
                try
                {
                    height = CameraParam.deepLoader((int)(newx), (int)(newy)) *9.0/100.0;
                    height = 1.133E-05*Math.Pow(height,4) - 0.001322 * Math.Pow(height, 3) + 0.04717 * Math.Pow(height, 2) + 0.6649 * Math.Pow(height, 1);
                }
                catch
                {
                    continue;
                }
                PointData item = new PointData((int)hv_I, hv_Column2[hv_I].D, hv_Row2[hv_I].D, height, hv_Angle[hv_I].D);
                List.Add(item);

                //生成一个单位矩阵
                HOperatorSet.HomMat2dIdentity(out hv_HomMat2DIdentity);
                //平移
                HOperatorSet.HomMat2dTranslate(hv_HomMat2DIdentity, hv_Row2.TupleSelect(hv_I),
                    hv_Column2.TupleSelect(hv_I), out hv_HomMat2DTranslate);
                //旋转
                HOperatorSet.HomMat2dRotate(hv_HomMat2DTranslate, hv_Angle.TupleSelect(hv_I),
                    hv_Row2.TupleSelect(hv_I), hv_Column2.TupleSelect(hv_I), out hv_HomMat2DRotate);
                //放缩，得到最终的仿射变换矩阵
                HOperatorSet.HomMat2dScale(hv_HomMat2DRotate, hv_Scale.TupleSelect(hv_I), hv_Scale.TupleSelect(
                    hv_I), hv_Row2.TupleSelect(hv_I), hv_Column2.TupleSelect(hv_I), out hv_HomMat2DScale);
                //仿射变换
                ho_ModelTrans.Dispose();
                HOperatorSet.AffineTransContourXld(ho_ModelContours, out ho_ModelTrans, hv_HomMat2DScale);
                ho_UnionContours.Dispose();
                HOperatorSet.UnionAdjacentContoursXld(ho_ModelTrans, out ho_UnionContours,
                    80, 1, "attr_keep");
                ho_Region.Dispose();
                HOperatorSet.GenRegionContourXld(ho_UnionContours, out ho_Region, "margin");
                {
                    HObject ExpTmpOutVar_0;
                    HOperatorSet.DilationCircle(ho_Region, out ExpTmpOutVar_0, 5);
                    ho_Region.Dispose();
                    ho_Region = ExpTmpOutVar_0;
                }
                {
                    HOperatorSet.PaintRegion(ho_Region, ho_greenTestImageMedian, out ho_greenTestImageMedian, 255, "fill");
                }
            }

            HOperatorSet.Compose3(ho_testImageMedian, ho_greenTestImageMedian, ho_testImageMedian,
                out outImage);


            ho_greenTestImageMedian.Dispose();
            ho_UnionContours.Dispose();
            ho_Region.Dispose();
            ho_ModelContours.Dispose();
            ho_testImage.Dispose();
            ho_testImageMedian.Dispose();
            ho_ModelTrans.Dispose();
        }

    }
}
