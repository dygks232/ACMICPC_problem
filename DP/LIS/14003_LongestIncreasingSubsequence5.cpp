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

#define MAXN 1000001

void inputAndInit();
void solve();
void output();

void calcLis();
void backtrace(int idx, int num);

int N, answer;

int arr[MAXN];
int POS[MAXN];
vector<int> LIS;
vector<int> LISval;

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

void backtrace(int idx, int num)
{
	int val = num;
	LISval = vector<int>(answer, 0);

	for (int i = idx; i >= 1; i--)
	{
		if (POS[i] == val)
		{
			LISval[val] = arr[i];
			val--;
		}
	}
}

void calcLis()
{
	vector<int>::iterator it;
	for (int i = 1; i <= N; i++)
	{
		it = lower_bound(LIS.begin(), LIS.end(), arr[i]);
		POS[i] = it - LIS.begin();
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
	backtrace(N, answer - 1);
}

void output()
{
	printf("%d\n", answer);
	for (int i = 0; i < answer; i++)
		printf("%d ", LISval[i]);
	printf("\n");
}