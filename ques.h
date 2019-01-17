#include <stack>
#include <iostream>
using std::stack;
using std::cout;
//古尼吉娃
struct LNode { int val; LNode* next; };

//1 - 仅用递归实现stack的反转
int getRemoveLast(stack<int> &S) {
	int result = S.top();
	S.pop();
	if (S.empty())
	{
		return	result;
	}
	else {
		int last = getRemoveLast(S);
		S.push(result);
		return last;
	}
}

void reverse(stack<int>&S) {
	if (S.empty())
	{
		return;
	}
	else
	{
		int i = getRemoveLast(S);
		reverse(S);
		S.push(i);
	}
}


//2 - 汉诺塔 ***
void HN(int n, char A, char B, char C)
{
	if (n == 0)
		return;
	HN(n - 1, A, C, B); // 借助C, 将n-1个圆环从A移到B, A->C->B
	cout << "move " << n << " from " << A << " to " << C << '\n'; // A的最后一个圆环, 从A到C
	HN(n - 1, B, A, C); // 借助A, 将n-1个圆环从B移到C, B->A->C
}

//4-单链表反转 ***
LNode* reverseLNode(LNode* head) {
	LNode* pre = nullptr;
	LNode* after = nullptr;
	while (head != nullptr)
	{
		after = pre;
		pre = head;
		//下面两句先后顺序不能颠倒
		head = head->next;
		pre->next = after;
	}
	return pre;
}

//5 - 反转链表部分区域： from->end
LNode* reverseLNode(LNode* head, int from, int end) {
	LNode* hh = head, *hhh = hh;;
	LNode* pre = nullptr;
	LNode* after = nullptr;
	LNode* left1 = nullptr, *left2 = left1;
	LNode* right1 = nullptr, *right2 = right1;
	int i;
	for (i = 1; hhh != nullptr; i++)
	{
		hhh = hhh->next;
	}
	if (i < end + 1 && hhh == nullptr)
		return hh;

	for (int i = 1; i <= end; i++)
	{
		if (i < from)
		{
			if (i == from - 1)
			{
				left1 = head;
				left2 = head->next;
			}
			head = head->next;
		}
		else
		{
			if (i == end)
			{
				right1 = head;
				right2 = head->next;
			}
			after = pre;
			pre = head;
			head = head->next;
			pre->next = after;
		}
	}
	left1->next = right1;
	left2->next = right2;
	return hh;
}

bool isHuiWenLink(LNode* head) {
	LNode* hh = head, *hhh = hh;
	int i;  //链表长度
	for (i = 0; hhh != nullptr; i++)
	{
		hhh = hhh->next;
	}

	for (int j = 1; j < i / 2 + 1; j++)
	{
		LNode* a = head;
		LNode* b = hh;
		head = head->next;

		for (int k = 1; k < i - j + 1; k++)
		{
			b = b->next;
		}
		if (a->val == b->val)
			continue;
		else
			return false;
	}
	return true;
}

//6-2个链表数字求和
//先将2链表反转, 再从左至右求和(注意进位), 将结果再反转即可
LNode* addedLK(LNode* head1, LNode* head2) {
	LNode* head = nullptr, *h = nullptr, *pre;
	head1 = reverseLNode(head1);
	head2 = reverseLNode(head2);
	LNode* h1 = head1;
	LNode* h2 = head2;

	int jinwei = 0, remind = 0;
	int i = 0;
	while (true)
	{
		if (head1 != nullptr && head2 != nullptr)
		{
			int V = (head1->val + head2->val + jinwei);
			jinwei = V >= 10;
			remind = jinwei > 0 ? (V - 10) : V;
			pre = new LNode();
			if (i == 0)
			{
				h = pre; i++;
			}
			pre->val = remind;
			pre->next = nullptr;
			if (head == nullptr)
				head = pre;
			else
			{
				head->next = pre;
				head = head->next;
			}
			head1 = head1->next;
			head2 = head2->next;
		}
		else if (head1 == nullptr)
		{
			while (head2 != nullptr)
			{
				int V = (head2->val + jinwei);
				jinwei = V >= 10;
				remind = jinwei > 0 ? (V - 10) : V;

				pre = new LNode();
				pre->val = remind;
				pre->next = nullptr;
				head->next = pre;
				head = head->next;
				head2 = head2->next;
			}
			break;
		}
		else if (head2 == nullptr)
		{
			while (head1 != nullptr)
			{
				int V = (head1->val + jinwei);
				jinwei = V >= 10;
				remind = jinwei > 0 ? (V - 10) : V;

				pre = new LNode();
				pre->val = remind;
				pre->next = nullptr;
				head->next = pre;
				head = head->next;
				head1 = head1->next;
			}
			break;
		}
	}

	if (jinwei > 0)
	{
		pre = new LNode();
		pre->val = jinwei;
		pre->next = nullptr;
		head->next = pre;
		head = head->next;
	}
	h = reverseLNode(h);
	return h;
}


double min(double a, double b) { return a > b ? b : a; }
//7-矩阵最小路径: 左上角->右下角
void DP() {
	//方法1: 二维矩阵, 填表
	//vector<int> vvec = { 0,0,0,0 };
	//vector<vector<int> > Map;
	//for (int i = 0; i < 4; i++)
	//	Map.push_back(vvec);

	//vvec = vector<int>{ 1,4,9,18 };
	//for (int i = 0; i < 4; i++)
	//	Map[0][i] = vvec[i];

	//vvec = vector<int>{ 1, 9, 14, 22 };
	//for (int i = 0; i < 4; i++)
	//	Map[i][0] = vvec[i];

	//for (int i = 1; i < 4;i++)
	//	for (int j = 1; j < 4; j++)
	//	{
	//		int M = (int)min(Map[i - 1][j], Map[i][j - 1]);
	//		Map[i][j] = M + vec[i][j];
	//	}

	//for (int i = 0; i < 4;i++)
	//{

	//	for (int j = 0; j < 4; j++)
	//		cout << Map[i][j] << "   ";
	//	cout << '\n';
	//}
	

	//方法二: 一维向量动态扫描-覆盖
	//vector<int> vvec ={ 1,4,9,18 };
	//for (int i = 1; i < 4;i++)
	//{	// vvec: (i-1, *)

	//	vvec[0] = vvec[0] + vec[i][0]; //本行计算: vvec[i,0]
	//	for (int j = 1; j < 4; j++)
	//	{   // vvec[i,j] = min( vvec[i-1, j], vvec[i,j-1] ) + vec[i][j]
	//		int M = (int)min(vvec[j] , vvec[j - 1]) + vec[i][j];
	//		vvec[j] = M;
	//	}
	//}
	return;
}

//8-最大递增数字子序列
//时间复杂度O(N^2)
int maxLenSubList(int a[]) {
	//for (int i = 0; i < 9; i++)
	//{
	//	dp[i] = 1;
	//	for (int j = 0; j < i; j++)
	//	{
	//		if (a[i] > a[j])
	//			dp[i] = dp[j] + 1;
	//	}
	//}
	return 0;//dp[8];
}


//9-动态规划的套路:
// 子问题分解->dp表的第一行、第一列初始化
// -> 从上至下、从左至右填写dp表
int maxLenCommonSubStr(char str1[], char str2[]) {
	//最长公共子序列, 不需要子序列的元素紧邻
	/*dp[0][0] = str1[0] == str2[0] ? 1 : 0;

	for (int i = 1; i < strlen(str1); i++)
	{
		if (str1[i] == str2[0])
			dp[i][0] = 1;
		else
			dp[i][0] = dp[i - 1][0];
	}

	for (int i = 0; i < strlen(str2); i++)
	{
		if (str1[0] == str2[i])
			dp[0][i] = 1;
		else
			dp[0][i] = dp[0][i - 1];
	}

	for (int i = 1; i < strlen(str1); i++)
	{
		for (int j = 1; j < strlen(str2); j++)
		{
			int a = max(dp[i - 1][j], dp[i][j - 1]);
			dp[i][j] = max(a, dp[i - 1][j - 1] + (str1[i] == str2[j]));
		}
	}*/
	return 0;// dp[9][11];
}

//10- 子串的字符必须紧邻
int maxCommonSubStr(char str1[], char str2[]) {
	int dp[11][11] = { 0 };  //row: str1, col:str2
	dp[0][0] = str1[0] == str2[0] ? 1 : 0;

	for (int i = 1; i < strlen(str1); i++)
		dp[i][0] = str1[i] == str2[0];

	for (int i = 0; i < strlen(str2); i++)
		dp[0][i] = str1[0] == str2[i];

	for (int i = 1; i < strlen(str1); i++)
		for (int j = 1; j < strlen(str2); j++)
			if (str1[i] == str2[j])
				dp[i][j] = dp[i - 1][j - 1] + 1;

	return 0;
}

//11- a[i]==k:表示从a[i]可以前跳[1~k]步, 求到a末尾的最短步数
int JumpSteps(int a[])
{
	int jump = 0, next = 0, current = 0;
	//cout << 1 << "->";
	//for (int i = 0; i < N; i++)
	//{
	//	if (current < i) {
	//		jump++;
	//		current = next;
	//		cout << next << "->";
	//	}
	//	next = max(i + a[i], next); //遍历a, 选择最远可到的下一步
	//}
	return jump;
}

//12- std::qsort使用方法
void QSORT(int arr[]) {
	// int arr[] = { 100, 4,  103, 200,  104, 5,1, 2, 105, 3, 101, 102 };
	std::qsort(arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), [](const void  * aa, const  void  * bb) {	return *(int*)aa - *(int*)bb; });
}

//13-位运算-不用比较, 求出2整数数的较大值
int max_int(int a, int b) {

	int c = a - b;
	bool signa = (a >> 31) & 0x01;
	bool signb = (b >> 31) & 0x01;
	bool signc = (c >> 31) & 0x01;
	bool dif_ab = signa^signb;  //判断a、b是否异号

	int s1 = (1 - dif_ab)*((1 - signc)*a + signc*b);// a、b同号, dif_ab==0
	int s2 = dif_ab*((1 - signa)*a + (1 - signb)*b);//a、b异号, dif_ab==1, 必有一正一负, 留下正数
	return s1 + s2;

}
