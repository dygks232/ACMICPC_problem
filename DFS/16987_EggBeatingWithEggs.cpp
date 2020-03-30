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

void dfs(int curr, int tempAns);

int N, answer;

pair<int, int> arr[8];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d", &N);
	answer = 0;
	for (int i = 0; i < N; i++)
		scanf("%d %d", &arr[i].first, &arr[i].second);
}

void dfs(int curr, int tempAns)
{
	bool isAllBroken = true, currBroken, nextBroken;

	if (curr == N)
	{
		answer = max(answer, tempAns);
		return;
	}

	if (arr[curr].first <= 0)
		dfs(curr + 1, tempAns);
	else
	{
		for (int next = 0; next < N; next++)
		{
			if (curr == next)
				continue;

			if (arr[next].first > 0)
			{
				isAllBroken = false;
				currBroken = nextBroken = false;
				arr[curr].first -= arr[next].second;
				arr[next].first -= arr[curr].second;
				if (arr[curr].first <= 0)
				{
					currBroken = true;
					tempAns++;
				}
				if (arr[next].first <= 0)
				{
					nextBroken = true;
					tempAns++;
				}
				dfs(curr + 1, tempAns);
				arr[curr].first += arr[next].second;
				arr[next].first += arr[curr].second;
				if (currBroken)
					tempAns--;
				if (nextBroken)
					tempAns--;
			}
		}
		if (isAllBroken)
			dfs(curr + 1, tempAns);
	}
}

void solve()
{
	dfs(0, 0);
}

void output()
{
	printf("%d\n", answer);
}