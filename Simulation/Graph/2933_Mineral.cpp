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

bool destroy(int time);
void calcLink();
bool isOutOfRange(int r, int c);
bool makeCluster();
void downCluster();
void linking(int row, int col);

#define BLANK 0
#define MINERAL 1

int R, C, N;

int dirR[4] = { 0,0,-1,1 };
int dirC[4] = { -1,1,0,0 };

vector<vector<int> > mineral;
vector<vector<bool> > link;
vector<vector<bool> > visit;
vector<vector<int> > cluster;
vector<int> throwHeight;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void downCluster()
{
	int left = INT_MAX, right = INT_MIN, downHeight = INT_MAX, mineralH;
	vector<int> clusterH, clusterH2;
	clusterH.assign(C, 0);
	clusterH2.assign(C, 0);
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
			if (cluster[i][j])
			{
				left = min(left, j);
				right = max(right, j);
			}

	for (int c = left; c <= right; c++)
	{
		mineralH = R;
		for (int r = R - 1; r >= 0; r--)
			if (cluster[r][c])
			{
				clusterH[c] = r;
				break;
			}
		for (int r = 0; r < R; r++)
			if (cluster[r][c])
			{
				clusterH2[c] = r;
				break;
			}
		for (int r = clusterH[c] + 1; r < R; r++)
			if (mineral[r][c])
			{
				mineralH = r;
				break;
			}
		downHeight = min(downHeight, mineralH - clusterH[c] - 1);
	}

	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			if (mineral[i][j] && cluster[i][j])
				mineral[i][j] = BLANK;
		}

	for (int c = left; c <= right; c++)
	{
		for (int t = 0; t < downHeight; t++)
		{
			for (int r = clusterH[c] + t; r >= clusterH2[c] + t; r--)
				cluster[r + 1][c] = cluster[r][c];

			cluster[clusterH2[c] + t][c] = BLANK;
		}
	}

	for (int c = left; c <= right; c++)
	{
		for (int r = 0; r < R; r++)
			if (cluster[r][c])
				mineral[r][c] = cluster[r][c];
	}

}

bool makeCluster()
{
	bool ret = false;
	cluster.assign(R, vector<int>(C, BLANK));

	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
			if (!link[i][j] && mineral[i][j])
			{
				cluster[i][j] = MINERAL;
				ret = true;
			}
	}
	return ret;
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

void linking(int row, int col)
{
	int nextRow, nextCol;
	visit[row][col] = true;
	link[row][col] = true;

	for (int dir = 0; dir < 4; dir++)
	{
		nextRow = row + dirR[dir];
		nextCol = col + dirC[dir];

		if (isOutOfRange(nextRow, nextCol))
			continue;

		if (mineral[nextRow][nextCol] && !visit[nextRow][nextCol] && !link[nextRow][nextCol])
			linking(nextRow, nextCol);
	}
}

void calcLink()
{
	int r, c;
	link.assign(R, vector<bool>(C, false));
	visit.assign(R, vector<bool>(C, false));

	for (int c = 0; c < C; c++)
	{
		if (mineral[R - 1][c] && !link[R - 1][c])
			linking(R - 1, c);
	}
}

bool destroy(int time)
{
	if (time % 2)
	{
		for (int c = C - 1; c >= 0; c--)
		{
			if (mineral[R - throwHeight[time]][c])
			{
				mineral[R - throwHeight[time]][c] = BLANK;
				return true;
			}
		}
	}
	else
	{
		for (int c = 0; c < C; c++)
		{
			if (mineral[R - throwHeight[time]][c])
			{
				mineral[R - throwHeight[time]][c] = BLANK;
				return true;
			}
		}
	}
	return false;
}

void inputAndInit()
{
	char c;
	cin >> R >> C;
	mineral.assign(R, vector<int>(C, 0));
	link.assign(R, vector<bool>(C, false));
	cluster.assign(R, vector<int>(C, 0));
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> c;
			if (c == '.')
				mineral[i][j] = BLANK;
			else
			{
				mineral[i][j] = MINERAL;
				link[i][j] = true;
			}
		}
	}
	cin >> N;
	throwHeight.assign(N, 0);
	for (int i = 0; i < N; i++)
		cin >> throwHeight[i];
}

void solve()
{
	for (int t = 0; t < N; t++)
	{
		if (destroy(t))
		{
			calcLink();
			if (makeCluster())
			{
				downCluster();
			}
		}
	}
}

void output()
{
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (mineral[i][j])
				cout << "x";
			else
				cout << ".";
		}
		cout << "\n";
	}
}
