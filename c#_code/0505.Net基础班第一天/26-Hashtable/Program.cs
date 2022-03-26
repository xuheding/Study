using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _26_Hashtable
{
    class Program
    {
        static void Main(string[] args)
        {
            //1.创建Hashtalbe（类似python中的字典）
            Hashtable ht = new Hashtable();
            ht.Add(1, "zhangsan");
            ht.Add(2, true);
            ht.Add(3, "male");
            ht.Add(false, "error");

            //var类似c++中的auto
            //2.遍历  键
            foreach (var item in ht.Keys)
            {
                Console.WriteLine(ht[item]);
            }

            //3.ht.ContainKey("abc");判断是否有某个键
            //4.ht.clear(); 清空hashtable
            //5.ht.Remove(3);根据键去移除键值对
        }
    }
}
