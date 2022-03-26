using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/// <summary>
/// 部分类：就是将一个类拆分为几个部分，这样就允许多人对一个类进行操作了。实际上还是一个类，用partial修饰
/// 因为本质就是一个类，只不过写在不同的地方而已，因此不能有重复的方法
/// </summary>
namespace _38_部分类
{
    class Program
    {
        static void Main(string[] args)
        {
            Person p1 = new Person();
        }

        public partial class Person
        {
            string _name;

        
        }

        public partial class Person
        {
            public string Name { get => _name; set => _name = value; }
        }
    }
}
