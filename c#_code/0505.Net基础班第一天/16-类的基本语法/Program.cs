using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _16_类的基本语法
{
    class Program
    {
        static void Main(string[] args)
        {
            //创建Person类的对象
            Person zhangSan = new Person();
            zhangSan.Name = "张三";
            zhangSan.Age = -10;
            zhangSan.Gender = '男';
            zhangSan.Print();
            Console.ReadKey();
        }
    }
}
