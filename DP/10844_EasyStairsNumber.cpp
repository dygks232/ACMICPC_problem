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

long long DP(int n);

long long N, answer;

long long cache[101][11];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

long long DP(int n)
{
	long long& ret = cache[n][10];
	if (ret != -1)
		return ret;
	if (n == 1)
	{
		cache[n][0] = 0;
		for (int i = 1; i <= 9; i++)
		{
			cache[n][i] = 1;
		}
		ret = 9;
		return ret;
	}

	DP(n - 1);
	ret = 0;
	for (int i = 0; i < 10; i++)
	{
		switch (i)
		{
		case 0:
			ret += cache[n - 1][i];
			cache[n][i] = cache[n - 1][1];
			break;
		case 9:
			ret += cache[n - 1][i];
			cache[n][i] = cache[n - 1][8];
			break;
		default:
			ret += (cache[n - 1][i] << 1);
			cache[n][i] = cache[n - 1][i - 1] + cache[n - 1][i + 1];
			break;
		}
		cache[n][i] %= MOD;
		ret %= MOD;
	}

	return ret;
}

void inputAndInit()
{
	scanf("%d", &N);
	memset(cache, -1, sizeof(cache));
}

void solve()
{
	answer = DP(N);
}

void output()
{
	printf("%lld\n", answer);
}