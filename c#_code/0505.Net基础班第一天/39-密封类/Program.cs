using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _39_密封类
{
    class Program
    {
        static void Main(string[] args)
        {
        }
    }

    //密封类：加入关键词sealed    特点是：不能被继承，但可以继承别人.
    public sealed class Person
    {

    }

    public class Test : Person  //不能继承密封类，会报错
    {

    }
}
