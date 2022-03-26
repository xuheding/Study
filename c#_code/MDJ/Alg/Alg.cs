using System;
using System.IO;
using System.Text;
using System.Windows;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;
using Point = System.Windows.Point;
using System.Security.Cryptography;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace MDJ
{
    public class ImageBytes : IDisposable
    {
        public byte[] bytes;
        public int width = 0;
        public int height = 0;

        public void Dispose()
        {
            bytes = null;
            GC.SuppressFinalize(this);
        }

        public ImageBytes(byte[] b, int w, int h)
        {
            bytes = b;
            width = w;
            height = h;
        }

        public ImageBytes(string file)
        {
            BitmapImage bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.CacheOption = BitmapCacheOption.OnLoad;
            bitmap.CreateOptions = BitmapCreateOptions.PreservePixelFormat;
            using (var stream = File.OpenRead(file)) {
                bitmap.StreamSource = stream;
                bitmap.EndInit();
                bitmap.Freeze();
            }

            width = bitmap.PixelWidth;
            height = bitmap.PixelHeight;
            bytes = new byte[width * height * 3];
            bitmap.CopyPixels(bytes, width * 3, 0);
        }

        public ImageBytes(BitmapSource source)
        {
            width = source.PixelWidth;
            height = source.PixelHeight;
            bytes = new byte[width * height * 3];
            source.CopyPixels(bytes, width * 3, 0);
        }

        public ImageBytes scale(float scale)
        {
            BitmapSource source = BitmapSource.Create(width, height, 96, 96, PixelFormats.Bgr24, null, bytes, width * 3);
            MemoryStream stream = new MemoryStream();
            BmpBitmapEncoder encoder = new BmpBitmapEncoder();
            encoder.Frames.Add(BitmapFrame.Create(source));
            encoder.Save(stream);

            Bitmap thumb = new Bitmap(new Bitmap(stream), (int)(width * scale), (int)(height * scale));
            int w = thumb.Width;
            int h = thumb.Height;

            IntPtr hBitmap = thumb.GetHbitmap();
            BitmapSource imagesource = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(hBitmap, IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
            byte[] buffer = new byte[w * h * 4];
            imagesource.CopyPixels(buffer, w * 4, 0);

            return new ImageBytes(buffer, w, h);
        }
    }



    public class AlgParam
    {
        public string param { get; set; }
        public string name { get; set; }
        public string type { get; set; }
        public string value { get; set; }
        public string remark { get; set; }

        public AlgParam(string p, string n, string t, string v = "", string r = "") { param = p; name = n; type = t; value = v; remark = r; }
        public bool check(string str = "")
        {
            if (string.IsNullOrEmpty(str))
                str = value;
            switch (type)
            {
                case "int":
                    return int.TryParse(str, out _);
                case "uint":
                    return uint.TryParse(str, out _);
                case "float":
                    return float.TryParse(str, out _);
                case "double":
                    return double.TryParse(str, out _);
                case "point":
                    try {
                        Point.Parse(str);
                        return true;
                    } catch {
                        return false;
                    }
                case "rect":
                    try {
                        Int32Rect.Parse(str);
                        return true;
                    } catch {
                        return false;
                    }
            }
            return true;
        }
    }


}
