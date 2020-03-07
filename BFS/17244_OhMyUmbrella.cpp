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

bool isWall(int r, int c);
int isNodeN(int r, int c);
void calcDist(int r, int c, int idx);
void calcAnswer(int curr, int num);

#define WALL -1
#define BLANK 0
#define START 1
#define NODE 2
#define END 3

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

int answer, R, C, nodeNum, tempNum;
pair<int, int> nodeS, nodeE;

vector<vector<int> > board;
vector<vector<bool> > visit;
vector<vector<int> > link;
vector<pair<int, int> > nodeX;
vector<bool> use;
vector<int> useIdx;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

void calcAnswer(int curr, int num)
{
	if (num == nodeNum - 2)
	{
		if (num)
		{
			int sum = link[0][useIdx[0]];
			for (int i = 0; i < nodeNum - 3; i++)
				sum += link[useIdx[i]][useIdx[i + 1]];
			sum += link[useIdx[nodeNum - 3]][nodeNum - 1];
			answer = min(answer, sum);
		}
		else
			answer = min(answer, link[0][1]);
		return;
	}

	for (int i = 0; i < nodeNum - 2; i++)
	{
		if (!use[i])
		{
			use[i] = true;
			useIdx[num] = i + 1;
			calcAnswer(i + 1, num + 1);
			useIdx[num] = -1;
			use[i] = false;
		}
	}
}

bool isWall(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C || board[r][c] == WALL;
}

int isNodeN(int r, int c)
{
	for (int i = 0; i < nodeNum - 2; i++)
		if (nodeX[i].first == r && nodeX[i].second == c)
			return i;
	return -1;
}

void calcDist(int r, int c, int idx)
{
	init();
	int currR, currC, nextR, nextC, currDist;
	queue<pair<pair<int, int>, int> > Q;
	Q.push(make_pair(make_pair(r, c), 0));
	visit[r][c] = true;

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
			if (isWall(nextR, nextC) || visit[nextR][nextC])
				continue;

			visit[nextR][nextC] = true;
			Q.push(make_pair(make_pair(nextR, nextC), currDist + 1));
			switch (board[nextR][nextC])
			{
			case START: link[idx][0] = currDist + 1;
				tempNum--;
				break;
			case END: link[idx][nodeNum - 1] = currDist + 1;
				tempNum--;
				break;
			case NODE: link[idx][isNodeN(nextR, nextC) + 1] = currDist + 1;
				tempNum--;
				break;
			}
			if (!tempNum)
				return;
		}
	}
}

void inputAndInit()
{
	char ch;
	cin >> C >> R;
	answer = INT_MAX;
	board.assign(R, vector<int>(C, 0));
	visit.assign(R, vector<bool>(C, false));
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			cin >> ch;
			switch (ch)
			{
			case '#': board[r][c] = WALL;
				break;
			case '.': board[r][c] = BLANK;
				break;
			case 'S': board[r][c] = START;
				nodeS = make_pair(r, c);
				break;
			case 'E': board[r][c] = END;
				nodeE = make_pair(r, c);
				break;
			case 'X': board[r][c] = NODE;
				nodeX.push_back(make_pair(r, c));
				break;
			}
		}
	}
	nodeNum = nodeX.size() + 2;
	link.assign(nodeNum, vector<int>(nodeNum, 0));
	use.assign(nodeNum - 2, false);
	useIdx.assign(nodeNum - 2, -1);
}

void init()
{
	tempNum = nodeNum;
	visit.assign(R, vector<bool>(C, false));
}

void solve()
{
	calcDist(nodeS.first, nodeS.second, 0);
	calcDist(nodeE.first, nodeE.second, nodeNum - 1);
	for (int i = 0; i < nodeNum - 2; i++)
		calcDist(nodeX[i].first, nodeX[i].second, i + 1);
	calcAnswer(0, 0);
}

void output()
{
	cout << answer << "\n";
}
