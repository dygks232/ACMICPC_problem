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

void bfs();

int N, K, answer;

bool visit[LIMIT + 1];
int dir[2] = { -1,1 };

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d %d", &N, &K);
	answer = 0;
	memset(visit, false, sizeof(visit));
}

void bfs()
{
	int currDist, currIdx, nextIdx;
	queue<pair<int, int> > Q;
	Q.push({ 0,N });
	visit[N] = true;

	while (!Q.empty())
	{
		currDist = Q.front().first;
		currIdx = Q.front().second;
		Q.pop();

		for (int d = 0; d < 2; d++)
		{
			nextIdx = currIdx + dir[d];
			if (nextIdx < 0 || nextIdx > LIMIT || visit[nextIdx])
				continue;
			if (nextIdx == K)
			{
				answer = currDist + 1;
				return;
			}
			visit[nextIdx] = true;
			Q.push({ currDist + 1,nextIdx });
		}
		nextIdx = currIdx + currIdx;
		if (nextIdx > LIMIT || visit[nextIdx])
			continue;
		if (nextIdx == K)
		{
			answer = currDist + 1;
			return;
		}
		visit[nextIdx] = true;
		Q.push({ currDist + 1,nextIdx });
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