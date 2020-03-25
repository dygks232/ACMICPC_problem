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

#define MAXN 10000

void inputAndInit();
void solve();
void output();

void makePostorder(int start, int end);

int N, idx;

int preorder[MAXN + 1];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	N = 0;
	while (scanf("%d", &preorder[N++]) != EOF);
}

void makePostorder(int start, int end)
{
	if (start == end)
		return;
	if (start == end - 1)
	{
		printf("%d\n", preorder[start]);
		return;
	}
	int idx = start + 1;
	while (1)
	{
		if (!(idx < end && preorder[idx] < preorder[start]))
			break;
		idx++;
	}
	makePostorder(start + 1, idx);
	makePostorder(idx, end);
	printf("%d\n", preorder[start]);
}

void solve()
{
	makePostorder(0, N - 1);
}

void output()
{

}
