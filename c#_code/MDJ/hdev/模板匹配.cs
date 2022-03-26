//
//  File generated by HDevelop for HALCON/DOTNET (C#) Version 12.0
//
//  This file is intended to be used with the HDevelopTemplate or
//  HDevelopTemplateWPF projects located under %HALCONEXAMPLES%\c#

using System;
using HalconDotNet;

public partial class HDevelopExport
{
  public HTuple hv_ExpDefaultWinHandle;

  // Main procedure 
  private void action()
  {


    // Local iconic variables 

    HObject ho_Image, ho_ImageMedian, ho_Rectangle;
    HObject ho_ImageReduced, ho_ModelImages, ho_ModelRegions;
    HObject ho_ModelContours, ho_testImage, ho_testImageMedian;
    HObject ho_ModelTrans=null;

    // Local control variables 

    HTuple hv_Width = null, hv_Height = null, hv_WindowHandle = new HTuple();
    HTuple hv_Row1 = null, hv_Column1 = null, hv_Row2 = null;
    HTuple hv_Column2 = null, hv_Area = null, hv_ModelID = null;
    HTuple hv_NumLevels = null, hv_AngleStart = null, hv_AngleExtent = null;
    HTuple hv_AngleStep = null, hv_ScaleMin = null, hv_ScaleMax = null;
    HTuple hv_ScaleStep = null, hv_Metric = null, hv_MinContrast = null;
    HTuple hv_Angle = null, hv_Scale = null, hv_Score = null;
    HTuple hv_I = null, hv_HomMat2DIdentity = new HTuple();
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
    HOperatorSet.GenEmptyObj(out ho_testImage);
    HOperatorSet.GenEmptyObj(out ho_testImageMedian);
    HOperatorSet.GenEmptyObj(out ho_ModelTrans);
    ho_Image.Dispose();
    HOperatorSet.ReadImage(out ho_Image, "D:/LabWork/Brick/dataset/2019_10_24/Image_20190926102120238.jpg");

    ho_ImageMedian.Dispose();
    HOperatorSet.MedianImage(ho_Image, out ho_ImageMedian, "circle", 10, "mirrored");


    HOperatorSet.GetImageSize(ho_ImageMedian, out hv_Width, out hv_Height);
    //dev_open_window(...);
    HOperatorSet.DispObj(ho_ImageMedian, hv_ExpDefaultWinHandle);


    HOperatorSet.DrawRectangle1(hv_ExpDefaultWinHandle, out hv_Row1, out hv_Column1, 
        out hv_Row2, out hv_Column2);

    ho_Rectangle.Dispose();
    HOperatorSet.GenRectangle1(out ho_Rectangle, hv_Row1, hv_Column1, hv_Row2, hv_Column2);



    ho_ImageReduced.Dispose();
    HOperatorSet.ReduceDomain(ho_ImageMedian, ho_Rectangle, out ho_ImageReduced);


    HOperatorSet.AreaCenter(ho_Rectangle, out hv_Area, out hv_Row1, out hv_Column1);


    HOperatorSet.CreateScaledShapeModel(ho_ImageReduced, 5, (new HTuple(-180)).TupleRad()
        , (new HTuple(360)).TupleRad(), "auto", 0.5, 1.5, "auto", "auto", "ignore_global_polarity", 
        "auto", "auto", out hv_ModelID);
    ho_ModelImages.Dispose();ho_ModelRegions.Dispose();
    HOperatorSet.InspectShapeModel(ho_ImageReduced, out ho_ModelImages, out ho_ModelRegions, 
        4, 20);
    HOperatorSet.GetShapeModelParams(hv_ModelID, out hv_NumLevels, out hv_AngleStart, 
        out hv_AngleExtent, out hv_AngleStep, out hv_ScaleMin, out hv_ScaleMax, out hv_ScaleStep, 
        out hv_Metric, out hv_MinContrast);
    ho_ModelContours.Dispose();
    HOperatorSet.GetShapeModelContours(out ho_ModelContours, hv_ModelID, 1);


    ho_testImage.Dispose();
    HOperatorSet.ReadImage(out ho_testImage, "D:/LabWork/Brick/dataset/2019_10_23/Image_2.bmp");
    ho_testImageMedian.Dispose();
    HOperatorSet.MedianImage(ho_testImage, out ho_testImageMedian, "circle", 10, 
        "mirrored");
    HOperatorSet.FindScaledShapeModel(ho_testImageMedian, hv_ModelID, (new HTuple(-180)).TupleRad()
        , (new HTuple(360)).TupleRad(), 0.8, 1.2, 0.4, 5, 0.5, "least_squares", 5, 
        0.8, out hv_Row2, out hv_Column2, out hv_Angle, out hv_Scale, out hv_Score);

    for (hv_I=0; (int)hv_I<=(int)((new HTuple(hv_Score.TupleLength()))-1); hv_I = (int)hv_I + 1)
    {
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
      HOperatorSet.DispObj(ho_ModelTrans, hv_ExpDefaultWinHandle);
    }









    ho_Image.Dispose();
    ho_ImageMedian.Dispose();
    ho_Rectangle.Dispose();
    ho_ImageReduced.Dispose();
    ho_ModelImages.Dispose();
    ho_ModelRegions.Dispose();
    ho_ModelContours.Dispose();
    ho_testImage.Dispose();
    ho_testImageMedian.Dispose();
    ho_ModelTrans.Dispose();

  }

  public void InitHalcon()
  {
    // Default settings used in HDevelop 
    HOperatorSet.SetSystem("width", 512);
    HOperatorSet.SetSystem("height", 512);
  }

  public void RunHalcon(HTuple Window)
  {
    hv_ExpDefaultWinHandle = Window;
    action();
  }

}

