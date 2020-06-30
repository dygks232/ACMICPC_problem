#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<deque>
#include<algorithm>
#include<functional>
#include<climits>
using namespace std;

#define MAXN 10000

void inputAndInit();
void solve();
void output();

void bfs();
int doD(int currNum);
int doS(int currNum);
int doL(int currNum);
int doR(int currNum);

int T, A, B;
string answer;

int cost[MAXN];

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
	scanf("%d %d", &A, &B);
	answer = "";
	memset(cost, -1, sizeof(cost));
	cost[A] = 0;
}

int doD(int currNum)
{
	return (currNum + currNum) % MAXN;
}

int doS(int currNum)
{
	int ret = currNum - 1;
	if (ret < 0)
		ret = MAXN - 1;
	return ret;
}

int doL(int currNum)
{
	return (currNum % 1000) * 10 + (currNum / 1000);
}

int doR(int currNum)
{
	return (currNum / 10) + (currNum % 10) * 1000;
}

void bfs()
{
	queue<pair<int, string> > Q;
	int curr, next, currLen;
	string currAns;
	Q.push({ A,answer });

	while (!Q.empty())
	{
		curr = Q.front().first;
		currAns = Q.front().second;
		currLen = currAns.length();
		Q.pop();

		next = doD(curr);
		if (cost[next] == -1)
		{
			cost[next] = currLen + 1;
			Q.push({ next, currAns + "D" });
			if (next == B)
			{
				answer = currAns + "D";
				return;
			}
		}

		next = doS(curr);
		if (cost[next] == -1)
		{
			cost[next] = currLen + 1;
			Q.push({ next, currAns + "S" });
			if (next == B)
			{
				answer = currAns + "S";
				return;
			}
		}

		next = doL(curr);
		if (cost[next] == -1)
		{
			cost[next] = currLen + 1;
			Q.push({ next, currAns + "L" });
			if (next == B)
			{
				answer = currAns + "L";
				return;
			}
		}

		next = doR(curr);
		if (cost[next] == -1)
		{
			cost[next] = currLen + 1;
			Q.push({ next, currAns + "R" });
			if (next == B)
			{
				answer = currAns + "R";
				return;
			}
		}
	}
}

void solve()
{
	bfs();
}

void output()
{
	cout << answer << "\n";
}