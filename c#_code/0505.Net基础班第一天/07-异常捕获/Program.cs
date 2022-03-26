using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _07_异常捕获
{
    class Program
    {
        /// <summary>
        /// 首先运行try中的代码，如果运行到一某行出错了，那么接下来的几行就不会运行，则会进行catch
        /// 和py中的try-except是一样的
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            int number=0;
            Console.WriteLine("请输入一个数字");

            try
            {
                number = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine(number * 2);
            }
            catch
            {
                Console.WriteLine("输入的内容不能转换为数字");
            }

                
            Console.ReadKey();

        }
    }
}
