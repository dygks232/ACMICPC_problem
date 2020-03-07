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

bool isClear(int time);
bool isImpossibleMove(int r, int c, vector<vector<int> >& mazeCopy);
void dfs(int time, int row, int col, bool& ans);
vector<vector<int> > wallDown(vector<vector<int> >& maze);
int countWall(int time);

#define BLANK 0
#define WALL 1
#define LEN 8

bool answer;
int currRow, currCol, currTime;
int dirR[9] = { 0,-1,-1,-1,0,1,1,1,0 };
int dirC[9] = { 0,-1,0,1,1,1,0,-1,-1 };

vector<vector<int> > maze[9];
vector<int> wallNum;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

int countWall(int time)
{
	int ret = 0;
	for (int i = 0; i < LEN; i++)
		for (int j = 0; j < LEN; j++)
			if (maze[time][i][j] == WALL)
				ret++;
	return ret;
}

vector<vector<int> > wallDown(vector<vector<int> >& maze)
{
	vector<vector<int> > ret = maze;
	for (int i = LEN - 2; i >= 0; i--)
		for (int j = 0; j < LEN; j++)
			ret[i + 1][j] = ret[i][j];
	return ret;
}

void dfs(int time, int row, int col, bool& ans)
{
	int nextRow, nextCol;
	bool copyFlag = false;
	vector<vector<int> > movedMaze;
	if (isClear(time) || ans || time == 8)
	{
		ans = true;
		return;
	}

	for (int dir = 0; dir < 9; dir++)
	{
		if (ans)
			break;
		nextRow = row + dirR[dir];
		nextCol = col + dirC[dir];
		if (isImpossibleMove(nextRow, nextCol, maze[time]))
			continue;

		dfs(time + 1, nextRow, nextCol, ans);
	}
}

bool isImpossibleMove(int r, int c, vector<vector<int> >& mazeCopy)
{
	return r < 0 || c < 0 || r >= LEN || c >= LEN || mazeCopy[r][c] == WALL || (r > 0 && mazeCopy[r - 1][c] == WALL);
}

bool isClear(int time)
{
	return !wallNum[time];
}

void inputAndInit()
{
	char c;
	answer = false;
	currRow = LEN - 1;
	currCol = 0;
	currTime = 0;
	wallNum.assign(9, 0);
	for (int i = 0; i < 9; i++)
		maze[i].assign(LEN, vector<int>(LEN, 0));
	for (int i = 0; i < LEN; i++)
		for (int j = 0; j < LEN; j++)
		{
			cin >> c;
			if (c == '.')
				maze[0][i][j] = BLANK;
			else if (c == '#')
			{
				maze[0][i][j] = WALL;
				wallNum[0]++;
			}
		}
	for (int i = 1; i < 9; i++)
	{
		maze[i] = wallDown(maze[i - 1]);
		wallNum[i] = countWall(i);
	}
}

void solve()
{
	if (!isClear(currTime))
	{
		dfs(currTime, currRow, currCol, answer);
	}
	else
		answer = true;
}

void output()
{
	if (answer)
		cout << "1\n";
	else
		cout << "0\n";
}