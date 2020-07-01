#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<cmath>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<deque>
#include<functional>
#include<cstring>
#include<string>
using namespace std;

#define WALL -2
#define BLANK -1
#define START 0
#define END 6

void inputAndInit();
void solve();
void output();

bool isOutOfBoundary(int r, int c);
void bfs(int startIdx, int num);

int R, C, answer, targetNum, sR, sC, eR, eC;

int board[50][50];
bool visit[50][50];
int dist[7][7];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<pair<int, int> > targetPos;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	char in;
	scanf("%d %d", &C, &R);
	targetNum = 0;
	answer = INT_MAX;
	targetPos.assign(7, { -1,-1 });
	memset(dist, 0, sizeof(dist));
	for (int r = 0; r < R; r++)
	{
		scanf("%c", &in);
		for (int c = 0; c < C; c++)
		{
			scanf("%c", &in);
			switch (in)
			{
			case '#':
				board[r][c] = WALL;
				break;
			case '.':
				board[r][c] = BLANK;
				break;
			case 'S':
				board[r][c] = START;
				targetPos[START] = { r,c };
				break;
			case 'E':
				board[r][c] = END;
				targetPos[END] = { r,c };
				break;
			case 'X': 
				board[r][c] = ++targetNum;
				targetPos[targetNum] = { r,c };
				break;
			}
		}
	}
}

void solve()
{
	for (int i = START; i <= targetNum; i++)
		bfs(i, targetNum + 1 - i);

	if (targetNum)
	{
		vector<int> permu(targetNum);
		int tempAns;
		for (int i = 0; i < targetNum; i++)
			permu[i] = i + 1;
		do
		{
			tempAns = dist[START][permu[0]];
			tempAns += dist[permu[targetNum - 1]][END];
			for (int i = 0; i < targetNum - 1; i++)
				tempAns += dist[permu[i]][permu[i + 1]];
			answer = min(answer, tempAns);
		} while (next_permutation(permu.begin(), permu.end()));
	}
	else
		answer = dist[START][END];
}

void output()
{
	printf("%d\n", answer);
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C || board[r][c] == WALL;
}

void bfs(int startIdx, int num)
{
	queue<pair<pair<int, int>, int> > Q;
	int currR, currC, nextR, nextC, currDist, currNum = 0;
	memset(visit, false, sizeof(visit));
	Q.push({ {targetPos[startIdx].first, targetPos[startIdx].second},0 });
	visit[targetPos[startIdx].first][targetPos[startIdx].second] = true;

	while (!Q.empty())
	{
		currR = Q.front().first.first;
		currC = Q.front().first.second;
		currDist = Q.front().second;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfBoundary(nextR, nextC) || visit[nextR][nextC])
				continue;
			if (board[nextR][nextC] > startIdx)
			{
				dist[startIdx][board[nextR][nextC]] = currDist + 1;
				dist[board[nextR][nextC]][startIdx] = currDist + 1;
				if (++currNum == num)
					return;
			}
			visit[nextR][nextC] = true;
			Q.push({ {nextR,nextC},currDist + 1 });
		}
	}
}