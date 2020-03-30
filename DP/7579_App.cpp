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

#define MAXN 100

void inputAndInit();
void solve();
void output();

int DP(int n, int m);

int N, M, answer;

int arr[MAXN];
int cost[MAXN];
int cache[MAXN][10001];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d %d", &N, &M);
	answer = INT_MAX;
	memset(cache, 0, sizeof(cache));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	for (int i = 0; i < N; i++)
		scanf("%d", &cost[i]);
	cache[0][cost[0]] = arr[0];
}

// DP(i,j) = i 인덱스까지만 고려했을 때, j 코스트가 소모되는 최대 바이트
int DP(int n, int m)
{
	int& ret = cache[n][m];
	if (ret)
		return ret;
	if (n)
	{
		if (m - cost[n] >= 0)
			ret = max(DP(n - 1, m), DP(n - 1, m - cost[n]) + arr[n]);
		else
			ret = DP(n - 1, m);
	}
	return ret;
}

void solve()
{
	for(int i = 1; i < N; i++)
		for (int j = 0; j <= 10000; j++)
		{
			if (DP(i, j) >= M)
				answer = min(answer, j);
		}
}

void output()
{
	printf("%d\n", answer);
}

/*
출처 : https://huiung.tistory.com/120
*/