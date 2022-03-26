using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// [public] interface 变量名
/// {
/// 
/// }
///
/// 接口只是一个行为的规范或规定
/// 抽象类主要用于关系密切的对象；而接口适合为不相关的类提供通用功能
/// </summary>
/// 

namespace _41_接口
{
    class Program
    {
        static void Main(string[] args)
        {
            IFlyable fly = new Bird();//相当于提供了一个对外的接口,是对象Bird中的一部分，并不是所有的全部对外。 
            fly.Fly();
            Console.ReadKey();
        }
    }

    public class Bird : IFlyable
    {
        public void Fly()
        {
            Console.WriteLine("鸟在飞");
        }

    }


    public interface IFlyable
    {
        //接口中的成员不允许添加访问修饰符，默认就是pubilc(类中默认是private)
        //接口中的方法，不允许有方法体(实现)
        //接口中不能包含字段和构造函数，只能有方法，属性(本质是两个方法)，索引器，事件
        //接口与接口之间可以继承，并且可以多继承
        //接口并不能去继承一个类，而类可以继承接口
        //继承接口的子类必须实现该接口的全部成员
        //如果一个类既继承类又继承接口，类要写在接口前面

        //接口不能被实例化

        void Fly();
        //string Test();

        //string Name
        //{
        //    get;
        //    set;
        //}
    }
}
