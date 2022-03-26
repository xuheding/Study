using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace WPFNET5
{
    
    public class MainViewModel
    {
        //MainWindow _mainWindow;
        //public MainViewModel(MainWindow mainWindow)//由于我们这个类要对主窗口的控件进行操作，因此要利用构造函数，把主窗口的对象传进行
        //{
        //    _mainWindow = mainWindow;
        //}


        private string _value="nxy";
        public string Value
        {
            get
            {
                return _value;
            }
            set   //直接在属性里面进行封装，下面只需要调用this.Value=100即可
            {
                _value = value;
                //_mainWindow.tbName.Text = value;
                //if (value == "100")
                //{
                //    _mainWindow.tbName.Foreground = Brushes.Orange;
                //}

            }
        }//可以输入prop+2次Tab，快速输出代码片段
    }
}
