#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<climits>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<deque>
#include<functional>
using namespace std;

#define BLANK 0
#define WALL 1
#define MAXN 20

void inputAndInit();
void solve();
void output();

bool isOutOfBoundary(int r, int c);
bool findPass();
bool arrivePass();

struct _passenger {
	bool exist;
	int endR;
	int endC;
	_passenger() {
		exist = endR = endC = 0;
	}
};

int N, passNum, energy, answer, sR, sC;

int board[MAXN][MAXN];
bool visit[MAXN][MAXN];

int dirR[4] = { -1,0,0,1 };
int dirC[4] = { 0,-1,1,0 };

_passenger pass[MAXN][MAXN];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int inR, inC;
	answer = -1;
	memset(pass, 0, sizeof(pass));
	scanf("%d %d %d", &N, &passNum, &energy);
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &board[r][c]);
		}
	}
	scanf("%d %d", &sR, &sC);
	sR--; sC--;
	for (int i = 0; i < passNum; i++)
	{
		scanf("%d %d", &inR, &inC);
		inR--; inC--;
		scanf("%d %d", &pass[inR][inC].endR, &pass[inR][inC].endC);
		pass[inR][inC].endR--; pass[inR][inC].endC--;
		pass[inR][inC].exist = true;
	}
}

void solve()
{
	while (passNum)
	{
		if (!findPass())
		{
			answer = -1;
			break;
		}
		if (!arrivePass())
		{
			answer = -1;
			break;
		}
		answer = energy;
	}
}

void output()
{
	printf("%d\n", answer);
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r >= N || c >= N || board[r][c] == WALL;
}

bool findPass()
{
	queue<pair<int, pair<int, int> > > Q;
	vector<pair<int, int> > nearPass;
	int currR, currC, nextR, nextC, currDist, prevDist = 0, len, retR, retC;
	memset(visit, false, sizeof(visit));
	Q.push({ 0,{sR,sC} });
	visit[sR][sC] = true;

	if (pass[sR][sC].exist)
	{
		pass[sR][sC].exist = false;
		return true;
	}

	while (!Q.empty())
	{
		currR = Q.front().second.first;
		currC = Q.front().second.second;
		currDist = Q.front().first;
		Q.pop();

		if (currDist > prevDist)
		{
			prevDist = currDist;
			if ((len = nearPass.size()) > 0)
			{
				retR = nearPass[0].first;
				retC = nearPass[0].second;
				for (int i = 1; i < len; i++)
				{
					if (retR > nearPass[i].first)
					{
						retR = nearPass[i].first;
						retC = nearPass[i].second;
					}
					else if (retR == nearPass[i].first && retC > nearPass[i].second)
					{
						retR = nearPass[i].first;
						retC = nearPass[i].second;
					}
				}
				energy -= currDist;
				sR = retR; sC = retC;
				pass[sR][sC].exist = false;
				if (energy > 0)
					return true;
				else
					return false;
			}
		}

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfBoundary(nextR, nextC) || visit[nextR][nextC])
				continue;
			visit[nextR][nextC] = true;
			Q.push({ currDist + 1,{nextR,nextC} });
			if (pass[nextR][nextC].exist)
			{
				nearPass.push_back({ nextR,nextC });
			}
		}
	}
	return false;
}

bool arrivePass()
{
	queue<pair<int, pair<int, int> > > Q;
	int currR, currC, nextR, nextC, currDist;
	memset(visit, false, sizeof(visit));
	Q.push({ 0,{sR,sC} });
	visit[sR][sC] = true;
	
	while (!Q.empty())
	{
		currR = Q.front().second.first;
		currC = Q.front().second.second;
		currDist = Q.front().first;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfBoundary(nextR, nextC) || visit[nextR][nextC])
				continue;
			visit[nextR][nextC] = true;
			Q.push({ currDist + 1,{nextR,nextC} });
			if (nextR == pass[sR][sC].endR && nextC == pass[sR][sC].endC)
			{
				energy -= (currDist + 1);
				if (energy < 0)
					return false;
				passNum--;
				energy += (currDist + currDist + 2);
				sR = nextR; sC = nextC;
				return true;
			}
		}
	}
	return false;
}