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

int N, K, ansTime, ansMethod;
bool flag;

int visit[LIMIT + 1];
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
	ansMethod = 0;
	ansTime = -1;
	flag = false;
	memset(visit, -1, sizeof(visit));
}

void bfs()
{
	int currDist, currIdx, nextIdx;
	queue<pair<int, int> > Q;
	Q.push({ 0,N });
	visit[N] = 0;

	while (!Q.empty())
	{
		currDist = Q.front().first;
		currIdx = Q.front().second;
		Q.pop();

		if (currDist == ansTime)
			return;

		for (int d = 0; d < 2; d++)
		{
			nextIdx = currIdx + dir[d];
			if (nextIdx < 0 || nextIdx > LIMIT || (visit[nextIdx] != -1 && visit[nextIdx] < currDist + 1))
				continue;
			if (nextIdx == K)
			{
				if (!flag)
				{
					ansTime = currDist + 1;
					ansMethod++;
					flag = true;
				}
				else if (currDist + 1 == ansTime)
					ansMethod++;
			}
			visit[nextIdx] = currDist + 1;
			Q.push({ currDist + 1,nextIdx });
		}
		nextIdx = currIdx + currIdx;
		if (nextIdx > LIMIT || (visit[nextIdx] != -1 && visit[nextIdx] < currDist + 1))
			continue;
		if (nextIdx == K)
		{
			if (!flag)
			{
				ansTime = currDist + 1;
				ansMethod++;
				flag = true;
			}
			else if (currDist + 1 == ansTime)
				ansMethod++;
		}
		visit[nextIdx] = currDist + 1;
		Q.push({ currDist + 1,nextIdx });
	}
}

void solve()
{
	if(N != K)
		bfs();
	else
	{
		ansTime = 0;
		ansMethod = 1;
	}
}

void output()
{
	printf("%d\n%d\n", ansTime, ansMethod);
}