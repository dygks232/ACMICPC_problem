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

void inputAndInit();
void solve();
void output();

void mergeSort(int s, int e);
void merge(int s, int m, int e);

int N, len;

pair<int, int> arr[LIMIT];
pair<int, int> temp[LIMIT];
int answer[LIMIT];

set<int> test;

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
	len = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &(arr[i].first));
		arr[i].second = i;
		answer[i] = 1;
	}
}

void mergeSort(int s, int e)
{
	int m = (s + e) / 2;
	if (s < e)
	{
		mergeSort(s, m);
		mergeSort(m + 1, e);
		merge(s, m, e);
	}
}

void merge(int s, int m, int e)
{
	int idxL = s, idxR = m + 1, idxT = 0;
	while (idxL <= m && idxR <= e)
	{
		if (arr[idxL].first < arr[idxR].first)
		{
			temp[idxT++] = arr[idxL++];
		}
		else
		{
			answer[arr[idxR].second] += (m - idxL + 1);
			temp[idxT++] = arr[idxR++];
		}
	}
	while (idxL <= m)
		temp[idxT++] = arr[idxL++];
	while (idxR <= e)
		temp[idxT++] = arr[idxR++];
	for (int i = 0; i <= e - s; i++)
		arr[i + s] = temp[i];
}

void solve()
{
	mergeSort(0, N - 1);
}

void output()
{
	for (int i = 0; i < N; i++)
		printf("%d\n", answer[i]);
}