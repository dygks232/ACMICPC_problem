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

#define MAXN 100000

void inputAndInit();
void solve();
void output();

void makePreorder(int postL, int postR, int inL, int inR);

int N, idx;

int preorder[MAXN];
pair<int, int> inorder[MAXN];
int postorder[MAXN];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d", &N);
	idx = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &(inorder[i].first));
		inorder[i].second = i;
	}
	for (int i = 0; i < N; i++)
		scanf("%d", &postorder[i]);
}

void makePreorder(int postL, int postR, int inL, int inR)
{
	int inM, lenL, lenR;
	preorder[idx++] = postorder[postR];
	inM = inorder[postorder[postR] - 1].second;
	lenL = inM - inL;
	lenR = inR - inM;

	if(lenL)
		makePreorder(postL, postL + lenL - 1, inL, inM - 1);
	if(lenR)
		makePreorder(postL + lenL, postL + lenL + lenR - 1, inM + 1, inR);
}

void solve()
{
	sort(inorder, inorder + N);
	makePreorder(0, N - 1, 0, N - 1);
}

void output()
{
	for (int i = 0; i < N; i++)
		printf("%d ", preorder[i]);
}
