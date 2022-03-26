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
    HOperatorSet.ReadImage(out ho_Image, "D:/LabWork/Brick/dataset/2019_10_24/Image_20190926102120238.jpg");

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

  public void RunHalcon(HTuple Window)
  {
    hv_ExpDefaultWinHandle = Window;
    action();
  }

}

