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

bool isOutOfBoundary(int r, int c);
void removeSmell();
void sharkMove();

int N, M, K, answer, sharkNum, time;

struct _region {
public:
	int idx;
	int smell;
	_region() {
		idx = smell = 0;
	}
	_region(bool u, int i, int s) {
		idx = i; smell = s;
	}
};

struct _shark {
	bool die;
	int row;
	int col;
	int dir;
	int prior[5][4];
	_shark() {
		die = false;
		row = col = dir = 0;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 4; j++)
				prior[i][j] = 0;
	}
};

_region board[20][20];
_region boardClone[20][20];
_shark shark[401];

int dirR[5] = { 0,-1,1,0,0 };
int dirC[5] = { 0,0,0,-1,1 };

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int in;
	scanf("%d %d %d", &N, &M, &K);
	sharkNum = M;
	time = 0;
	answer = -1;
	memset(board, 0, sizeof(board));
	memset(shark, 0, sizeof(shark));
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &in);
			if (in)
			{
				shark[in].row = r;
				shark[in].col = c;
				board[r][c].idx = in;
				board[r][c].smell = K;
			}
		}
	}
	for (int i = 1; i <= M; i++)
		scanf("%d", &(shark[i].dir));
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				scanf("%d", &(shark[i].prior[j][k]));
			}
		}
	}
}

void solve()
{
	for (time = 1; time <= 1000; time++)
	{
		memcpy(boardClone, board, sizeof(board));
		sharkMove();
		memcpy(board, boardClone, sizeof(board));
		removeSmell();
		
		if (sharkNum == 1)
		{
			answer = time;
			break;
		}
	}
}

void output()
{
	printf("%d\n", answer);
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r >= N || c >= N;
}

void removeSmell()
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (board[r][c].smell)
				board[r][c].smell -= 1;
			if (!board[r][c].smell)
				board[r][c].idx = 0;
		}
	}
}

void sharkMove()
{
	bool bNoSmell;
	bool noSmell[5], mySmell[5];
	int noIdx, myIdx, nextRow, nextCol;
	for (int i = 1; i <= M; i++)
	{
		if (shark[i].die)
			continue;
		bNoSmell = false;
		noIdx = myIdx = 0;
		memset(noSmell, false, sizeof(noSmell));
		memset(mySmell, false, sizeof(mySmell));
		for (int dir = 1; dir <= 4; dir++)
		{
			nextRow = shark[i].row + dirR[dir];
			nextCol = shark[i].col + dirC[dir];
			if (isOutOfBoundary(nextRow, nextCol))
				continue;
			if (board[nextRow][nextCol].idx == 0)
			{
				bNoSmell = true;
				noSmell[dir] = true;
				noIdx++;
			}
			else if (board[nextRow][nextCol].idx == i)
			{
				mySmell[dir] = true;
				myIdx++;
			}
		}
		if (bNoSmell)
		{
			for (int iter = 0; iter < 4; iter++)
			{
				if (noSmell[shark[i].prior[shark[i].dir][iter]])
				{
					shark[i].row += dirR[shark[i].prior[shark[i].dir][iter]];
					shark[i].col += dirC[shark[i].prior[shark[i].dir][iter]];
					if (boardClone[shark[i].row][shark[i].col].idx) // 우선순위에 따라 이동했는데, 나보다 강한 상어를 만날 때
					{
						shark[i].die = true;
						sharkNum--;
						break;
					}
					shark[i].dir = shark[i].prior[shark[i].dir][iter];
					boardClone[shark[i].row][shark[i].col].idx = i;
					boardClone[shark[i].row][shark[i].col].smell = K + 1;
					break;
				}
			}
		}
		else
		{
			for (int iter = 0; iter < 4; iter++)
			{
				if (mySmell[shark[i].prior[shark[i].dir][iter]])
				{
					shark[i].row += dirR[shark[i].prior[shark[i].dir][iter]];
					shark[i].col += dirC[shark[i].prior[shark[i].dir][iter]];
					shark[i].dir = shark[i].prior[shark[i].dir][iter];
					boardClone[shark[i].row][shark[i].col].idx = i;
					boardClone[shark[i].row][shark[i].col].smell = K + 1;
					break;
				}
			}
		}
	}
}