using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/// <summary>
/// 一个类中包含字段、属性、方法
/// 属性的作用就是保护字段、对字段的赋值和取值进行限定
/// 属性的本质就是连个方法，一个是get(),一个是set()
/// 不是每个属性都需要有get(）和set(),
/// 
/// public,protected,private用法和c++一样
/// </summary>
namespace _16_类的基本语法
{
    public class Person
    {
        //字段
        private string _name;//默认不加就是private
        private int _age;
        private char _gender;


        //属性(选中字段 ctrl+r+e可以快速创建属性)
        public string Name  //属性本质是方法，使用的是字段的值
        {
            //当输出属性的时候
            get { return _name; }
            //当设置属性的时候
            set { _name = value; }
        }
        public int Age
        {
            get { return _age; }
            set 
            {
                if (value < 0 || value > 100)
                {
                    value = 0;
                }
                _age = value; 
            }
        }
        public char Gender
        {
            get 
            {
                if (_gender != '男' && _gender != '女')
                {
                    return '男';
                }
                return _gender; 
            }
            set 
            { 
                _gender = value; 
            }
        }
        

        //方法
        public void Print()
        {
            Console.WriteLine("我叫{0},我{1}岁了，我是{2}生",this.Name,this.Age,this.Gender);
        }
    }

}
