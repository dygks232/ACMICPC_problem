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

#define MAXN 1000000

void inputAndInit();
void solve();
void output();

void bfs();
bool isOutOfRange(vector<int>& idx);

int boardSize, zeroCnt, answer;

int boardLen[11];
int dir[11][22] = {
	{ -1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,-1,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,-1,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,-1,1,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,1 }
};
int board[MAXN];
int boardDim[11];

queue<pair<int, int> > startIdx;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	boardSize = 1;
	zeroCnt = 0;
	answer = 0;
	boardDim[0] = 1;
	for (int i = 0; i < 11; i++)
	{
		scanf("%d", &boardLen[i]);
		boardSize *= boardLen[i];
	}
	for (int i = 1; i < 11; i++)
		boardDim[i] = boardDim[i - 1] * boardLen[i - 1];
	for (int i = 0; i < boardSize; i++)
	{
		scanf("%d", &board[i]);
		if (!board[i])
			zeroCnt++;
		else if (board[i] == 1)
			startIdx.push({ i,0 });
	}
}

bool isOutOfRange(vector<int>& idx)
{
	for (int i = 0; i < 11; i++)
	{
		if (idx[i] < 0 || idx[i] >= boardLen[i])
			return true;
	}
	return false;
}

void bfs()
{
	vector<int> currIdx(11), nextIdx(11);
	int currDist, next;

	while (!startIdx.empty())
	{
		for (int i = 0; i < 10; i++)
			currIdx[i] = (startIdx.front().first % boardDim[i + 1]) / boardDim[i];
		currIdx[10] = startIdx.front().first / boardDim[10];
		currDist = startIdx.front().second;
		startIdx.pop();

		for (int d = 0; d < 22; d++)
		{
			next = 0;
			for (int dim = 0; dim < 11; dim++)
			{
				nextIdx[dim] = currIdx[dim] + dir[dim][d];
				next += nextIdx[dim] * boardDim[dim];
			}
			if (isOutOfRange(nextIdx) || board[next])
				continue;
			board[next] = currDist + 1;
			answer = max(answer, currDist + 1);
			zeroCnt--;
			startIdx.push({ next, currDist + 1 });
		}
	}
}

void solve()
{
	if (zeroCnt)
	{
		bfs();
		if (zeroCnt)
			answer = -1;
	}
}

void output()
{
	printf("%d\n", answer);
}
