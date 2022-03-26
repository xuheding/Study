using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _31_Dictionary
{
    class Program
    {
        static void Main(string[] args)
        {
            //类似于ArrayList和List的区别，一个涉及拆箱装箱，一个不涉及
            //Hashtable涉及拆箱和装箱，而Dictionary不涉及

            Dictionary<int, string> dic = new Dictionary<int, string>();
            dic.Add(1, "张三");
            dic.Add(2, "李四");
            dic.Add(3, "王五");
            //foreach(var item in dic.Keys)
            //{
            //    Console.WriteLine(dic[item]);
            //}

            foreach(KeyValuePair<int,string> kv in dic)
            {
                Console.WriteLine("{0}--{1}",kv.Key,kv.Value);
            }

            Console.ReadKey();
        }
    }
}
