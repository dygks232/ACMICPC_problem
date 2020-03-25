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

#define MAXN 102

void inputAndInit();
void solve();
void output();

int calcDist(int idx1, int idx2);
void dijkstra();

int T, N;

vector<pair<int, int> > cost[MAXN];
pair<int, int> pos[MAXN];
int dist[MAXN];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

int calcDist(int idx1, int idx2)
{
	return abs(pos[idx1].first - pos[idx2].first) + abs(pos[idx1].second - pos[idx2].second);
}

void inputAndInit()
{
	int d;
	scanf("%d", &N);
	N += 2;
	for (int i = 0; i < N; i++)
		cost[i].clear();
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &pos[i].first, &pos[i].second);
		dist[i] = INT_MAX;
		for (int j = 0; j < i; j++)
		{
			if ((d = calcDist(i, j)) <= 1000)
			{
				cost[i].push_back({ d,j });
				cost[j].push_back({ d,i });
			}
		}
	}
	dist[0] = 0;
}

void dijkstra()
{
	int curr, currCost, next, nextCost, size;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PQ;
	PQ.push({ 0,0 });

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
	dijkstra();
}

void output()
{
	if (dist[N - 1] < INT_MAX)
		printf("happy\n");
	else
		printf("sad\n");
}