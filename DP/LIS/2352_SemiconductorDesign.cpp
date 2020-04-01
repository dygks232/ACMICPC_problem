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

#define MAXN 40000

void inputAndInit();
void solve();
void output();

void calcLis();

int N, answer;

int arr[MAXN + 1];

vector<int> LIS;

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
	for (int i = 1; i <= N; i++)
		scanf("%d", &arr[i]);
	answer = INT_MIN;
}

void calcLis()
{
	vector<int>::iterator it;
	for (int i = 1; i <= N; i++)
	{
		it = lower_bound(LIS.begin(), LIS.end(), arr[i]);
		if (it == LIS.end())
			LIS.push_back(arr[i]);
		else
			*it = arr[i];
	}
	answer = LIS.size();
}

void solve()
{
	calcLis();
}

void output()
{
	printf("%d\n", answer);
}