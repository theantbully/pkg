// ���ر����������
// ����һ���ݹ�����, ��ת��Ϊ��ά�������ѭ��������
#include<iostream>
#include <algorithm>
// ���� http://new-play.tudou.com/v/448118973.html?f=38184740��
// �鿴Ϊʲô��Ʒ����Ϊnum_of_item-1, ������������Ϊpkg_total_weight-1
#define num_of_item 4 //��Ʒ����num_of_item-1
#define pkg_total_weight 15  //����������pkg_total_weight-1
#define  MIN(a,b)  (a)<(b)?a:b
using std::endl;
using std::cout;
using std::min;
using std::max;

int value[num_of_item][pkg_total_weight] = { 0 };
////��ÿ����Ʒ����Դ���ޣ� ���ڿ��ظ���ȡ�ķ�ʽ��, ֻ��2����Ʒ, CPU(value)���ڴ�(����)
int item_weight[num_of_item] = { 0,2,3,1} ; //�ڴ�
int item_value[num_of_item] = { 0,3,4,2 }; // ����CPU
int item_num[num_of_item] = {0,5,5,3}; //�������Ŀ

//int item_weight[num_of_item] = { 0,1,1,1,1,4,4,4,4,4 }; //�ڴ�
//int item_value[num_of_item] = { 0,5,5,5,5,5,5,5,5,5 }; // ����CPU

void pkg() {

	for (int item_index = 1; item_index < num_of_item; item_index++)
	{
		for (int C = 1; C < pkg_total_weight; C++) // C: Capacity
		{
			if (item_weight[item_index] > C)
			{
				value[item_index][C] = value[item_index - 1][C]; //̫�أ�װ����, ��͵, ��Ʒ��һ, ��������
			}
			else {//���أ�װ���£���ѡ��͵��͵
				// int k = (md == PKG01) ? 1 : (C) / item_weight[item_index];
				//��ÿ����Ʒ����Դ���ޣ� ���ڿ��ظ���ȡ�ķ�ʽ��, k=min( (C) / item_weight[item_index], Ni),
				//����NiΪ��i����Ʒ������, ���ڿ���С͵����ѡ��͵ȡ0~k֮����������, ��˻������k.
				int k = min(C / item_weight[item_index], item_num[item_index]);
				cout << "k=" << k << endl;
				int v1 = value[item_index - 1][C]; //��͵, ��ֵ����, ��������.
				value[item_index][C] = v1;
				//͵, ���ڿ���С͵����ѡ��͵ȡ0~k֮����������, ��˻������k.
				for (int m=1; m<=k; m++)
				{
					int v2 = value[item_index - 1][C - item_weight[item_index] *m] + m*item_value[item_index]; //͵, ��������it[item_index], ��ֵ����
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
				cout << "ѡ������Ʒ: " << item_index << "*" << m << "��\n";
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