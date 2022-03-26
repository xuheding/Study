using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HalconDotNet;

namespace MDJ
{

    public partial class TemplateBuilder
    {
        public HTuple hv_ExpDefaultWinHandle;

        // Main procedure 
        private HTuple getTemplate(string tempPath)
        {
            // Local iconic variables 
            HObject ho_Image, ho_ImageMedian, ho_Rectangle;
            HObject ho_ImageReduced, ho_ModelImages, ho_ModelRegions;
            HObject ho_ModelContours;
            HObject ho_ModelTrans = null;

            // Local control variables 
            HTuple hv_Width = null, hv_Height = null, hv_WindowHandle = new HTuple();
            HTuple hv_Row1 = null, hv_Column1 = null, hv_Row2 = null;
            HTuple hv_Column2 = null, hv_Area = null, hv_ModelID = null;

            HTuple hv_HomMat2DIdentity = new HTuple();
            HTuple hv_HomMat2DTranslate = new HTuple(), hv_HomMat2DRotate = new HTuple();
            HTuple hv_HomMat2DScale = new HTuple();

            // Initialize local and output iconic variables 
            HOperatorSet.GenEmptyObj(out ho_Image);
            HOperatorSet.GenEmptyObj(out ho_ImageMedian);
            HOperatorSet.GenEmptyObj(out ho_Rectangle);
            HOperatorSet.GenEmptyObj(out ho_ImageReduced);
            HOperatorSet.GenEmptyObj(out ho_ModelImages);
            HOperatorSet.GenEmptyObj(out ho_ModelRegions);
            HOperatorSet.GenEmptyObj(out ho_ModelContours);
            HOperatorSet.GenEmptyObj(out ho_ModelTrans);
            ho_Image.Dispose();
            HOperatorSet.ReadImage(out ho_Image, tempPath);

            ho_ImageMedian.Dispose();
            HOperatorSet.MedianImage(ho_Image, out ho_ImageMedian, "circle", 10, "mirrored");


            HOperatorSet.GetImageSize(ho_ImageMedian, out hv_Width, out hv_Height);
            //dev_open_window(...);
            HOperatorSet.DispObj(ho_ImageMedian, hv_ExpDefaultWinHandle);
            HOperatorSet.DrawRectangle1(hv_ExpDefaultWinHandle, out hv_Row1, out hv_Column1,
                out hv_Row2, out hv_Column2);
            HOperatorSet.GenRectangle1(out ho_Rectangle, hv_Row1, hv_Column1, hv_Row2, hv_Column2);
            HOperatorSet.ReduceDomain(ho_ImageMedian, ho_Rectangle, out ho_ImageReduced);
            HOperatorSet.AreaCenter(ho_Rectangle, out hv_Area, out hv_Row1, out hv_Column1);
            HOperatorSet.CreateScaledShapeModel(ho_ImageReduced, 5, (new HTuple(-180)).TupleRad()
                , (new HTuple(360)).TupleRad(), "auto", 0.5, 1.5, "auto", "auto", "ignore_global_polarity",
                "auto", "auto", out hv_ModelID);
            HOperatorSet.GetShapeModelContours(out ho_ModelContours, hv_ModelID, 1);
            HOperatorSet.HomMat2dIdentity(out hv_HomMat2DIdentity);
            HOperatorSet.HomMat2dTranslate(hv_HomMat2DIdentity, hv_Row1,hv_Column1, out hv_HomMat2DTranslate);
            HOperatorSet.AffineTransContourXld(ho_ModelContours, out ho_ModelTrans, hv_HomMat2DTranslate);
            HOperatorSet.DispObj(ho_ModelTrans, hv_ExpDefaultWinHandle);

            ho_Image.Dispose();
            ho_ImageMedian.Dispose();
            ho_Rectangle.Dispose();
            ho_ImageReduced.Dispose();
            ho_ModelImages.Dispose();
            ho_ModelRegions.Dispose();
            ho_ModelContours.Dispose();
            ho_ModelTrans.Dispose();
            return hv_ModelID;
        }


        private void readImage(string tempPath)
        {
            HObject ho_Image, ho_ImageMedian;
            HOperatorSet.GenEmptyObj(out ho_Image);
            HOperatorSet.GenEmptyObj(out ho_ImageMedian);
            HTuple hv_Width = null, hv_Height = null;
            HOperatorSet.ReadImage(out ho_Image, tempPath);
            HOperatorSet.MedianImage(ho_Image, out ho_ImageMedian, "circle", 10, "mirrored");
            HOperatorSet.GetImageSize(ho_ImageMedian, out hv_Width, out hv_Height);
            //dev_open_window(...);
            HOperatorSet.DispObj(ho_ImageMedian, hv_ExpDefaultWinHandle);
            ho_Image.Dispose();
            ho_ImageMedian.Dispose();

        }


        public void InitHalcon()
        {
            // Default settings used in HDevelop 
            HOperatorSet.SetSystem("width", 512);
            HOperatorSet.SetSystem("height", 512);
        }

        public HTuple setTemplate(HTuple Window, string tempPath)
        {
            hv_ExpDefaultWinHandle = Window;
            HTuple temp = getTemplate(tempPath);
            return temp;
        }

        public void showTemplate(HTuple Window, string tempPath)
        {
            hv_ExpDefaultWinHandle = Window;
            readImage(tempPath);
        }

    }
}
