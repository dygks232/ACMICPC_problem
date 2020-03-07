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

void rotate(int rot);
bool permu(int curr);
bool permu2(int curr);
void makeCube(const vector<int>& permu, const vector<int>& rot);
bool bfs(int startR, int startC, int startH);
bool isOutOfBoundary(int r, int c, int h);

#define LEN 5
#define ROT 4

struct pos {
	int row; int col; int hei;
	pos() { row = col = hei = 0; }
	pos(int r, int c, int h) { row = r; col = c; hei = h; }
};

int answer;
bool cube[LEN][LEN][LEN];
bool visit[LEN][LEN][LEN];
bool plate[LEN][ROT][LEN][LEN]; // plate[idx][rot][row][col]

int dirR[6] = { -1,0,0,1,0,0 };
int dirC[6] = { 0,-1,0,0,1,0 };
int dirH[6] = { 0,0,-1,0,0,1 };

vector<int> permutation;
vector<int> rotation;
vector<bool> use;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

bool isOutOfBoundary(int r, int c, int h)
{
	return r < 0 || c < 0 || h < 0 || r >= LEN || c >= LEN || h >= LEN || !cube[r][c][h];
}

bool bfs(int startR, int startC, int startH)
{
	queue<pair<int, pos> > Q;
	int currR, currC, currH, nextR, nextC, nextH, currDist;
	int endR = 4 - startR, endC = 4 - startC, endH = 4 - startH;
	if (!cube[startR][startC][startH] || !cube[endR][endC][endH])
		return false;
	memset(visit, 0, sizeof(visit));
	Q.push(make_pair(0, pos(startR, startC, startH)));
	visit[startR][startC][startH] = true;

	while (!Q.empty())
	{
		currR = Q.front().second.row;
		currC = Q.front().second.col;
		currH = Q.front().second.hei;
		currDist = Q.front().first;
		Q.pop();

		for (int dir = 0; dir < 6; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			nextH = currH + dirH[dir];
			if (isOutOfBoundary(nextR, nextC, nextH) || visit[nextR][nextC][nextH])
				continue;
			if (nextR == endR && nextC == endC && nextH == endH)
			{
				answer = min(answer, currDist + 1);
				if (answer == 12)
					return true;
				return false;
			}
			visit[nextR][nextC][nextH] = true;
			Q.push(make_pair(currDist + 1, pos(nextR, nextC, nextH)));
		}
	}
	return false;
}

void makeCube(const vector<int>& permu, const vector<int>& rot)
{
	for (int i = 0; i < LEN; i++)
		memcpy(cube[i], plate[permu[i]][rot[i]], sizeof(bool) * 25);
}

bool permu2(int curr)
{
	if (curr == LEN)
	{
		makeCube(permutation, rotation);
		// 시작점 4군데에서의 각각 BFS 추가
		if (bfs(0, 0, 0))
			return true;
		if (bfs(4, 0, 0))
			return true;
		if (bfs(0, 4, 0))
			return true;
		if (bfs(0, 0, 4))
			return true;
		return false;
	}
	for (int i = 0; i < ROT; i++)
	{
		rotation[curr] = i;
		if (permu2(curr + 1))
			return true;
	}
	return false;
}

bool permu(int curr)
{
	if (curr == LEN)
	{
		if (permu2(1))
			return true;
		return false;
	}
	for (int i = 0; i < LEN; i++)
	{
		if (!use[i])
		{
			use[i] = true;
			permutation[curr] = i;
			if (permu(curr + 1))
				return true;
			use[i] = false;
		}
	}
	return false;
}

void rotate(int rot)
{
	for (int idx = 0; idx < LEN; idx++)
		for (int row = 0; row < LEN; row++)
			for (int col = 0; col < LEN; col++)
				plate[idx][rot + 1][LEN - 1 - col][row] = plate[idx][rot][row][col];
}

void inputAndInit()
{
	int in;
	answer = INT_MAX;
	memset(cube, 0, sizeof(cube));
	rotation.assign(LEN, 0);
	permutation.assign(LEN, 0);
	use.assign(LEN, false);
	for (int idx = 0; idx < LEN; idx++)
		for (int row = 0; row < LEN; row++)
			for (int col = 0; col < LEN; col++)
			{
				cin >> in;
				plate[idx][0][row][col] = (bool)in;
			}
	for (int i = 0; i < ROT - 1; i++)
		rotate(i);
}

void solve()
{
	permu(0);
}

void output()
{
	if (answer != INT_MAX)
		cout << answer << "\n";
	else
		cout << "-1\n";
}
