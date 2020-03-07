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

long long DP(int n);

int T, N;
long long answer;

long long cache[101];

int main()
{
	scanf("%d", &T);
	memset(cache, -1, sizeof(cache));
	cache[1] = cache[2] = cache[3] = 1;
	cache[4] = cache[5] = 2;
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

long long DP(int n)
{
	long long& ret = cache[n];
	if (ret != -1)
		return ret;

	ret = DP(n - 5) + DP(n - 1);

	return ret;
}

void inputAndInit()
{
	scanf("%d", &N);
}

void solve()
{
	answer = DP(N);
}

void output()
{
	printf("%lld\n", answer);
}