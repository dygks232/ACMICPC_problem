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

#define INF 555555555
#define MAXN 1000

void inputAndInit();
void solve();
void output();

void floyd();

int N, M, X, answer;

int adj[MAXN + 1][MAXN + 1];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int u, v, d;
	scanf("%d %d %d", &N, &M, &X);
	answer = INT_MIN;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			adj[i][j] = INF;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &u, &v, &d);
		adj[u][v] = min(adj[u][v], d);
	}
}

void floyd()
{
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (i == k || adj[i][k] >= INF)
				continue;
			for (int j = 1; j <= N; j++)
			{
				if (j == i || j == k)
					continue;
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
}

void solve()
{
	floyd();
	for (int i = 1; i <= N; i++)
	{
		if (i == X) continue;
		answer = max(answer, adj[i][X] + adj[X][i]);
	}
}

void output()
{
	printf("%d\n", answer);
}