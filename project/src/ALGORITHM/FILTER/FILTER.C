#include "FILTER.H"
u16 filter(u16 *ary,u8 num,u16 MaxValue,u16 MinValue)
{
	int angleDataloopTemp2;
	u16 finalData=0;
	int maxValue = MinValue;
	int minValue = MaxValue;
	for (angleDataloopTemp2 = 0; angleDataloopTemp2 < num; angleDataloopTemp2++) //找出最大值和最小值
	{
		if (ary[angleDataloopTemp2] > maxValue) //去掉最大值最小值
		{
			maxValue = ary[angleDataloopTemp2];
		}
		if (ary[angleDataloopTemp2] < minValue) //去掉最大值最小值
		{
			minValue = ary[angleDataloopTemp2];
		}
		finalData += ary[angleDataloopTemp2];
	}
	finalData -= (maxValue + minValue);  //去掉最大值最小值
	finalData /= (num-2);	 //取平均值
	return finalData;
}
