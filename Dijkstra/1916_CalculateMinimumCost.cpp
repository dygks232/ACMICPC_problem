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

#define MAXV 1000

void inputAndInit();
void solve();
void output();

void dijkstra(int s);

int N, M, S, E;

vector<pair<int, int> > cost[MAXV];
vector<int> dist;

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
	dist.assign(N, INT_MAX);
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &u, &v, &d);
		cost[u - 1].push_back({ d,v - 1 });
	}
	scanf("%d %d", &S, &E);
	dist[S - 1] = 0;
}

void dijkstra(int s)
{
	int curr, currCost, next, nextCost, size;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PQ;
	PQ.push({ 0,s });

	while (!PQ.empty())
	{
		currCost = PQ.top().first;
		curr = PQ.top().second;
		PQ.pop();

		if (currCost > dist[curr])
			continue;

		size = cost[curr].size();
		for (int i = 0; i < size; i++)
		{
			nextCost = cost[curr][i].first + currCost;
			next = cost[curr][i].second;
			if (nextCost < dist[next])
			{
				dist[next] = nextCost;
				PQ.push({ nextCost,next });
			}
		}
	}
}

void solve()
{
	dijkstra(S - 1);
}

void output()
{
	printf("%d\n", dist[E - 1]);
}
