#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<deque>
#include<functional>
using namespace std;

#define WALL -1
#define BLANK 0
#define TARGET1 1
#define TARGET2 2
#define DOOR 3

void inputAndInit();
void solve();
void output();

bool isOutOfBoundary(int r, int c);
void bfs();

int T, R, C, answer;

int board[102][102];
int dist[3][102][102];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<pair<int, int> > targetPos;

int main()
{
	scanf("%d", &T);
	while(T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

void inputAndInit()
{
	char in;
	int temp = 0;
	scanf("%d %d", &R, &C);
	answer = INT_MAX;
	targetPos.assign(3, { 0,0 });
	memset(board, 0, sizeof(board));
	for (int r = 1; r <= R; r++)
	{
		scanf("%c", &in);
		for (int c = 1; c <= C; c++)
		{
			scanf("%c", &in);
			switch (in)
			{
			case '.':
				board[r][c] = BLANK;
				break;
			case '*':
				board[r][c] = WALL;
				break;
			case '#':
				board[r][c] = DOOR;
				break;
			case '$':
				targetPos[temp] = { r,c };
				board[r][c] = ++temp;
				break;
			}
		}
	}
}

void solve()
{
	int temp;
	bfs();
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			if (board[r][c] == WALL)
				continue;
			temp = 0;
			for (int i = 0; i < 3; i++)
				temp += dist[i][r][c];
			if (board[r][c] == DOOR)
				temp -= 2;
			answer = min(answer, temp);
		}
	}
}

void output()
{
	printf("%d\n", answer);
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r > R + 1 || c > C + 1 || board[r][c] == WALL;
}

void bfs()
{
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > PQ;
	int currR, currC, nextR, nextC, currDist;
	memset(dist, -1, sizeof(dist));

	for (int i = 0; i < 3; i++)
	{
		PQ.push({ 0,targetPos[i] });
		dist[i][targetPos[i].first][targetPos[i].second] = 0;

		while (!PQ.empty())
		{
			currR = PQ.top().second.first;
			currC = PQ.top().second.second;
			currDist = PQ.top().first;
			PQ.pop();

			for (int dir = 0; dir < 4; dir++)
			{
				nextR = currR + dirR[dir];
				nextC = currC + dirC[dir];
				if (isOutOfBoundary(nextR, nextC) || dist[i][nextR][nextC] != -1)
					continue;

				if (board[nextR][nextC] == DOOR)
				{
					dist[i][nextR][nextC] = currDist + 1;
					PQ.push({ currDist + 1,{nextR,nextC} });
				}
				else
				{
					dist[i][nextR][nextC] = currDist;
					PQ.push({ currDist,{nextR,nextC} });					
				}
			}
		}
	}
}