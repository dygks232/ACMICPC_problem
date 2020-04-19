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

bool isOutOfBoundary(int r, int c);
bool white(int pIdx, int nextR, int nextC);
bool red(int pIdx, int nextR, int nextC);
bool blue(int pIdx);

int N, K, answer;

int board[12][12][5];
int piece[12][3];

int dirR[4] = { 0,0,-1,1 };
int dirC[4] = { 1,-1,0,0 };

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r >= N || c >= N;
}

void inputAndInit()
{
	int ir, ic, id;
	scanf("%d %d", &N, &K);
	answer = 0;
	memset(board, -1, sizeof(board));
	for(int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &board[r][c][0]);
		}
	for (int i = 0; i < K; i++)
	{
		scanf("%d %d %d", &ir, &ic, &id);
		piece[i][0] = ir - 1;
		piece[i][1] = ic - 1;
		piece[i][2] = id - 1;
		board[piece[i][0]][piece[i][1]][1] = i;
	}
}

bool blue(int pIdx)
{
	int nextR, nextC;
	if (piece[pIdx][2] & 1)
		piece[pIdx][2]--;
	else
		piece[pIdx][2]++;
	nextR = piece[pIdx][0] + dirR[piece[pIdx][2]];
	nextC = piece[pIdx][1] + dirC[piece[pIdx][2]];
	if (isOutOfBoundary(nextR, nextC) || board[nextR][nextC][0] == 2)
		;
	else if (!board[nextR][nextC][0])
	{
		if (white(pIdx, nextR, nextC))
			return true;
	}
	else
	{
		if (red(pIdx, nextR, nextC))
			return true;
	}
	return false;
}

bool red(int pIdx, int nextR, int nextC)
{
	int orgCnt = 0, newCnt = 0, i, pos, currR, currC;
	for (i = 1; i < 5; i++)
		if (board[piece[pIdx][0]][piece[pIdx][1]][i] == pIdx)
		{
			pos = i;
			break;
		}
	for (; i < 5; i++)
	{
		if (board[piece[pIdx][0]][piece[pIdx][1]][i] == -1)
			break;
		newCnt++;
	}
	for (i = 1; i < 5; i++)
	{
		if (board[nextR][nextC][i] == -1)
			break;
		orgCnt++;
	}
	if (orgCnt + newCnt >= 4)
		return true;

	currR = piece[pIdx][0];
	currC = piece[pIdx][1];
	for (int k = pos + newCnt - 1; k >= pos; k--)
	{
		board[nextR][nextC][i] = board[currR][currC][k];
		board[currR][currC][k] = -1;
		piece[board[nextR][nextC][i]][0] = nextR;
		piece[board[nextR][nextC][i]][1] = nextC;
		i++;
	}

	return false;
}

bool white(int pIdx, int nextR, int nextC)
{
	int orgCnt = 0, newCnt = 0, i, pos, currR, currC;
	for (i = 1; i < 5; i++)
		if (board[piece[pIdx][0]][piece[pIdx][1]][i] == pIdx)
		{
			pos = i;
			break;
		}
	for (; i < 5; i++)
	{
		if (board[piece[pIdx][0]][piece[pIdx][1]][i] == -1)
			break;
		newCnt++;
	}
	for (i = 1; i < 5; i++)
	{
		if (board[nextR][nextC][i] == -1)
			break;
		orgCnt++;
	}
	if (orgCnt + newCnt >= 4)
		return true;

	currR = piece[pIdx][0];
	currC = piece[pIdx][1];
	for (int k = pos; k <= pos + newCnt - 1; k++)
	{
		board[nextR][nextC][i] = board[currR][currC][k];
		board[currR][currC][k] = -1;
		piece[board[nextR][nextC][i]][0] = nextR;
		piece[board[nextR][nextC][i]][1] = nextC;
		i++;
	}

	return false;
}

void solve()
{
	int i, nextR, nextC;
	while (1)
	{
		answer++;

		for (i = 0; i < K; i++)
		{
			nextR = piece[i][0] + dirR[piece[i][2]];
			nextC = piece[i][1] + dirC[piece[i][2]];
			if (isOutOfBoundary(nextR, nextC) || board[nextR][nextC][0] == 2)
			{
				if (blue(i))
					return;
			}
			else if (!board[nextR][nextC][0])
			{
				if (white(i, nextR, nextC))
					return;
			}
			else
			{
				if (red(i, nextR, nextC))
					return;
			}
		}

		if (answer >= 1000)
		{
			answer = -1;
			break;
		}
	}
}

void output()
{
	printf("%d\n", answer);
}