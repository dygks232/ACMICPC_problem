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

void inputAndInit();
void solve();
void output();

bool isOutOfRange(int r, int c);
void bfs(int r, int c);

int N, answer;

int board[100][100];
bool visit[100][100];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<pair<int, int> > landPos;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d", &N);
	answer = INT_MAX;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &board[r][c]);
			if (board[r][c])
				landPos.push_back({ r,c });
		}
	}
}

void solve()
{
	bool isStart;
	int len = landPos.size(), nextR, nextC;
	for (int i = 0; i < len; i++)
	{
		isStart = false;
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = landPos[i].first + dirR[dir];
			nextC = landPos[i].second + dirC[dir];
			if (isOutOfRange(nextR, nextC))
				continue;
			if (!board[nextR][nextC])
			{
				isStart = true;
				break;
			}
		}
		if(isStart)
			bfs(landPos[i].first, landPos[i].second);
	}
}

void output()
{
	printf("%d\n", answer);
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= N || c >= N;
}

void bfs(int r, int c)
{
	queue<pair<int, pair<int, int> > > Q;
	int currR, currC, nextR, nextC, currDist;

	memset(visit, false, sizeof(visit));
	visit[r][c] = true;
	Q.push({ 0,{r,c} });
	while (!Q.empty())
	{
		currR = Q.front().second.first;
		currC = Q.front().second.second;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC] || !board[nextR][nextC])
				continue;
			visit[nextR][nextC] = true;
			Q.push({ 0,{nextR,nextC} });
		}
	}

	Q.push({ 0,{r,c} });
	while (!Q.empty())
	{
		currR = Q.front().second.first;
		currC = Q.front().second.second;
		currDist = Q.front().first;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC])
				continue;

			if (board[nextR][nextC])
			{
				answer = min(answer, currDist);
				return;
			}

			visit[nextR][nextC] = true;
			Q.push({ currDist + 1,{nextR,nextC} });
		}
	}
}