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

#define MAXN 100
#define MAXW 100000

void inputAndInit();
void solve();
void output();

int DP(int currIdx, int currLimit);

int N, W, answer;

int value[MAXN + 1];
int weight[MAXN + 1];
int cache[MAXN + 1][MAXW + 1];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int DP(int currIdx, int currLimit)
{
	int& ret = cache[currIdx][currLimit];
	if (ret != -1)
		return ret;

	if (weight[currIdx] > currLimit)
		ret = DP(currIdx - 1, currLimit);
	else
		ret = max(DP(currIdx - 1, currLimit), value[currIdx] + DP(currIdx - 1, currLimit - weight[currIdx]));

	return ret;
}

void inputAndInit()
{
	scanf("%d %d", &N, &W);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d %d", &weight[i], &value[i]);
	}
	memset(cache, -1, sizeof(cache));
	memset(cache, 0, sizeof(cache[0]));
	for (int r = 1; r <= MAXN; r++)
		cache[r][0] = 0;
}

void solve()
{
	answer = DP(N, W);
}

void output()
{
	printf("%d\n", answer);
}