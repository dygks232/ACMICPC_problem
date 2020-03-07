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

int DP1(int n);
int DP2(int n);

int N, answer;

int arr[MAXN];
int cache1[MAXN];
int cache2[MAXN];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int DP1(int n)
{
	int& ret = cache1[n];
	if (ret != -1)
		return ret;

	ret = 0;
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < arr[n])
			ret = max(ret, DP1(i));
	}
	ret++;

	return ret;
}

int DP2(int n)
{
	int& ret = cache2[n];
	if (ret != -1)
		return ret;

	ret = 0;
	for (int i = N; i > n; i--)
	{
		if (arr[n] > arr[i])
			ret = max(ret, DP2(i));
	}
	ret++;

	return ret;
}

void inputAndInit()
{
	memset(cache1, -1, sizeof(cache1));
	memset(cache2, -1, sizeof(cache2));
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &arr[i]);
	cache1[1] = 1;
	cache2[N] = 1;
	answer = INT_MIN;
}

void solve()
{
	int ans1 = INT_MIN, ans2 = INT_MIN;
	for (int i = 1; i <= N; i++)
	{
		answer = max(answer, DP1(i) + DP2(i) - 1);
	}
}

void output()
{
	printf("%d\n", answer);
}