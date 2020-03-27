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

#define MOD 1000

void inputAndInit();
void solve();
void output();

bool isUsed();
void bfs();
bool isOutOfRange(int r, int c);

int R, C, green, red, startCnt, answer;

int board[50][50];
int timeMapOrigin[50][50];
int timeMapClone[50][50];
bool visit[50][50];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

pair<int, int> startPos[10];
set<int> use;
vector<int> permutation;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int idx = 0;
	scanf("%d %d %d %d", &R, &C, &green, &red);
	startCnt = answer = 0;
	use.clear();
	memset(timeMapOrigin, 0, sizeof(timeMapOrigin));
	for(int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
		{
			scanf("%d", &board[r][c]);
			if (board[r][c] == 2)
			{
				startPos[idx++] = make_pair(r, c);
				startCnt++;
			}
			else if (!board[r][c])
				timeMapOrigin[r][c] = -1;
		}
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

bool isUsed()
{
	int useFlag, compareFlag;
	useFlag = compareFlag = 0;
	for (int i = 0; i < startCnt; i++)
	{
		useFlag <<= 2;
		compareFlag <<= 2;
		if (permutation[i] == -2)
		{
			useFlag += 1;
			compareFlag += 2;
		}
		else if (permutation[i] == -1)
		{
			useFlag += 2;
			compareFlag += 1;
		}
	}
	if (use.find(compareFlag) != use.end())
		return true;

	use.insert(useFlag);
	return false;
}

void bfs()
{
	queue<pair<pair<int, int>, pair<int, bool> > > Q;
	set<int> answerList;
	int currR, currC, nextR, nextC, currDist, tempAns = 0, flagG, flagR;
	bool isRed;
	memset(visit, false, sizeof(visit));
	memmove(timeMapClone, timeMapOrigin, sizeof(timeMapOrigin));
	for (int i = 0; i < startCnt; i++)
	{
		if (permutation[i] == -2)
		{
			Q.push({ {startPos[i].first,startPos[i].second},{0,false} });
			visit[startPos[i].first][startPos[i].second] = true;
		}
		else if (permutation[i] == -1)
		{
			Q.push({ {startPos[i].first,startPos[i].second},{0,true} });
			visit[startPos[i].first][startPos[i].second] = true;
		}
	}

	while (!Q.empty())
	{
		currR = Q.front().first.first;
		currC = Q.front().first.second;
		currDist = Q.front().second.first;
		isRed = Q.front().second.second;
		Q.pop();
		if (answerList.find(currR * 100 + currC) != answerList.end())
			continue;

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || !board[nextR][nextC] || visit[nextR][nextC])
				continue;
			flagG = timeMapClone[nextR][nextC] % MOD;
			flagR = timeMapClone[nextR][nextC] / MOD;
			if (!isRed)
			{
				if (flagG || (flagR > 0 && flagR < currDist + 1))
					continue;
				timeMapClone[nextR][nextC] += currDist + 1;
				if (flagR == currDist + 1)
				{
					tempAns++;
					answerList.insert(nextR * 100 + nextC);
				}
				else
					Q.push({ {nextR,nextC},{currDist + 1,isRed} });
			}
			else
			{
				if (flagR || (flagG > 0 && flagG < currDist + 1))
					continue;
				timeMapClone[nextR][nextC] += (currDist + 1) * MOD;
				if (flagG == currDist + 1)
				{
					tempAns++;
					answerList.insert(nextR * 100 + nextC);
				}
				else
					Q.push({ {nextR,nextC},{currDist + 1,isRed} });
			}
		}
	}
	answer = max(answer, tempAns);
}

void solve()
{
	permutation.assign(startCnt, 0);
	for (int i = 0; i < green; i++)
		permutation[i] = -2;
	for (int i = green; i < green + red; i++)
		permutation[i] = -1;
	do
	{
		if (isUsed())
			continue;
		bfs();
	} while (next_permutation(permutation.begin(), permutation.end()));
}

void output()
{
	printf("%d\n", answer);
}
