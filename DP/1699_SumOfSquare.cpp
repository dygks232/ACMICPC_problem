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

int cache[100001];

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

	ret = INT_MAX;
	for (int i = 1; i * i <= n; i++)
	{
		ret = min(ret, 1 + DP(n - i * i));
	}

	return ret;
}

void inputAndInit()
{
	scanf("%d", &N);
	memset(cache, -1, sizeof(cache));
	cache[0] = 0;
	cache[1] = 1;
	cache[2] = 2;
	cache[3] = 3;
}

void solve()
{
	answer = DP(N);
}

void output()
{
	printf("%d\n", answer);
}
