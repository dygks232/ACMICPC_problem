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

void inputAndInit();
void solve();
void output();

void dfs(int curr, int r, int c, double val);

int N;

double answer;

double P[4];
int dirR[4] = { 0,0,1,-1 };
int dirC[4] = { 1,-1,0,0 };

bool visit[29][29];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int in;
	scanf("%d", &N);
	memset(visit, 0, sizeof(visit));
	answer = 1.0;
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &in);
		P[i] = in / 100.0;
	}
}

void dfs(int curr, int r, int c, double val)
{
	int nextR, nextC;
	if (curr == N)
	{
		return;
	}

	for (int dir = 0; dir < 4; dir++)
	{
		nextR = r + dirR[dir];
		nextC = c + dirC[dir];
		if (P[dir] == 0.0)
			continue;

		if (visit[nextR][nextC])
		{
			answer -= val * P[dir];
			continue;
		}

		visit[nextR][nextC] = true;
		dfs(curr + 1, nextR, nextC, val * P[dir]);
		visit[nextR][nextC] = false;
	}
}

void solve()
{
	visit[14][14] = true;
	dfs(0, 14, 14, 1.0);
}

void output()
{
	cout.precision(11);
	cout << answer << "\n";
}
