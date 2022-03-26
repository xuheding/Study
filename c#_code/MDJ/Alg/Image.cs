using System;
using System.Drawing;
using System.Drawing.Imaging;
using HalconDotNet;
using System.Windows.Media.Imaging;
using System.Runtime.InteropServices;





namespace MDJ
{
    public class Image
    {
        public static HObject Bytes2HObject(ImageBytes image)
        {
            return Bytes2HObject(image.bytes, image.width, image.height);
        }

        public static HObject Bytes2HObject(byte[] bytes, int width, int height)
        {
            try {
                unsafe {
                    fixed (byte* ptr = bytes) {
                        HOperatorSet.GenImage1(out HObject ho, "byte", width, height, new IntPtr(ptr));
                        return ho;
                    }
                }
            } catch (Exception e) {
                Console.WriteLine("Bytes2HObject fail: " + e.Message);
                return null;
            }
        }
        public static HObject Bytes2HObject3(ImageBytes image)
        {
            return Bytes2HObject3(image.bytes, image.width, image.height);
        }

        public static HObject Bytes2HObject3(byte[] bytes, int width, int height)
        {
            try {
                unsafe {
                    fixed (byte* ptr = bytes) {
                        HOperatorSet.GenImageInterleaved(out HObject ho, new IntPtr(ptr), "bgr", width, height, -1, "byte", width, height, 0, 0, -1, 0);
                        return ho;
                    }
                }
            } catch (Exception e) {
                Console.WriteLine("Bytes2HObject3 fail: " + e.Message);
                return null;
            }
        }

        public static HObject Bitmap2HObject(Bitmap bmp)
        {
            try {
                HOperatorSet.GenEmptyObj(out HObject ho_Image);
                unsafe {
                    Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
                    BitmapData srcBmpData = bmp.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
                    unsafe {
                        HOperatorSet.GenImage1(out ho_Image, "byte", bmp.Width, bmp.Height, srcBmpData.Scan0);
                    }
                    bmp.UnlockBits(srcBmpData);
                    return ho_Image;
                }
            } catch (Exception e) {
                Console.WriteLine("Bytes2HObject fail: " + e.Message);
                return null;
            }
        }

        public static HObject Bitmap2HObject3(Bitmap bitmap)
        {
            try {
                HOperatorSet.GenEmptyObj(out HObject ho_Image);
                unsafe {
                    BitmapData bmpData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
                    unsafe {
                        HOperatorSet.GenImageInterleaved(out ho_Image, bmpData.Scan0, "bgr", bitmap.Width, bitmap.Height, -1, "byte", bitmap.Width, bitmap.Height, 0, 0, -1, 0);
                    }
                    bitmap.UnlockBits(bmpData);
                    return ho_Image;
                }
            } catch (Exception e) {
                Console.WriteLine("Bitmap2HObject3 fail: " + e.Message);
                return null;
            }
        }

        [DllImport("kernel32.dll")]
        public static extern void CopyMemory(int Destination, int add, int Length);

        public static void HObject2Bitmap(HObject image, out Bitmap res)
        {

            HTuple hpoint, type, width, height;

            const int Alpha = 255;
            int[] ptr = new int[2];
            HOperatorSet.GetImagePointer1(image, out hpoint, out type, out width, out height);

            res = new Bitmap(width, height, PixelFormat.Format8bppIndexed);
            ColorPalette pal = res.Palette;
            for (int i = 0; i <= 255; i++)
            {
                pal.Entries[i] = Color.FromArgb(Alpha, i, i, i);
            }
            res.Palette = pal;
            Rectangle rect = new Rectangle(0, 0, width, height);
            BitmapData bitmapData = res.LockBits(rect, ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            int PixelSize = Bitmap.GetPixelFormatSize(bitmapData.PixelFormat) / 8;
            ptr[0] = bitmapData.Scan0.ToInt32();
            ptr[1] = hpoint.I;
            if (width % 4 == 0)
                CopyMemory(ptr[0], ptr[1], width * height * PixelSize);
            else
            {
                for (int i = 0; i < height - 1; i++)
                {
                    ptr[1] += width;
                    CopyMemory(ptr[0], ptr[1], width * PixelSize);
                    ptr[0] += bitmapData.Stride;
                }
            }
            res.UnlockBits(bitmapData);


        }




        public static Bitmap HObject2Bitmap3(HObject image)
        {
            try {
                HOperatorSet.GetImagePointer3(image, out HTuple hred, out HTuple hgreen, out HTuple hblue, out HTuple type, out HTuple width, out HTuple height);

                Bitmap bitmap = new Bitmap(width, height, PixelFormat.Format24bppRgb);
                BitmapData bitmapData = bitmap.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
                unsafe {
                    byte* bptr = (byte*)bitmapData.Scan0;
                    byte* r = (byte*)hred.I;
                    byte* g = (byte*)hgreen.I;
                    byte* b = (byte*)hblue.I;

                    int lengh = width * height;
                    for (int i = 0; i < lengh; i++) {
                        bptr[i * 3] = b[i];
                        bptr[i * 3 + 1] = g[i];
                        bptr[i * 3 + 2] = r[i];

                    }
                }
                bitmap.UnlockBits(bitmapData);
                return bitmap;
            } catch (Exception e) {
                Console.WriteLine("HObject2Bitmap3 fail: " + e.Message);
                return null;
            }
        }

        public static ImageBytes HObject2Bytes3(HObject image)
        {
            try {
                unsafe {
                    HOperatorSet.GetImagePointer3(image, out HTuple hred, out HTuple hgreen, out HTuple hblue, out HTuple type, out HTuple width, out HTuple height);
                    ImageBytes ib = new ImageBytes(new byte[width * height * 3], width, height);

                    byte* r = (byte*)hred.I;
                    byte* g = (byte*)hgreen.I;
                    byte* b = (byte*)hblue.I;

                    int length = width * height;
                    for (int i = 0; i < length; i++) {
                        ib.bytes[i * 3] = b[i];
                        ib.bytes[i * 3 + 1] = g[i];
                        ib.bytes[i * 3 + 2] = r[i];
                    }
                    return ib;
                }
            } catch (Exception e) {
                Console.WriteLine("HObject2Bitmap3 fail: " + e.Message);
                return null;
            }
        }


        public static ImageBytes HObject2Bytes(HObject image)
        {
            try
            {
                unsafe
                {
                    HOperatorSet.GetImagePointer1(image, out HTuple hred, out HTuple type, out HTuple width, out HTuple height);
                    ImageBytes ib = new ImageBytes(new byte[width * height], width, height);

                    byte* r = (byte*)hred.I;

                    int length = width * height;
                    for (int i = 0; i < length; i++)
                    {
                        ib.bytes[i] = r[i];
                    }
                    return ib;
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("HObject2Bytes fail: " + e.Message);
                return null;
            }
        }



        public static void BitmapToHobject(Bitmap bitmap, out HObject image)
        {
            Rectangle imgRect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
            BitmapData bitData = bitmap.LockBits(imgRect, ImageLockMode.ReadOnly, bitmap.PixelFormat);
            switch (bitmap.PixelFormat) {
                case PixelFormat.Format8bppIndexed:
                    HOperatorSet.GenImage1(out image, "byte", bitmap.Width, bitmap.Height, bitData.Scan0);
                    break;
                case PixelFormat.Format24bppRgb:
                    HOperatorSet.GenImageInterleaved(out image, bitData.Scan0, "rgb", bitmap.Width, bitmap.Height, 0, "byte", bitmap.Width, bitmap.Height, 0, 0, -1, 0);
                    break;
                default:
                    HOperatorSet.GenImage1(out image, "byte", bitmap.Width, bitmap.Height, bitData.Scan0);
                    break;
            }
            bitmap.UnlockBits(bitData);
        }
    }
}
