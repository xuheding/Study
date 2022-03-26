using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows;
using System.ComponentModel;
using System.Windows.Input;

namespace _5_行为绑定
{
    public class MainViewModel:INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private string _value="99";

        public string Value
        {
            get { return _value; }
            set 
            { 
                _value = value;
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Value"));
                if (value == "100")
                {       
                    ValueColor = Brushes.Red;
                }


                //为了使得每次输入完成都进行一个判断 （如果为空，就使得按钮失效，否则，enalbe）
                (this.ValueCommand as CommandBase).RaiseCanChanged();
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

        private ICommand _valueCommand;
        //对button的command绑定后，点击button就会执行该ValueCommand中的Execute方法，对于ICommand是一个接口，它本身是没有实例化任何方法的，我们要添加一个对象去实现这个接口
        //于是就添加一个类去实现该方法
        public ICommand ValueCommand
        {
            get
            {
                if (_valueCommand == null)
                {
                    _valueCommand = new CommandBase() 
                    { 
                        DoAction = new Action<object>(ValueCommandAction), //创建CpmmmandBase对象，并初始化委托函数
                        DoCanExecute = new Func<object, bool>(CanExecute)
                    };

                }
                return _valueCommand;
            }
            set { _valueCommand = value; }
        }

        private void ValueCommandAction(object obj)
        {
            Value = "100";
        }
        private bool CanExecute(object obj)
        {
            return !string.IsNullOrEmpty(Value);
        }
    }
}
