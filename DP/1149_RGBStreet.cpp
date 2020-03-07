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
using namespace std;

#define COLOR 3

void inputAndInit();
void init();
void solve();
void output();

int dp(int curr, int color);

int N, answer;

int cache[COLOR][1000];
vector<vector<int>> eachCost;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int in;
	cin >> N;
	eachCost.assign(3, vector<int>());
	for (int i = 0; i < COLOR; i++)
		eachCost[i].assign(N, 0);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < COLOR; j++)
		{
			cin >> in;
			eachCost[j][i] = in;
			cache[j][i] = -1;
		}
	}
	answer = INT_MAX;
}

int dp(int curr, int color)
{
	if (curr == N - 1)
		return eachCost[color][curr];

	int& ret = cache[color][curr];
	if (ret != -1)
		return ret;

	int minValue = INT_MAX;
	for (int i = 0; i < COLOR; i++)
	{
		if (color == i)
			continue;
		minValue = min(minValue, dp(curr + 1, i));
	}
	ret = eachCost[color][curr] + minValue;
	return ret;
}

void solve()
{
	for (int i = 0; i < COLOR; i++)
		answer = min(answer, dp(0, i));
}

void output()
{
	cout << answer << "\n";
}
