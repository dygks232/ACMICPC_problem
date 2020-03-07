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

#define MOD 10007

void inputAndInit();
void solve();
void output();

int DP(int n, int cnt);

int N, answer;

int cache[1001][10];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int DP(int n, int cnt)
{
	int& ret = cache[n][cnt];
	if (ret != -1)
		return ret;
	if (n == 1)
	{
		ret = 1;
		return ret;
	}

	ret = 0;
	for (int i = 0; i <= cnt; i++)
	{
		ret += DP(n - 1, i);
		ret %= MOD;
	}

	return ret;
}

void inputAndInit()
{
	scanf("%d", &N);
	memset(cache, -1, sizeof(cache));
	answer = 0;
}

void solve()
{
	for (int i = 0; i < 10; i++)
		answer += DP(N, i);
	answer %= MOD;
}

void output()
{
	printf("%d\n", answer);
}