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

#define BLANK 0
#define WALL 1
#define VIRUS 2

#define NEW_WALL 3
#define MAXLEN 8
#define MAXVIRUS 10

void inputAndInit();
void solve();
void output();

bool isOutOfBoundary(int r, int c);
void bfs(int r, int c);

int R, C, answer, virusNum, blankNum, tempAns;

int board[MAXLEN][MAXLEN];
int boardClone[MAXLEN][MAXLEN];
bool visit[MAXLEN][MAXLEN];
pair<int, int> virusPos[MAXVIRUS];
pair<int, int> blankPos[MAXLEN * MAXLEN];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d %d", &R, &C);
	blankNum = virusNum = answer = 0;
	memset(virusPos, -1, sizeof(virusPos));
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			scanf("%d", &board[r][c]);
			if (board[r][c] == BLANK)
				blankPos[blankNum++] = { r,c };
			else if (board[r][c] == VIRUS)
				virusPos[virusNum++] = { r,c };
		}
	}
}

void solve()
{
	vector<int> permu;
	permu.assign(blankNum, 1);
	for (int i = 0; i < NEW_WALL; i++)
		permu[i] = 0;
	do
	{
		memcpy(boardClone, board, sizeof(board));
		for (int i = 0; i < blankNum; i++)
		{
			if (!permu[i])
				boardClone[blankPos[i].first][blankPos[i].second] = WALL;
		}
		memset(visit, false, sizeof(visit));
		tempAns = blankNum - NEW_WALL;
		for (int i = 0; i < virusNum; i++)
		{
			bfs(virusPos[i].first, virusPos[i].second);
		}
		answer = max(answer, tempAns);
	} while (next_permutation(permu.begin(), permu.end()));
}

void output()
{
	printf("%d\n", answer);
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C || boardClone[r][c] == WALL;
}

void bfs(int r, int c)
{
	queue<pair<int, int> > Q;
	int currRow, currCol, nextRow, nextCol;
	Q.push({ r,c });
	visit[r][c] = true;

	while (!Q.empty())
	{
		currRow = Q.front().first;
		currCol = Q.front().second;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextRow = currRow + dirR[dir];
			nextCol = currCol + dirC[dir];
			if (isOutOfBoundary(nextRow, nextCol) || visit[nextRow][nextCol])
				continue;
			visit[nextRow][nextCol] = true;
			Q.push({ nextRow,nextCol });
			if (boardClone[nextRow][nextCol] == BLANK)
				tempAns--;
		}
	}
}