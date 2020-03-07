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

int DP(int n, int cnt);

int N, answer;

int arr[10001];
int cache[10001][3];

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
		switch (cnt)
		{
		case 0: ret = 0;
			break;
		case 1: ret = arr[n];
			break;
		}
		return ret;
	}
	if (n == 2)
	{
		switch (cnt)
		{
		case 0: ret = DP(n - 1, 1);
			break;
		case 1: ret = arr[n];
			break;
		case 2: ret = arr[n] + DP(n - 1, 1);
			break;
		}
		return ret;
	}

	switch (cnt)
	{
	case 0:
		ret = max(DP(n - 1, 0), DP(n - 1, 1));
		ret = max(ret, DP(n - 1, 2));
		break;
	case 1:
		ret = DP(n - 1, 0) + arr[n];
		break;
	case 2:
		ret = DP(n - 1, 1) + arr[n];
		break;
	}
	return ret;
}

void inputAndInit()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &arr[i]);
	memset(cache, -1, sizeof(cache));
}

void solve()
{
	if (N > 1)
	{
		answer = max(DP(N, 0), DP(N, 1));
		answer = max(answer, DP(N, 2));
	}
	else
		answer = arr[1];
}

void output()
{
	printf("%d\n", answer);
}