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

void bfs();

int N, M, S, E, answer;

int visit[MAXN];
vector<pair<int, int> > link[MAXN];

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
	memset(visit, false, sizeof(visit));
	answer = INT_MAX;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d", &u, &v, &d);
		link[u - 1].push_back({ d,v - 1 });
		link[v - 1].push_back({ d,u - 1 });
	}
	scanf("%d %d", &S, &E);
	S--; E--;
}

void bfs()
{
	priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > PQ;
	int curr, next, weight, len;
	memset(visit, false, sizeof(visit));
	PQ.push({ INT_MAX,S });

	while (!PQ.empty())
	{
		weight = PQ.top().first;
		curr = PQ.top().second;
		visit[curr] = true;
		PQ.pop();
		if (curr == E)
		{
			answer = weight;
			return;
		}

		len = link[curr].size();
		for (int i = 0; i < len; i++)
		{
			next = link[curr][i].second;
			if (visit[next])
				continue;
			PQ.push({ min(link[curr][i].first,weight), next });
		}
	}
}

void solve()
{
	bfs();
}

void output()
{
	printf("%d\n", answer);
}