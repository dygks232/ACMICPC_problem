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
void bfs1(int r, int c);
void bfs2(int r, int c);

int N, answer1, answer2;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<vector<int> > board1;
vector<vector<bool> > visit1, visit2, board2;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= N || c >= N;
}

void inputAndInit()
{
	char in[101];
	scanf("%d", &N);
	answer1 = answer2 = 0;
	board1.assign(N, vector<int>(N, 0));
	board2.assign(N, vector<bool>(N, false));
	visit1.assign(N, vector<bool>(N, false));
	visit2.assign(N, vector<bool>(N, false));
	for (int r = 0; r < N; r++)
	{
		scanf("%s", in);
		for (int c = 0; c < N; c++)
		{
			switch (in[c])
			{
			case 'R':
				board1[r][c] = 0;
				board2[r][c] = 0;
				break;
			case 'G':
				board1[r][c] = 1;
				board2[r][c] = 0;
				break;
			case 'B':
				board1[r][c] = 2;
				board2[r][c] = 1;
				break;
			}
		}
	}
}

void bfs1(int r, int c)
{
	int currR, currC, nextR, nextC, val;
	queue<pair<int, int> > Q;
	visit1[r][c] = true;
	Q.push({ r,c });
	val = board1[r][c];

	while (!Q.empty())
	{
		currR = Q.front().first;
		currC = Q.front().second;
		Q.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit1[nextR][nextC] || board1[nextR][nextC] != val)
				continue;
			visit1[nextR][nextC] = true;
			Q.push({ nextR,nextC });
		}
	}
	answer1++;
}

void bfs2(int r, int c)
{
	int currR, currC, nextR, nextC, val;
	queue<pair<int, int> > Q;
	visit2[r][c] = true;
	Q.push({ r,c });
	val = board2[r][c];

	while (!Q.empty())
	{
		currR = Q.front().first;
		currC = Q.front().second;
		Q.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit2[nextR][nextC] || board2[nextR][nextC] != val)
				continue;
			visit2[nextR][nextC] = true;
			Q.push({ nextR,nextC });
		}
	}
	answer2++;
}

void solve()
{
	for(int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			if (!visit1[r][c])
				bfs1(r, c);
			if (!visit2[r][c])
				bfs2(r, c);
		}
}

void output()
{
	printf("%d %d\n", answer1, answer2);
}