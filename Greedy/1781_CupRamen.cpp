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

#define MAXN 200000

void inputAndInit();
void solve();
void output();

int N, M, X, answer;

pair<int, int> arr[MAXN];

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
	for(int i = 0; i < N; i++)
		scanf("%d %d", &(arr[i].first), &(arr[i].second));
}

void solve()
{
	priority_queue<int, vector<int>, greater<int> > PQ;
	sort(arr, arr + N);
	for (int i = 0; i < N; i++)
	{
		PQ.push(arr[i].second);
		while (PQ.size() > arr[i].first)
			PQ.pop();
	}
	while (!PQ.empty())
	{
		answer += PQ.top();
		PQ.pop();
	}
}

void output()
{
	printf("%d\n", answer);
}