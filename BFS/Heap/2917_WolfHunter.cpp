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
void bfs();
void makeDistMap();

struct pos {
	int row;
	int col;
	pos() { row = col = 0; }
	pos(int r, int c) { row = r; col = c; }
};

int answer, R, C;

pos start, dest;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<vector<bool> > visit;
int distTree[500][500];
queue<pos> tree;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void makeDistMap()
{
	int currR, currC, nextR, nextC, currDist;
	while (!tree.empty())
	{
		currR = tree.front().row;
		currC = tree.front().col;
		tree.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || distTree[nextR][nextC] != -1)
				continue;
			distTree[nextR][nextC] = distTree[currR][currC] + 1;
			tree.push(pos(nextR, nextC));
		}
	}
}

void bfs()
{
	priority_queue<pair<int, pair<int, pair<int, int> > >, vector<pair<int, pair<int, pair<int, int> > > >, less<pair<int, pair<int, pair<int, int> > > > > PQ;
	int currR, currC, nextR, nextC, currDist, currMinDist;
	PQ.push(make_pair(distTree[start.row][start.col], make_pair(distTree[start.row][start.col], make_pair(start.row, start.col))));
	visit[start.row][start.col] = true;

	while (!PQ.empty())
	{
		currR = PQ.top().second.second.first;
		currC = PQ.top().second.second.second;
		currDist = PQ.top().first;
		currMinDist = PQ.top().second.first;
		PQ.pop();
		visit[currR][currC] = true;
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC))
				continue;
			if (visit[nextR][nextC])
				continue;
			if (nextR == dest.row && nextC == dest.col)
			{
				answer = min(currMinDist, distTree[nextR][nextC]);
				return;
			}
			visit[nextR][nextC] = true;
			PQ.push(make_pair(distTree[nextR][nextC], make_pair(min(currMinDist, distTree[nextR][nextC]), make_pair(nextR, nextC))));
		}
	}
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

void inputAndInit()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	string str;
	cin >> R >> C;
	answer = INT_MIN;
	visit.assign(R, vector<bool>(C, false));
	memset(distTree, -1, 250000*sizeof(int));
	for (int i = 0; i < R; i++)
	{
		cin >> str;
		for (int j = 0; j < C; j++)
		{
			switch (str[j])
			{
			case '.': 
				break;
			case 'V': 
				start.row = i; start.col = j;
				break;
			case 'J': 
				dest.row = i; dest.col = j;
				break;
			case '+': 
				distTree[i][j] = 0;
				tree.push(pos(i, j));
				break;
			}
		}
	}
	makeDistMap();
}

void solve()
{
	bfs();
}

void output()
{
	cout << answer << "\n";
}
