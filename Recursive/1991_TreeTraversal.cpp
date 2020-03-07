#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<algorithm>
#include<cmath>
#include<climits>
#include<set>
#include<map>
#include<string>
#include<cstring>
#include<functional>
using namespace std;

void inputAndInit();
void solve();
void output();

void preorder(int curr);
void inorder(int curr);
void postorder(int curr);

int N;

char tree[500];
int idx[500];

int main()
{
	inputAndInit();
	//solve();
	output();
	return 0;
}

void inputAndInit()
{
	char in[6];
	int parent;
	char temp;
	scanf("%d", &N);
	scanf("%1c", &temp);
	tree[0] = 'A';
	idx[0] = 0;
	for (int i = 0; i < N; i++)
	{
		cin.getline(in, 6);
		parent = idx[in[0] - 'A'];
		tree[parent * 2 + 1] = in[2];
		tree[parent * 2 + 2] = in[4];
		if (in[2] != '.')
			idx[in[2] - 'A'] = parent * 2 + 1;
		if (in[4] != '.')
			idx[in[4] - 'A'] = parent * 2 + 2;
	}
}

void preorder(int curr)
{
	int left = curr * 2 + 1;
	int right = left + 1;
	printf("%c", tree[curr]);
	if (tree[left] != '.')
		preorder(left);
	if (tree[right] != '.')
		preorder(right);
}

void inorder(int curr)
{
	int left = curr * 2 + 1;
	int right = left + 1;
	if (tree[left] != '.')
		inorder(left);
	printf("%c", tree[curr]);
	if (tree[right] != '.')
		inorder(right);
}

void postorder(int curr)
{
	int left = curr * 2 + 1;
	int right = left + 1;
	if (tree[left] != '.')
		postorder(left);
	if (tree[right] != '.')
		postorder(right);
	printf("%c", tree[curr]);
}

void solve()
{

}

void output()
{
	preorder(0);
	printf("\n");
	inorder(0);
	printf("\n");
	postorder(0);
	printf("\n");
}
