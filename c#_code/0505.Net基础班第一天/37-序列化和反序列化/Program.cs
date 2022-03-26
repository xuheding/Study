using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
/// <summary>
/// 序列化：就是将对象转换为二进制
/// 反序列化：就是将二进制转换为对象
/// 作用：传输数据
/// 
/// 可以保存任何一个obj对象
/// </summary>
namespace _37_序列化和反序列化
{
    class Program
    {
        static void Main(string[] args)
        {

            //序列化
            Person p = new Person();
            p.Name = "张三";
            p.Age = 10;
            p.Gender = '男';
            using (FileStream fsWrite=new FileStream(@"E:\code\c#_code\0505.Net基础班第一天\37-序列化和反序列化\new.txt", FileMode.OpenOrCreate, FileAccess.Write))
            {
                //开始序列化对象
                BinaryFormatter bf = new BinaryFormatter();
                bf.Serialize(fsWrite,p);
            }
            Console.WriteLine("序列化成功");
            //Console.ReadKey();


            //反序列化
            Person p2;
            using (FileStream fsRead=new FileStream(@"E:\code\c#_code\0505.Net基础班第一天\37-序列化和反序列化\new.txt", FileMode.OpenOrCreate, FileAccess.Read))
            {
                BinaryFormatter bf2 = new BinaryFormatter();
                p2 = (Person)bf2.Deserialize(fsRead);
                
            }
            Console.WriteLine(p.Name);
            Console.WriteLine(p.Age);
            Console.WriteLine(p.Gender);
            Console.ReadKey();
        }
    }



    //将对象序列化，必须要加上这么一行，表示可序列化
    [Serializable]
    public class Person
    {
        string _name;
        int _age;
        char _gender;

        public string Name { get => _name; set => _name = value; }
        public int Age { get => _age; set => _age = value; }
        public char Gender { get => _gender; set => _gender = value; }


    }
}
