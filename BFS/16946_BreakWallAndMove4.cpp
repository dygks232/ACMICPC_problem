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
void bfs(int r, int c);
int calcAns(int r, int c);

int R, C, clusterIdx;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<vector<bool> > board;
vector<vector<bool> > visit;
vector<vector<int> > answer;
vector<pair<int, int> > blank;
vector<vector<int> > cluster;
vector<vector<int> > linkNum;

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

void bfs(int r, int c)
{
	if (visit[r][c])
		return;

	queue<pair<int, int> > Q;
	vector<pair<int, int> > vec;
	int currR, currC, nextR, nextC, num = 1, size;
	visit[r][c] = true;
	Q.push({ r,c });
	vec.push_back({ r,c });

	while (!Q.empty())
	{
		currR = Q.front().first;
		currC = Q.front().second;
		Q.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC] || board[nextR][nextC])
				continue;
			visit[nextR][nextC] = true;
			Q.push({ nextR,nextC });
			vec.push_back({ nextR,nextC });
			num++;
		}
	}

	size = vec.size();
	for (int i = 0; i < size; i++)
	{
		linkNum[vec[i].first][vec[i].second] = num;
		cluster[vec[i].first][vec[i].second] = clusterIdx;
	}
	clusterIdx++;
}

void inputAndInit()
{
	int in;
	scanf("%d %d", &R, &C);
	board.assign(R, vector<bool>(C, false));
	visit.assign(R, vector<bool>(C, false));
	answer.assign(R, vector<int>(C, 0));
	cluster.assign(R, vector<int>(C, 0));
	linkNum.assign(R, vector<int>(C, 0));
	clusterIdx = 1;
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			scanf("%1d", &in);
			board[r][c] = in;
			if (!in)
				blank.push_back({ r,c });
		}
	}
}

void solve()
{
	int size = blank.size();
	for (int i = 0; i < size; i++)
		bfs(blank[i].first, blank[i].second);
}

int calcAns(int r, int c)
{
	if (!board[r][c])
		return 0;

	int ret = 1, nextR, nextC;
	bool flag;
	pair<int, int> currLink[4] = { {-1,0},{-1,0},{-1,0},{-1,0} };
	for (int dir = 0; dir < 4; dir++)
	{
		nextR = r + dirR[dir];
		nextC = c + dirC[dir];
		if (isOutOfRange(nextR, nextC) || board[nextR][nextC])
			continue;

		flag = false;
		currLink[dir] = { cluster[nextR][nextC],linkNum[nextR][nextC] };
		for (int dir2 = 0; dir2 < dir; dir2++)
		{
			if (currLink[dir2].first == -1)
				continue;
			if (currLink[dir2].first == currLink[dir].first)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			ret += currLink[dir].second;
		}
	}
	return ret % 10;
}

void output()
{
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			printf("%d", calcAns(r, c));
		}
		printf("\n");
	}
}