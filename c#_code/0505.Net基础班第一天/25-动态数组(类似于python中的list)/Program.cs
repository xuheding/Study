using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _25_动态数组_类似于python中的list_
{
    class Program
    {
        static void Main(string[] args)
        {
            //1.创建一个列表对象
            ArrayList list = new ArrayList();
            //列表的好处:长度可任意改变，类型随便
            //2.添加一个元素(相当于python中的append)
            list.Add(1);
            list.Add(3.14);
            list.Add(true);
            list.Add('男');
            list.Add(new int[] { 1, 2, 3 });

            for(int i = 0; i < list.Count; i++)
            {
                Console.WriteLine(list[i]);
            }


            //3.添加一系列元素(相当于python中的extend)
            list.AddRange(new int[] { 1, 2, 3, 4, 5 });
            list.AddRange(list);


            for (int i = 0; i < list.Count; i++)
            {
                Console.WriteLine(list[i]);
            }
            Console.ReadKey();

            //4. list.clear();清空所有元素
            //5. list.Remove(true);删除单个元素，写谁就删谁
            //6. list.RemoveAt(0);根据下标去删除元素
            //7. list.RemoveRange(0,3);根据下标范围内元素
            //8. list.Sort();升序排列（元素一定是相似类型的）
            //9. list.Reverse();反转
            //10. list.Insert(1,"插入的");在指定索引插入元素
            //11. list.InsertRange(0,new string[]{"张三","李四"});在指定位置插入一系列元素
            //12. list.Contains(1);判断是否包含元素
        }

    }
}
