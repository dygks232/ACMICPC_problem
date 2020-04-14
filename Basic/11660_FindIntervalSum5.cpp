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

#define MAXN 1024

void inputAndInit();
void solve();
void output();

int calcAns(int r1, int c1, int r2, int c2);

int N, M, answer;

int prefixSum[MAXN + 1][MAXN + 1] = { 0, };

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int in;
	scanf("%d %d", &N, &M);
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &in);
			prefixSum[r][c] = prefixSum[r - 1][c] + prefixSum[r][c - 1] - prefixSum[r - 1][c - 1] + in;
		}
	}
}

int calcAns(int r1, int c1, int r2, int c2)
{
	return prefixSum[r2][c2] - prefixSum[r1 - 1][c2] - prefixSum[r2][c1 - 1] + prefixSum[r1 - 1][c1 - 1];
}

void solve()
{

}

void output()
{
	int r1, c1, r2, c2;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		printf("%d\n", calcAns(r1, c1, r2, c2));
	}
}