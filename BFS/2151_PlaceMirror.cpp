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

#define WALL -1
#define BLANK 0
#define MIR_POS 1
#define DOOR 2

void inputAndInit();
void init();
void solve();
void output();
void solveAndOutput();

struct pos {
	int row;
	int col;
	pos() {
		row = col = 0;
	}
	pos(int r, int c) {
		row = r; col = c;
	}
};

void bfs(pos curr, int cnt, int dir);
bool isOutOfRange(pos curr);

int dirR[4] = { -1,1,0,0 };
int dirC[4] = { 0,0,-1,1 };

int N, answer;
pos door1, door2;
vector<vector<int> > house;
vector<vector<bool> > visit[2];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfRange(pos curr)
{
	if (curr.row < 0 || curr.col < 0 || curr.row >= N || curr.col >= N)
		return true;
	if (house[curr.row][curr.col] == DOOR)
		return false;
	if (house[curr.row][curr.col] == WALL)
		return true;
	else
		return false;
}

void bfs(pos curr, int cnt, int dir)
{
	queue<pair<pos, pair<int, int> > > q;
	pos currPos, nextPos;
	int currCnt, currDir, nextDir;

	q.push(make_pair(curr, make_pair(cnt, dir)));

	while (!q.empty())
	{
		currPos.row = q.front().first.row;
		currPos.col = q.front().first.col;
		currCnt = q.front().second.first;
		currDir = q.front().second.second;

		for (nextDir = 2 * currDir; nextDir <= 2 * currDir + 1; nextDir++)
		{
			nextPos.row = currPos.row + dirR[nextDir];
			nextPos.col = currPos.col + dirC[nextDir];

			while (!isOutOfRange(nextPos))
			{
				if (nextPos.row == door2.row && nextPos.col == door2.col)
				{
					answer = min(answer, currCnt);
					return;
				}
				if (house[nextPos.row][nextPos.col] == MIR_POS && !visit[currDir][nextPos.row][nextPos.col])
				{
					visit[currDir][nextPos.row][nextPos.col] = true;
					q.push(make_pair(nextPos, make_pair(currCnt + 1, (currDir + 1) % 2)));
				}

				nextPos.row += dirR[nextDir];
				nextPos.col += dirC[nextDir];
			}

		}
		q.pop();
	}
}

void inputAndInit()
{
	char c;
	bool find = false;
	cin >> N;
	answer = INT_MAX;
	house.assign(N, vector<int>(N, 0));
	visit[0].assign(N, vector<bool>(N, false));
	visit[1].assign(N, vector<bool>(N, false));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> c;
			switch (c)
			{
			case '*': house[i][j] = WALL;
				break;
			case '.': house[i][j] = BLANK;
				break;
			case '!': house[i][j] = MIR_POS;
				break;
			case '#': house[i][j] = DOOR;
				if (!find) {
					door1 = pos(i, j);
					find = true;
				}
				else
					door2 = pos(i, j);
				break;
			}
		}
	}
}

void solve()
{
	bfs(door1, 0, 0);
	bfs(door1, 0, 1);
}

void output()
{
	cout << answer << "\n";
}