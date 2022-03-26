using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _32_Filestream
{
    class Program
    {
        static void Main(string[] args)
        {
            //FileStream 操作字节的(在操作大文件的时候需要用到循环)
            //1.创建FileStream对象
            FileStream fsRead = new FileStream(@"E:\code\c#_code\0505.Net基础班第一天\32-Filestream\1.txt", FileMode.OpenOrCreate, FileAccess.Read);
            byte[] buffer = new byte[1024 * 1024 * 5];
            //返回本次实际读取到的有效字节数
            int r= fsRead.Read(buffer, 0, buffer.Length);//从0开始放，读的长度为buffer.Length,每次读5Mb
            //将字节数组中每一个元素按照指定的编码格式解码成字符串
            string s = Encoding.UTF8.GetString(buffer,0,r);//比如文件只有100kb，但是每次读5Mb，导致buffer数组中很多都是空的，因此要限制buffer的范围为0~r
            //关闭流
            fsRead.Close();
            //释放流所占用的资源
            fsRead.Dispose();
            Console.WriteLine(s);
            Console.ReadKey();

            //2.将创建文件流对象的过程写在using当找，会自动帮助我们释放流所占用的资源。

            //类型python中的上下文管理器(with)
            using (FileStream fsWrite=new FileStream(@"E:\code\c#_code\0505.Net基础班第一天\32-Filestream\new.txt",FileMode.OpenOrCreate,FileAccess.Write))
            {
                string str = "";
                byte[] buffer1 = Encoding.UTF8.GetBytes(str);
                fsWrite.Write(buffer, 0, buffer.Length);//这个例子中只读取一次
            }


            //3.用FileStream文件流进行文件复制

            //4.StreamReader和StreamWriter

            //用StreamReader读取文件
            using (StreamReader sr=new StreamReader(@"E:\code\c#_code\0505.Net基础班第一天\32-Filestream\1.txt"))
            {
                while (!sr.EndOfStream)
                {
                    Console.WriteLine(sr.ReadLine());
                }
            }
            Console.ReadKey();


            //用StreamWriter来写入一个文本文件
            using (StreamWriter sw=new StreamWriter(@"E:\code\c#_code\0505.Net基础班第一天\32-Filestream\new.txt",true))//设置追加
            {
                sw.Write("hello");
            }
            


        }
    }
}
