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

long long N, answer;

long long cache[100];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

long long DP(int n)
{
	long long& ret = cache[n];
	if (ret != -1)
		return ret;

	ret = 1;
	for (int i = n - 2; i >= 1; i--)
		ret += DP(i);

	return ret;
}

void inputAndInit()
{
	scanf("%d", &N);
	memset(cache, -1, sizeof(cache));
	cache[1] = 1;
	cache[2] = 1;
}

void solve()
{
	answer = DP(N);
}

void output()
{
	printf("%lld\n", answer);
}