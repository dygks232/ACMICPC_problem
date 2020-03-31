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

#define MAXN 500001

void inputAndInit();
void solve();
void output();

int sum(int i);
void update(int i, int diff);

int N, H;
pair<int, int> answer;

int tree[MAXN];

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
	scanf("%d %d", &N, &H);
	answer = { 0,0 };
	memset(tree, 0, sizeof(tree));
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &in);
		if (i & 1)
		{
			update(H - in + 1, 1);
		}
		else
		{
			update(1, 1);
			update(1 + in, -1);
		}
	}
}

int sum(int i)
{
	int ans = 0;
	while (i > 0)
	{
		ans += tree[i];
		i -= (i & -i);
	}

	return ans;
}

void update(int i, int diff)
{
	while (i < MAXN)
	{
		tree[i] += diff;
		i += (i & -i);
	}
}

void solve()
{
	int temp;
	answer = { sum(1),1 };
	for (int i = 2; i <= H; i++)
	{
		temp = sum(i);
		if (answer.first > temp)
			answer = { temp,1 };
		else if (answer.first == temp)
			answer.second++;
	}
}

void output()
{
	printf("%d %d\n", answer.first, answer.second);
}