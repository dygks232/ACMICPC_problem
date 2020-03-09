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
void makeAnswer();

int N, K, ansTime;

bool visit[LIMIT + 1];
int dir[2] = { -1,1 };

vector<int> visitIdx[LIMIT + 1];
stack<int> answer;

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
	ansTime = -1;
	memset(visit, false, sizeof(visit));
}

void makeAnswer()
{
	int temp = ansTime, size, backtrace = K, curr;
	answer.push(K);
	while (temp)
	{
		size = visitIdx[temp - 1].size();
		for (int i = 0; i < size; i++)
		{
			curr = visitIdx[temp - 1][i];
			if (curr == backtrace - 1 || curr == backtrace + 1 || curr + curr == backtrace)
			{
				answer.push(curr);
				backtrace = curr;
				break;
			}
		}
		temp--;
	}
}

void bfs()
{
	int currDist, currIdx, nextIdx;
	queue<pair<int, int> > Q;
	Q.push({ 0,N });
	visitIdx[0].push_back(N);
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
				ansTime = currDist + 1;
				makeAnswer();
				return;
			}
			visit[nextIdx] = true;
			visitIdx[currDist + 1].push_back(nextIdx);
			Q.push({ currDist + 1,nextIdx });
		}
		nextIdx = currIdx + currIdx;
		if (nextIdx > LIMIT || visit[nextIdx])
			continue;
		if (nextIdx == K)
		{
			ansTime = currDist + 1;
			makeAnswer();
			return;
		}
		visit[nextIdx] = true;
		visitIdx[currDist + 1].push_back(nextIdx);
		Q.push({ currDist + 1,nextIdx });
	}
}

void solve()
{
	if (N != K)
		bfs();
	else
	{
		ansTime = 0;
		answer.push(N);
	}
}

void output()
{
	printf("%d\n", ansTime);
	while (!answer.empty())
	{
		printf("%d ", answer.top());
		answer.pop();
	}
}