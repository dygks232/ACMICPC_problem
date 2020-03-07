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

#define BLANK 0
#define WATER 1
#define WALL 2
#define END 3

void inputAndInit();
void solve();
void output();

bool isOutOfRange(int r, int c);
void makeWaterMap();
void bfs();

int R, C, answer, sr, sc, er, ec;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<vector<int> > board;
vector<vector<int> > water;
vector<vector<bool> > visit;
queue<pair<int, pair<int,int> > > waterQ;

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

void inputAndInit()
{
	char in[51];
	scanf("%d %d", &R, &C);
	answer = -1;
	water.assign(R, vector<int>(C, INT_MAX));
	board.assign(R, vector<int>(C, 0));
	visit.assign(R, vector<bool>(C, false));
	for (int r = 0; r < R; r++)
	{
		scanf("%s", in);
		for (int c = 0; c < C; c++)
		{
			switch (in[c])
			{
			case 'S':
				sr = r; sc = c;
			case '.':
				board[r][c] = BLANK;
				break;
			case '*':
				board[r][c] = WATER;
				waterQ.push({ 0,{r,c} });
				water[r][c] = 0;
				break;
			case 'X':
				board[r][c] = WALL;
				break;
			case 'D':
				board[r][c] = END;
				er = r; ec = c;
				break;
			}
		}
	}
	makeWaterMap();
}

void makeWaterMap()
{
	int currR, currC, nextR, nextC, currDist;

	while (!waterQ.empty())
	{
		currR = waterQ.front().second.first;
		currC = waterQ.front().second.second;
		currDist = waterQ.front().first;
		waterQ.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || water[nextR][nextC] != INT_MAX || board[nextR][nextC] >= WALL)
				continue;
			water[nextR][nextC] = currDist + 1;
			waterQ.push({ currDist + 1,{nextR,nextC} });
		}
	}
}

void bfs()
{
	int currR, currC, nextR, nextC, currDist;
	queue<pair<int, pair<int, int> > > Q;
	visit[sr][sc] = true;
	Q.push({ 0,{sr,sc} });

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
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC] || board[nextR][nextC] == WALL || water[nextR][nextC] <= currDist + 1)
				continue;
			if (board[nextR][nextC] == END)
			{
				answer = currDist + 1;
				return;
			}
			visit[nextR][nextC] = true;
			Q.push({ currDist + 1,{nextR,nextC} });
		}
	}
}

void solve()
{
	bfs();
}

void output()
{
	if (answer != -1)
		printf("%d\n", answer);
	else
		printf("KAKTUS\n");
}