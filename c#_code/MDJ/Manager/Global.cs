using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;
using System.Windows;


namespace MDJ
{

    public class CameraInfo
    {
        public string sn = "";
        public int trigger = 0;
        public int expose = 0;
        public float gain = 0;
        public int width = 0;
        public int height = 0;
        public byte stride = 0;
        public byte lorr = 0;
    }

    class Global
    {
        public static List<CameraInfo> listCamera = new List<CameraInfo>();
        public static double detectAcc = 0.66;

        public static void writeImage(WriteableBitmap wbm, Int32Rect rect, byte[] bytes, int stride, Action onFinish = null)
        {
            try
            {
                wbm.Lock();
                wbm.WritePixels(rect, bytes, stride, 0);
            }
            catch (Exception ex)
            {
                //LogMgr.instance.addError("writeImage error:" + ex.Message);
                Console.WriteLine("writeImage error:" + ex.Message);

            }
            finally
            {
                wbm.Unlock();
                onFinish?.Invoke();
            }
        }
    }
}
