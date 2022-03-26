using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/// <summary>
/// 如果你在一个方法中，返回多个相同类型的值的时候，可以考虑返回一个数组，
/// 但是，如果返回多个不同类型的值的时候，返回数组就不行了，那么这个时候，
/// 我们可以考虑使用out参数
/// </summary>
namespace _13_out参数
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            int max = 0;
            int min = 0;
            Test(numbers, out max, out min);//注意调用的时候,也要加入out

        }
        /// <summary>
        /// 计算数组的最大值最小值
        /// </summary>
        /// <param name="nums">数组</param>
        /// <param name="max">数组的最大值</param>
        /// <param name="min">数组的最小值</param>
        public static void Test(int[] nums,out int max,out int min)
        {
            max = nums[0];//在形参中定义，不要重新定义
            min = nums[0];
            for(int i = 0; i < nums.Length; i++)
            {
                max = max > nums[i] ? max : nums[i];
                min = min < nums[i] ? min : nums[i];
            }

        }
    }
}
//ref指定的参数在函数调用时候必须初始化，不能为空的引用。而out指定的参数在函数调用时候可以不初始化；
//out指定的参数在进入函数时会清空自己，必须在函数内部赋初值。而ref指定的参数不需要。