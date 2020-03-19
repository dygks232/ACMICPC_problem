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
#define MAXN 100

void inputAndInit();
void solve();
void output();

int N, M;

int graph[MAXN + 1][MAXN + 1];

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
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			graph[i][j] = INF;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &u, &v, &d);
		graph[u][v] = min(graph[u][v], d);
	}
}

void solve()
{
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (k == i || graph[i][k] >= INF) continue;
			for (int j = 1; j <= N; j++)
			{
				if (j == k || j == i) continue;
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
}

void output()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			if (graph[i][j] < INF) printf("%d ", graph[i][j]);
			else printf("0 ");
		printf("\n");
	}
}
