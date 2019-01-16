#include <stack>
#include <iostream>
using std::stack;
using std::cout;

struct LNode { int val; LNode* next; };

//1 - ���õݹ�ʵ��stack�ķ�ת
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


//2 - ��ŵ�� ***
void HN(int n, char A, char B, char C)
{
	if (n == 0)
		return;
	HN(n - 1, A, C, B); // ����C, ��n-1��Բ����A�Ƶ�B, A->C->B
	cout << "move " << n << " from " << A << " to " << C << '\n'; // A�����һ��Բ��, ��A��C
	HN(n - 1, B, A, C); // ����A, ��n-1��Բ����B�Ƶ�C, B->A->C
}

//4-������ת ***
LNode* reverseLNode(LNode* head) {
	LNode* pre = nullptr;
	LNode* after = nullptr;
	while (head != nullptr)
	{
		after = pre;
		pre = head;
		//���������Ⱥ�˳���ܵߵ�
		head = head->next;
		pre->next = after;
	}
	return pre;
}

//5 - ��ת���������� from->end
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
	int i;  //������
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

//6-2�������������
//�Ƚ�2����ת, �ٴ����������(ע���λ), ������ٷ�ת����
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
//7-������С·��: ���Ͻ�->���½�
void DP() {
	//����1: ��ά����, ���
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
	

	//������: һά������̬ɨ��-����
	//vector<int> vvec ={ 1,4,9,18 };
	//for (int i = 1; i < 4;i++)
	//{	// vvec: (i-1, *)

	//	vvec[0] = vvec[0] + vec[i][0]; //���м���: vvec[i,0]
	//	for (int j = 1; j < 4; j++)
	//	{   // vvec[i,j] = min( vvec[i-1, j], vvec[i,j-1] ) + vec[i][j]
	//		int M = (int)min(vvec[j] , vvec[j - 1]) + vec[i][j];
	//		vvec[j] = M;
	//	}
	//}
	return;
}

//8-����������������
//ʱ�临�Ӷ�O(N^2)
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


//9-��̬�滮����·:
// ������ֽ�->dp��ĵ�һ�С���һ�г�ʼ��
// -> �������¡�����������дdp��
int maxLenCommonSubStr(char str1[], char str2[]) {
	//�����������, ����Ҫ�����е�Ԫ�ؽ���
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

//10- �Ӵ����ַ��������
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

//11- a[i]==k:��ʾ��a[i]����ǰ��[1~k]��, ��aĩβ����̲���
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
	//	next = max(i + a[i], next); //����a, ѡ����Զ�ɵ�����һ��
	//}
	return jump;
}

//12- std::qsortʹ�÷���
void QSORT(int arr[]) {
	// int arr[] = { 100, 4,  103, 200,  104, 5,1, 2, 105, 3, 101, 102 };
	std::qsort(arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), [](const void  * aa, const  void  * bb) {	return *(int*)aa - *(int*)bb; });
}

//13-λ����-���ñȽ�, ���2�������Ľϴ�ֵ
int max_int(int a, int b) {

	int c = a - b;
	bool signa = (a >> 31) & 0x01;
	bool signb = (b >> 31) & 0x01;
	bool signc = (c >> 31) & 0x01;
	bool dif_ab = signa^signb;  //�ж�a��b�Ƿ����

	int s1 = (1 - dif_ab)*((1 - signc)*a + signc*b);// a��bͬ��, dif_ab==0
	int s2 = dif_ab*((1 - signa)*a + (1 - signb)*b);//a��b���, dif_ab==1, ����һ��һ��, ��������
	return s1 + s2;

}
