using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _24_里氏转换练习
{
    class Program
    {
        static void Main(string[] args)
        {
            //子类可以用父类数组存储
            Person[] pers = new Person[10];
            Random r = new Random();
            for(int i = 0; i < 10; i++)
            {
                int p = r.Next(1, 4);//1~3
                switch (p)
                {
                    case 1:
                        pers[i] = new Student();
                        break;
                    case 2:
                        pers[i] = new Teacher();
                        break;
                    case 3:
                        pers[i] = new YeShou();
                        break;
                }

            }

            for(int i = 0; i < 10; i++)
            {
                //如果属于哪个子类，就调用它的方法.
                if(pers[i] is Student)
                {
                    ((Student)pers[i]).StudentPrint();
                }
                else if(pers[i] is Teacher)
                {
                    ((Teacher)pers[i]).TeacherPrint();
                }
                else if(pers[i] is YeShou)
                {
                    ((YeShou)pers[i]).YeshowPrint();
                }
            }
            Console.ReadKey();

        }

       
    }


    public class Person
    {
        public void PersonPrint()
        {
            Console.WriteLine("this is a person");
        }

    }
    public class Student : Person
    {
        public void StudentPrint()
        {
            Console.WriteLine("this is a student");
        }

    }

    public class Teacher : Person
    {
        public void TeacherPrint()
        {
            Console.WriteLine("this is a teacher");
        }

    }

    public class YeShou : Person
    {
        public void YeshowPrint()
        {
            Console.WriteLine("this is a yeshou");
        }

    }

}
