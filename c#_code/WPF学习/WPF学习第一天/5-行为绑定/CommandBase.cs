using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace _5_行为绑定
{
    public class CommandBase : ICommand  //先继承ICommand接口，然后Alt+Enter去实现所有接口
    {
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            //绑定了这个命令的按钮是否可用
            return DoCanExecute?.Invoke(parameter)==true;
        }

        public void Execute(object parameter)//这里的parameter是来自  xaml控件中的CommandParameter参数设置
        {
            //控制逻辑      
            DoAction?.Invoke(parameter);//Invoke在拥有此控件的基础窗口句柄的线程上执行指定的委托
        }

        public Action<object> DoAction { get; set; }
        public Func<object,bool> DoCanExecute { get; set; }//返回值是bool

        public void RaiseCanChanged()
        {
            CanExecuteChanged?.Invoke(this, new EventArgs());
        }

    }
}
