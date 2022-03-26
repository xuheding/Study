using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/// <summary>
/// c#中的访问修饰符
/// 
/// public:公开的
/// private:私有的,只能在当前类的内部访问
/// protected:受保护的，只能在当前类的内部以及该类的子类中访问
/// internal:只能在当前项目中访问 。在同一个项目中，internal和public 权限是一样的
/// 
/// 1)能够修饰类的访问修饰符只有两个：public、internal
/// 2)可访问行不一致
/// 子类的访问权限不能高于父类的访问权限,否则会暴露父类的成员
/// 
/// </summary>
namespace _35_访问修饰符
{
    class Program
    {
        static void Main(string[] args)
        {
        }
    }


    //不能这样写，因为Person是internal权限，其他项目无法访问它和它的成员
    //如果子类Student写成public，那么可以通过子类去访问Person的东西，这样显然是不允许的，会报错
    //internal class Person
    //{

    //}

    //public class Student : Person
    //{

    //}

}
