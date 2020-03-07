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

int arr[301];
int cache[301][2];

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
		if (!cnt)
			ret = arr[n];
		else
			ret = 0;
		return ret;
	}
	if (n == 2)
	{
		if (!cnt)
			ret = arr[n];
		else
			ret = arr[n] + DP(n - 1, cnt - 1);
		return ret;
	}

	if (!cnt)
	{
		ret = max(DP(n - 2, 0), DP(n - 2, 1)) + arr[n];
	}
	else
	{
		ret = DP(n - 1, 0) + arr[n];
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
		answer = max(DP(N, 0), DP(N, 1));
	else
		answer = arr[1];
}

void output()
{
	printf("%d\n", answer);
}