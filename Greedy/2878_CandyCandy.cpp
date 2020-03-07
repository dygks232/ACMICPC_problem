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

void inputAndInit();
void init();
void solve();
void output();

unsigned long long M;
int N;
unsigned long long answer;

map<unsigned long long, int> mp;

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
	cin >> M >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> in;
		if (mp.find(in) != mp.end())
			mp[in]++;
		else
			mp[in] = 1;
	}
	answer = 0;
}

void solve()
{
	map<unsigned long long, int>::iterator it;
	map<unsigned long long, int>::reverse_iterator rit;
	unsigned long long num = 0;
	while (M)
	{
		rit = mp.rbegin();
		num = min((rit->second), (int)M);
		M -= num;
		rit->second -= num;
		if (mp.find(rit->first - 1) != mp.end())
			mp[rit->first - 1] += num;
		else
			mp[rit->first - 1] = num;
		if (rit->second == 0)
			mp.erase(rit->first);
	}

	for (it = mp.begin(); it != mp.end(); it++)
	{
		answer += (it->first) * (it->first) * (it->second);
	}
}

void output()
{
	cout << answer << "\n";
}