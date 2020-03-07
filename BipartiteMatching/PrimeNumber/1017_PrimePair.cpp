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

bool p[3000], no[3000];
int n, visited[100], b[100], a[100];

vector<vector<int>> vt;
vector<int> res;

bool dfs (int here) 
{
	if (visited[here])
		return false;

	visited[here] = true;

	for (int there : vt[here]) 
	{
		if (!b[there] || dfs(b[there])) 
		{
			b[there] = here;
			return true;
		}
	}

	return false;
}

int bmatch() {
	memset(b, 0, sizeof(b));

	int c = 0;
	for (int i = 1; i <= n; i++) 
	{
		if (a[i] % 2 != a[1] % 2)
			continue;
		memset(visited, 0, sizeof(visited));
		if (dfs(i))
			c++;
	}
	if (c == n / 2) 
	{
		for (int i = 1; i <= n; i++) 
		{
			if (b[i] == 1) 
			{
				return a[i];
			}
		}
		return 0;
	}
	else
		return 0;
}

int main() {
	p[0] = p[1] = true;

	for (int i = 2; i < 3000; i++) 
	{
		if (p[i])
			continue;
		for (int j = i + i; j < 3000; j += i)
			p[j] = true;
	}

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);

	while (1) 
	{
		vt.clear();
		vt.resize(n + 1);
		for (int i = 1; i <= n; i++) 
		{
			for (int j = 1; j <= n; j++) 
			{
				if (i == j)
					continue;
				if (i == 1 && no[a[j]])
					continue;
				if (!p[a[i] + a[j]])
					vt[i].push_back(j);
			}
		}
		int k = bmatch();
		if (k) 
		{
			res.push_back(k);
			no[k] = true;
		}
		else
			break;
	}
	sort(res.begin(), res.end());
	if (!res.size())
		res.push_back(-1);
	for (auto r : res)
		printf("%d ", r);
	puts("");
	return 0;
}
