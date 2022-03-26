using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


using _18_构造函数_析构函数;


/// <summary>
/// 要调用其他项目下的类
/// 1.现在当前项目的引用，右击添加类所在项目
/// 2.在要使用的cs文件中，using + 命名空间   即可
/// </summary>
namespace _19_命名空间
{
    class Program
    {
        static void Main(string[] args)
        {
            Student stu = new Student("zhangsan",10);
           
        }
    }
}
