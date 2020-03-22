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

#define LIMIT 500000
#define SEGSIZE (1 << (1 + (int)ceil(log2(LIMIT))))

void inputAndInit();
void solve();
void output();

void update_segTree(int node, int start, int end, int index, int diff);
int sum_segTree(int node, int start, int end, int left, int right);
bool comp1(pair<int, int> a, pair<int, int> b);
bool comp2(pair<int, int> a, pair<int, int> b);

int N, len;

pair<int, int> arr[LIMIT];
int segTree[SEGSIZE];
int answer[LIMIT];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool comp1(pair<int, int> a, pair<int, int> b)
{
	if (a.first < b.first)
		return true;
	return false;
}

bool comp2(pair<int, int> a, pair<int, int> b)
{
	if (a.second < b.second)
		return true;
	return false;
}

void inputAndInit()
{
	scanf("%d", &N);
	memset(segTree, 0, sizeof(segTree));
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &(arr[i].first));
		arr[i].second = i;
	}
}

void update_segTree(int node, int start, int end, int index, int diff)
{
	if (index < start || index > end)
		return;
	segTree[node] += diff;
	if (start != end)
	{
		int mid = (start + end) / 2;
		update_segTree(node * 2 + 1, start, mid, index, diff);
		update_segTree(node * 2 + 2, mid + 1, end, index, diff);
	}
}

int sum_segTree(int node, int start, int end, int left, int right)
{
	if (left > end || right < start)
		return 0;
	if (left <= start && end <= right)
		return segTree[node];
	int mid = (start + end) / 2;
	return sum_segTree(node * 2 + 1, start, mid, left, right) + sum_segTree(node * 2 + 2, mid + 1, end, left, right);
}

void solve()
{
	sort(arr, arr + N, comp1);
	for (int i = 0; i < N; i++)
		arr[i].first = i;
	sort(arr, arr + N, comp2);
	
	for (int i = 0; i < N; i++)
	{
		answer[i] = i + 1 - sum_segTree(0, 0, N - 1, 0, arr[i].first);
		update_segTree(0, 0, N - 1, arr[i].first, 1);
	}
}

void output()
{
	for (int i = 0; i < N; i++)
		printf("%d\n", answer[i]);
}