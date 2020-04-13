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

#define MAXN 10001

void inputAndInit();
void solve();
void output();

int T, N, M, answer;

deque<pair<int, int> > deq;
map<int, int> dict;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

void inputAndInit()
{
	int in;
	scanf("%d %d", &N, &M);
	deq.clear();
	dict.clear();
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &in);
		deq.push_back({ in,i });
		if (dict.find(in) == dict.end())
			dict[in] = 1;
		else
			dict[in]++;
	}
}

void solve()
{
	int cnt = 1;
	while (1)
	{
		if (deq[0].first == dict.rbegin()->first)
		{
			if (deq[0].second == M)
			{
				answer = cnt;
				break;
			}
			else
			{
				if (dict.rbegin()->second == 1)
					dict.erase(deq[0].first);
				else
					dict.rbegin()->second -= 1;
				cnt++;
				deq.pop_front();
			}
		}
		else
		{
			deq.push_back(deq[0]);
			deq.pop_front();
		}
	}
}

void output()
{
	printf("%d\n", answer);
}
