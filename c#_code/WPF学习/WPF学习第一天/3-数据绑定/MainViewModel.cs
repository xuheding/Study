using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows;
using System.ComponentModel;


namespace _3_数据绑定
{
    public class MainViewModel:INotifyPropertyChanged//继承这个接口
    {
        public event PropertyChangedEventHandler PropertyChanged;//然后去实现这个接口，后续就对 该对象的属性更新到窗体中

        private string _value="99";

        public string Value
        {
            get { return _value; }
            set 
            { 
                _value = value;
                if (value == "100")
                {
                    PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Value"));//通知窗体对该值做出更新
                    ValueColor = Brushes.Red;
                }
            }
        }

        private Brush _valueColor=Brushes.Orange;

        public Brush ValueColor
        {
            get { return _valueColor; }
            set 
            { 
                _valueColor = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("ValueColor"));
            }
        }



    }
}
