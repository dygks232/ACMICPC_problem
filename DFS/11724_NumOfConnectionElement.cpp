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

int vertex, edge, answer;

set<int> link[1001];
bool visit[1001] = { 0, };


int main()
{
	inputAndInit();
	solve();
	output();

	return 0;
}

void inputAndInit()
{
	int a, b;
	cin >> vertex >> edge;
	for (int i = 0; i < edge; i++)
	{
		cin >> a >> b;
		link[a].insert(b);
		link[b].insert(a);
	}
}

void dfs(int curV)
{
	visit[curV] = true;
	if (link[curV].empty())
		return;

	set<int>::iterator setIter;
	for (setIter = link[curV].begin(); setIter != link[curV].end(); setIter++)
	{
		if (!visit[*setIter])
		{
			dfs(*setIter);
		}
	}
}

void solve()
{
	for (int i = 1; i <= vertex; i++)
	{
		if (!visit[i])
		{
			dfs(i);
			answer++;
		}
	}
}

void output()
{
	cout << answer << "\n";
}