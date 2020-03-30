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

void play(int noPlay);

int N, K, answer;

int advantage[9][9];
int order[3][20];
int idx[3];
int win[3];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d %d", &N, &K);
	answer = 0;
	for (int i = 0; i < N; i++)
	{
		order[0][i] = i;
		for (int j = 0; j < N; j++)
			scanf("%d", &advantage[i][j]);
	}
	for(int i = 1; i < 3; i++)
		for (int j = 0; j < 20; j++)
		{
			scanf("%d", &order[i][j]);
			order[i][j]--;
		}
}

void play(int noPlay)
{
	if (win[0] >= K)
	{
		answer = 1;
		return;
	}
	if (win[1] >= K || win[2] >= K || idx[0] == N || (idx[1] >= 20 && noPlay != 1) || (idx[2] >= 20 && noPlay != 2))
		return;

	int result;

	switch (noPlay)
	{
	case 0:
		result = advantage[order[1][idx[1]++]][order[2][idx[2]++]];
		switch (result)
		{
		case 0:
		case 1:
			win[2]++;
			play(1);
			break;
		case 2:
			win[1]++;
			play(2);
			break;
		}
		break;
	case 1:
		result = advantage[order[0][idx[0]++]][order[2][idx[2]++]];
		switch (result)
		{
		case 0:
		case 1:
			win[2]++;
			play(0);
			break;
		case 2:
			win[0]++;
			play(2);
			break;
		}
		break;
	case 2:
		result = advantage[order[0][idx[0]++]][order[1][idx[1]++]];
		switch (result)
		{
		case 0:
		case 1:
			win[1]++;
			play(0);
			break;
		case 2:
			win[0]++;
			play(1);
			break;
		}
		break;
	}
}

void solve()
{
	do 
	{
		memset(idx, 0, sizeof(idx));
		memset(win, 0, sizeof(win));
		play(2);
		if (answer)
			break;
	} while (next_permutation(order[0], order[0] + N));
}

void output()
{
	printf("%d\n", answer);
}