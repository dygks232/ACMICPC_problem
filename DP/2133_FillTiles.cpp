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

int DP(int n);

int N, answer;

int cache[31];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int DP(int n)
{
	int& ret = cache[n];
	if (ret != -1)
		return ret;

	if (n & 1)
	{
		ret = 0;
		return ret;
	}

	int num = n;
	ret = 3 * DP(n - 2) + 2;
	for (num = n; num - 4 > 0; num -= 2)
	{
		ret += 2 * DP(num - 4);
	}

	return ret;
}

void inputAndInit()
{
	scanf("%d", &N);
	memset(cache, -1, sizeof(cache));
	cache[2] = 3;
	cache[4] = 11;
}

void solve()
{
	answer = DP(N);
}

void output()
{
	printf("%d\n", answer);
}