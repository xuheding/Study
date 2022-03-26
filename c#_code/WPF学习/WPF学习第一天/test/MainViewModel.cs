using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
namespace test
{
    class MainViewModel:INotifyPropertyChanged
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

                (ValueCommand as CommonBase).RaiseCanExecute();
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
        public ICommand ValueCommand
        {
            get
            {
                if (_valueCommand == null)
                {
                    _valueCommand = new CommonBase() 
                    { 
                        DoAction = new Action<object>(ValueCommandAction),
                        DoCanExecute = new Func<object, bool>(CanExecute)
                    };

                }
                return _valueCommand;
            }
            set
            {
                _valueCommand = value;
            }
        }

        public void ValueCommandAction(object obj)
        {
            Value = "100";
        }
        public bool CanExecute(object obj)
        {
            return !string.IsNullOrEmpty(Value);
        }



    }
}
