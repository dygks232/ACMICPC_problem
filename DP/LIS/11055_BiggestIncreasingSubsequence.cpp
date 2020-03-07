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

#define MAXN 1001

void inputAndInit();
void solve();
void output();

int DP(int n);

int N, answer;

int arr[MAXN];
int cache[MAXN];

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

	ret = 0;
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < arr[n])
			ret = max(ret, DP(i));
	}
	ret += arr[n];

	return ret;
}

void inputAndInit()
{
	memset(cache, -1, sizeof(cache));
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &arr[i]);
	cache[1] = arr[1];
	answer = INT_MIN;
}

void solve()
{
	for (int i = 1; i <= N; i++)
		answer = max(answer, DP(i));
}

void output()
{
	printf("%d\n", answer);
}