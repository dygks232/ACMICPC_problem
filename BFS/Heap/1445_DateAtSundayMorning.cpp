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

int encoding(const int &a, const int &b);
pair<int, int> decoding(const int &a);
void calcAnswer();
bool isOutOfRange(int r, int c);
bool isEnd(int r, int c);
bool isG(int r, int c);
bool isNearG(int r, int c);

#define BLANK 0
#define GARBAGE 1
#define START 2
#define END 3

pair<int, int> answer, nodeS, nodeE;
int R, C;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<vector<int> > board;
vector<vector<bool> > visit;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

bool isNearG(int r, int c)
{
	int nextR, nextC;
	for (int dir = 0; dir < 4; dir++)
	{
		nextR = r + dirR[dir];
		nextC = c + dirC[dir];
		if (isOutOfRange(nextR, nextC))
			continue;
		if (isG(nextR, nextC))
			return true;
	}
	return false;
}

bool isG(int r, int c)
{
	return board[r][c] == GARBAGE;
}

bool isEnd(int r, int c)
{
	return nodeE.first == r && nodeE.second == c;
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

void calcAnswer()
{
	int currR, currC, nextR, nextC, currCode;
	pair<int, int> currAns;
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > PQ;
	PQ.push(make_pair(0, make_pair(nodeS.first, nodeS.second)));
	visit[nodeS.first][nodeS.second] = true;

	while (!PQ.empty())
	{
		currR = PQ.top().second.first;
		currC = PQ.top().second.second;
		currAns = decoding(PQ.top().first);

		PQ.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC])
				continue;
			if (isEnd(nextR, nextC))
			{
				answer = currAns;
				return;
			}

			visit[nextR][nextC] = true;
			if (isG(nextR, nextC))
				/*if (isNearG(nextR, nextC))
					PQ.push(make_pair(encoding(currAns.first + 1, currAns.second + 1), make_pair(nextR, nextC)));
				else*/
					PQ.push(make_pair(encoding(currAns.first + 1, currAns.second), make_pair(nextR, nextC)));
			else
				if (isNearG(nextR, nextC))
					PQ.push(make_pair(encoding(currAns.first, currAns.second + 1), make_pair(nextR, nextC)));
				else
					PQ.push(make_pair(encoding(currAns.first, currAns.second), make_pair(nextR, nextC)));
		}
	}
}

int encoding(const int &a, const int &b)
{
	return 10000 * a + b;
}

pair<int, int> decoding(const int &a)
{
	pair<int, int> ret;
	ret.first = a / 10000;
	ret.second = a % 10000;
	return ret;
}

void inputAndInit()
{
	char ch;
	cin >> R >> C;
	board.assign(R, vector<int>(C, 0));
	visit.assign(R, vector<bool>(C, false));
	for(int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
		{
			cin >> ch;
			switch (ch)
			{
			case '.': board[r][c] = BLANK;
				break;
			case 'g': board[r][c] = GARBAGE;
				break;
			case 'S': board[r][c] = START;
				nodeS = make_pair(r, c);
				break;
			case 'F': board[r][c] = END;
				nodeE = make_pair(r, c);
				break;
			}
		}
}

void solve()
{
	calcAnswer();
}

void output()
{
	cout << answer.first << " " << answer.second << "\n";
}
