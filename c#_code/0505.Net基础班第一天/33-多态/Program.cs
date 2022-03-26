using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/// <summary>
/// 1.将父类函数标记成virtual虚函数，子类重写加override。 这样就能通过父类调用子类函数
/// 2.抽象类
///     当父类中的方法不知道如何去实现的时候，可以考虑将父类写成抽象类，将方法写成抽象方法
/// </summary>
namespace _33_多态
{
    class Program
    {
        static void Main(string[] args)
        {
            Chinese cn1 = new Chinese("lilei");
            Chinese cn2 = new Chinese("cao");
            English en1 = new English("1111");
            Person[] pers = { cn1, cn2, en1 };

            for(int i = 0; i < pers.Length; i++)
            {
                pers[i].SayHello();
            }
            Console.ReadKey();

        }
    }

    public class Person
    {
        string _name;

        public string Name { get => _name; set => _name = value; }

        public Person(string name)
        {
            _name = name;
        }
        public virtual void SayHello()  //父类要设置虚函数 加关键字virtual
        {
            Console.WriteLine("我是人类");
        }
    }

    public class Chinese : Person
    {
        public Chinese(string name)
            : base(name)
        {

        }

        public override void SayHello()  //子类要重写父类虚函数  加关键字override
        {
            Console.WriteLine("我是中国人,{0}", this.Name);
        }
    }

    public class English : Person
    {
        public English(string name)
            : base(name)
        {

        }

        public override void SayHello()
        {
            Console.WriteLine("我是英国人,{0}", this.Name);
        }
    }
}
