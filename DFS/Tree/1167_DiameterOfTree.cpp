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

#define LIMIT 100000

void inputAndInit();
void solve();
void output();

void dfs(int idx);

int N, answer, startIdx;

bool visit[LIMIT + 1];

vector<pair<int, int> > link[LIMIT + 1];

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
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &u);
		while (1)
		{
			scanf("%d", &v);
			if (v == -1)
				break;
			scanf("%d", &d);
			link[u].push_back({ v,d });
		}
	}
}

void dfs(int idx)
{
	stack<pair<int, int> > STACK;
	int curr, currDist, nextDist, len;
	memset(visit, false, N + 1);
	visit[idx] = true;
	STACK.push({ 0,idx });
	answer = 0;

	while (!STACK.empty())
	{
		currDist = STACK.top().first;
		curr = STACK.top().second;
		STACK.pop();

		len = link[curr].size();
		for (int i = 0; i < len; i++)
		{
			if (visit[link[curr][i].first])
				continue;
			nextDist = currDist + link[curr][i].second;
			if (answer < nextDist)
			{
				answer = nextDist;
				startIdx = link[curr][i].first;
			}
			visit[link[curr][i].first] = true;
			STACK.push({ nextDist, link[curr][i].first });
		}
	}
}

void solve()
{
	dfs(1);
	dfs(startIdx);
}

void output()
{
	printf("%d\n", answer);
}
