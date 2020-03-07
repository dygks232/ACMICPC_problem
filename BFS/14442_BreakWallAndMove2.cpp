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

void inputAndInit();
void solve();
void output();

bool isOutOfRange(int r, int c);
void bfs();

int R, C, K, answer;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<vector<bool> > board;
vector<vector<bool> > visit[11];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

void bfs()
{
	short currR, currC, nextR, nextC;
	int currDist;
	int flag;
	queue<pair<pair<int, int>, pair<short, short> > > Q;
	visit[0][0][0] = true;
	Q.push({ {1,0},{0,0} });

	while (!Q.empty())
	{
		currR = Q.front().second.first;
		currC = Q.front().second.second;
		currDist = Q.front().first.first;
		flag = Q.front().first.second;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC))
				continue;
			if (visit[flag][nextR][nextC])
				continue;
			if (flag && visit[flag - 1][nextR][nextC])
				continue;

			if (nextR == R - 1 && nextC == C - 1)
			{
				answer = currDist + 1;
				return;
			}

			if (flag == K && board[nextR][nextC])
				continue;

			if (!board[nextR][nextC])
			{
				visit[flag][nextR][nextC] = true;
				Q.push({ {currDist + 1,flag},{nextR,nextC} });
			}
			else if (flag < K)
			{
				visit[flag + 1][nextR][nextC] = true;
				Q.push({ {currDist + 1,flag + 1},{nextR,nextC} });
			}
		}
	}
}

void inputAndInit()
{
	int in;
	scanf("%d %d %d", &R, &C, &K);
	answer = -1;
	board.assign(R, vector<bool>(C, false));
	for (int i = 0; i < 11; i++)
		visit[i].assign(R, vector<bool>(C, false));
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			scanf("%1d", &in);
			board[r][c] = in;
		}
	}
}

void solve()
{
	bfs();
	if (R == C && R == 1)
		answer = 1;
}

void output()
{
	printf("%d\n", answer);
}