// 多重背包问题解析
// 这是一个递归问题, 可转化为二维数组进行循环遍历！
#include<iostream>
#include <algorithm>
// 访问 http://new-play.tudou.com/v/448118973.html?f=38184740，
// 查看为什么物品个数为num_of_item-1, 背包容量定义为pkg_total_weight-1
#define num_of_item 4 //物品个数num_of_item-1
#define pkg_total_weight 15  //背包总容量pkg_total_weight-1
#define  MIN(a,b)  (a)<(b)?a:b
using std::endl;
using std::cout;
using std::min;
using std::max;

int value[num_of_item][pkg_total_weight] = { 0 };
////若每类商品的资源有限， 则在可重复盗取的方式下, 只需2类商品, CPU(value)和内存(容重)
int item_weight[num_of_item] = { 0,2,3,1} ; //内存
int item_value[num_of_item] = { 0,3,4,2 }; // 初赛CPU
int item_num[num_of_item] = {0,5,5,3}; //虚拟机数目

//int item_weight[num_of_item] = { 0,1,1,1,1,4,4,4,4,4 }; //内存
//int item_value[num_of_item] = { 0,5,5,5,5,5,5,5,5,5 }; // 初赛CPU

void pkg() {

	for (int item_index = 1; item_index < num_of_item; item_index++)
	{
		for (int C = 1; C < pkg_total_weight; C++) // C: Capacity
		{
			if (item_weight[item_index] > C)
			{
				value[item_index][C] = value[item_index - 1][C]; //太重，装不下, 不偷, 商品减一, 容量不变
			}
			else {//不重，装得下，可选则偷或不偷
				// int k = (md == PKG01) ? 1 : (C) / item_weight[item_index];
				//若每类商品的资源有限， 则在可重复盗取的方式下, k=min( (C) / item_weight[item_index], Ni),
				//其中Ni为第i类商品的总数, 由于可以小偷可以选择偷取0~k之间的任意件数, 因此还需遍历k.
				int k = min(C / item_weight[item_index], item_num[item_index]);
				cout << "k=" << k << endl;
				int v1 = value[item_index - 1][C]; //不偷, 价值不变, 容量不变.
				value[item_index][C] = v1;
				//偷, 由于可以小偷可以选择偷取0~k之间的任意件数, 因此还需遍历k.
				for (int m=1; m<=k; m++)
				{
					int v2 = value[item_index - 1][C - item_weight[item_index] *m] + m*item_value[item_index]; //偷, 容量减少it[item_index], 价值增加
					if (v2 > value[item_index][C])
						value[item_index][C] = v2;
				}
			}
		}
	}

	int C = pkg_total_weight - 1;    
	for (int item_index = num_of_item - 1; item_index > 0; item_index--)
	{
		int k = min(C / item_weight[item_index], item_num[item_index]);
		for (int m = 1; m <= k; m++)
		{
			if (value[item_index][C] == value[item_index - 1][C - item_weight[item_index] * m] + m*item_value[item_index])
			{
				cout << "选择了商品: " << item_index << "*" << m << "件\n";
				C -= m* item_weight[item_index];
				break;
			}
		}
	}
	cout << endl;
}

int main()
{
	pkg();
	for (int idx = 0; idx < num_of_item; idx++)
	{
		for (int C = 0; C < pkg_total_weight; C++)
		{
			cout << value[idx][C] << " ";
		}
		cout << endl;
	}
	return 0;
}