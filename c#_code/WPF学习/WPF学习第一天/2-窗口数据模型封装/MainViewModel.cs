using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;//这两个库都要加进来
using System.Windows;

namespace _2_窗口数据模型封装
{
    class MainViewModel
    {
        private MainWindow _mainWindow;
        public MainViewModel(MainWindow mainWindow)
        {
            _mainWindow = mainWindow;
        }
        //通过propfull+2次Tab可以快速打出字段及其属性

        private string _value;

        public string Value
        {
            get { return _value; }
            set 
            { 
                _value = value;
                _mainWindow.tbName.Text = value;
                if (value == "100")
                {
                    _mainWindow.tbName.Foreground = Brushes.Orange;
                    MessageBox.Show("登录成功");
                }
                
            }
        }





    }
}
