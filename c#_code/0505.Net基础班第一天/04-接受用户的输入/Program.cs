using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _04_接受用户的输入
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("请输入你的姓名");

            //接受控制台的输入
            string name=Console.ReadLine();

            Console.WriteLine("您的姓名是{0}", name);
            Console.ReadKey();
        }
    }
}
