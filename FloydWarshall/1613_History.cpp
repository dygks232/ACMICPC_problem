#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<deque>
#include<functional>
using namespace std;

#define INF 555555555

void inputAndInit();
void solve();
void output();

void floyd();

int N, K, S;

int graph[401][401];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int in1, in2;
	scanf("%d %d", &N, &K);
	memset(graph, 0, sizeof(graph));
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			graph[r][c] = INF;
	for (int i = 0; i < K; i++)
	{
		scanf("%d %d", &in1, &in2);
		graph[in1][in2] = 1;
	}
}

void solve()
{
	floyd();
}

void output()
{
	int in1, in2;
	scanf("%d", &S);
	for (int i = 0; i < S; i++)
	{
		scanf("%d %d", &in1, &in2);
		if(graph[in1][in2] == INF && graph[in2][in1] == INF)
			printf("0\n");
		else if (graph[in1][in2] > 0 && graph[in2][in1] == INF)
			printf("-1\n");
		else if (graph[in2][in1] > 0 && graph[in1][in2] == INF)
			printf("1\n");
		else
			printf("0\n");
	}
}

void floyd()
{
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			if (k == i || graph[i][k] >= INF)
				continue;
			for (int j = 1; j <= N; j++)
			{
				if (j == k || j == i)
					continue;
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
}