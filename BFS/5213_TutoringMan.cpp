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
void init();
void solve();
void output();
void solveAndOutput();

int getTile(int r, int c);
void bfs();
bool isSameTile(int r1, int c1, int r2, int c2);
bool isOutOfBoundary(int r, int c);
void printAnswer(int idx);
int calcAnswer(int idx);

#define BLANK -1

int R, C, answer, N, tileNum;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<vector<int> > board;
vector<bool> visit;
vector<int> preNode;
vector<vector<int> > tile;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C || board[r][c] == BLANK;
}

bool isSameTile(int r1, int c1, int r2, int c2)
{
	return tile[r1][c1] == tile[r2][c2];
}

int getTile(int r, int c)
{
	int ret = 0;
	for (int i = 0; i < r; i++)
		ret += R - i % 2;
	if (r % 2)
	{
		if (c == 0 || c == C - 1)
			return BLANK;
		ret += c / 2 + c % 2 - 1;
	}
	else
		ret += c / 2;
	return ret;
}

void bfs()
{
	queue<pair<int, pair<int, int> > > Q;
	int currR, currC, nextR, nextC, currDist;
	Q.push(make_pair(1, make_pair(0, 0)));
	visit[0] = true;

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
			if (isOutOfBoundary(nextR, nextC) || isSameTile(currR, currC, nextR, nextC) || visit[tile[nextR][nextC]])
				continue;
			if (board[currR][currC] != board[nextR][nextC])
				continue;

			visit[tile[nextR][nextC]] = true;
			Q.push(make_pair(currDist + 1, make_pair(nextR, nextC)));
			preNode[tile[nextR][nextC]] = tile[currR][currC];
		}

		if ((!(currR % 2) && !(currC % 2)) || ((currR % 2) && (currC % 2)))
			currC++;
		else
			currC--;
		
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfBoundary(nextR, nextC) || isSameTile(currR, currC, nextR, nextC) || visit[tile[nextR][nextC]])
				continue;
			if (board[currR][currC] != board[nextR][nextC])
				continue;

			visit[tile[nextR][nextC]] = true;
			Q.push(make_pair(currDist + 1, make_pair(nextR, nextC)));
			preNode[tile[nextR][nextC]] = tile[currR][currC];
		}
	}
}

void inputAndInit()
{
	//cin >> N;
	scanf("%d", &N);
	C = N * 2;
	R = N;
	tileNum = N * N - N / 2;
	board.assign(R, vector<int>(C, 0));
	tile.assign(R, vector<int>(C, 0));
	visit.assign(tileNum, false);
	preNode.assign(tileNum, BLANK);
	for (int r = 0; r < R; r++)
	{
		if (r % 2)
		{
			board[r][0] = board[r][C - 1] = BLANK;
			tile[r][0] = tile[r][C - 1] = BLANK;
		}
		for (int c = r % 2; c < C - r % 2; c++)
		{
			//cin >> board[r][c];
			scanf("%d", &board[r][c]);
			tile[r][c] = getTile(r, c);
		}
	}
}

void solve()
{
	bfs();
}

int calcAnswer(int idx)
{
	if (!idx)
		return 1;
	return calcAnswer(preNode[idx]) + 1;
}

void printAnswer(int idx)
{
	if (!idx)
	{
		printf("1 ");
		return;
	}
	printAnswer(preNode[idx]);
	printf("%d ", idx + 1);
}

void output()
{
	int dest = BLANK;
	for(int i = tileNum-1; i >= 0; i--)
		if (preNode[i] != BLANK)
		{
			dest = i;
			break;
		}

	if (dest == BLANK)
		printf("1\n1\n");
	else
	{
		printf("%d\n", calcAnswer(dest));
		printAnswer(dest);
		printf("\n");
	}
}
