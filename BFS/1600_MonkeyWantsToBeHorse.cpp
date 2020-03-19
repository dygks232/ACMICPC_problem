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

void bfs();
bool isOutOfRange(int r, int c);
bool isAnswer(int r, int c);

#define WRONG_ANSWER -1
#define MOVE_MONKEY 4
#define MOVE 12
#define MAX_MOVE_HORSE 31

struct info {
	int pos;
	unsigned short dist;
	char horse;
	info() { pos = dist = horse = 0; }
	info(int p, unsigned short d, char h) {
		pos = p; dist = d; horse = h;
	}
};

int K, C, R, answer;

int dirR[12] = { -1,0,1,0,-2,-2,-1,1,2,2,1,-1 };
int dirC[12] = { 0,-1,0,1,-1,1,2,2,1,-1,-2,-2 };

vector<vector<bool> > inputMap;
vector<vector<bool> > visit[MAX_MOVE_HORSE];

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

bool isAnswer(int r, int c)
{
	return r == R - 1 && c == C - 1;
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C || inputMap[r][c];
}

void bfs()
{
	queue<info> Q;
	int currR, currC, nextR, nextC;
	char currHorse;
	unsigned short currDist;
	Q.push(info());

	while (!Q.empty())
	{
		currR = Q.front().pos / 300;
		currC = Q.front().pos % 300;
		currDist = Q.front().dist;
		currHorse = Q.front().horse;
		//visit[currHorse][currR][currC] = true;
		Q.pop();

		for (int dir = 0; dir < MOVE; dir++)
		{
			if (currHorse >= K && dir >= MOVE_MONKEY)
				break;
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC))
				continue;
			if (isAnswer(nextR, nextC))
			{
				answer = currDist + 1;
				return;
			}
			if (dir < MOVE_MONKEY && !visit[currHorse][nextR][nextC])
			{
				visit[currHorse][nextR][nextC] = true;
				Q.push(info(nextR * 300 + nextC, currDist + 1, currHorse));
			}
			else if (dir >= MOVE_MONKEY && !visit[currHorse + 1][nextR][nextC])
			{
				visit[currHorse + 1][nextR][nextC] = true;
				Q.push(info(nextR * 300 + nextC, currDist + 1, currHorse + 1));
			}
		}
	}
}

void inputAndInit()
{
	int in;
	cin >> K >> C >> R;
	answer = WRONG_ANSWER;
	inputMap.assign(R, vector<bool>(C, false));
	for (int i = 0; i < MAX_MOVE_HORSE; i++)
		visit[i].assign(R, vector<bool>(C, false));
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			cin >> in;
			if (in)
				inputMap[i][j] = true;
		}
}

void solve()
{
	if (R > 1 || C > 1)
		bfs();
	else
		answer = 0;
}

void output()
{
	cout << answer << "\n";
}
