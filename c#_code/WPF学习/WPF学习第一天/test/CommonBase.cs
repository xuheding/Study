using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace test
{
    public class CommonBase : ICommand
    {
        public event EventHandler CanExecuteChanged;

        public bool CanExecute(object parameter)
        {
            return DoCanExecute?.Invoke(parameter) == true;

        }

        public void Execute(object parameter)
        {
            DoAction?.Invoke(parameter);

        }

        public Action<object> DoAction { get; set; }
        public Func<object,bool> DoCanExecute { get; set; }

        public void RaiseCanExecute()
        {
            CanExecuteChanged?.Invoke(this, new EventArgs());
        }
    }
}
