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

#define MOD 1000000000

void inputAndInit();
void solve();
void output();

int DP(int n, int k);

int answer, N, K;

int cache[201][201];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int DP(int n, int k)
{
	int& ret = cache[n][k];
	if (ret != -1)
		return ret;
	if (k == 1)
	{
		ret = 1;
		return ret;
	}
	if (n == 1)
	{
		ret = k;
		return ret;
	}
	ret = 0;
	for (int i = 1; i <= k; i++)
	{
		ret += DP(n - 1, i);
		ret %= MOD;
	}

	return ret;
}

void inputAndInit()
{
	scanf("%d %d", &N, &K);
	memset(cache, -1, sizeof(cache));
	answer = -1;
}

void solve()
{
	answer = DP(N, K);
}

void output()
{
	printf("%d\n", answer);
}