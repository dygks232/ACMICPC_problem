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

void inputAndInit();
void init();
void solve();
void output();
void solveAndOutput();

void grouping(int curr);
void calcAnswer();
void spread(int curr, int groupIdx, int &num);

#define groupA 0
#define groupB 1

int N, answer;

vector<int> population;
vector<vector<int> > link;
vector<bool> visit;
vector<bool> group;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

void spread(int curr, int groupIdx, int& num)
{
	int next;
	visit[curr] = true;

	for (int i = 0; i < link[curr].size(); i++)
	{
		next = link[curr][i];
		if (!visit[next] && group[next] == groupIdx)
		{
			num++;
			spread(next, groupIdx, num);
		}
	}
}

void grouping(int curr)
{
	if (curr == N)
	{
		calcAnswer();
		return;
	}
	group[curr] = groupA;
	grouping(curr + 1);
	group[curr] = groupB;
	grouping(curr + 1);
}

void calcAnswer()
{
	int numA = 0, numB = 0, popA = 0, popB = 0;

	for (int i = 0; i < N; i++)
	{
		if (group[i] == groupA)
		{
			visit.assign(N, 0);
			numA++;
			spread(i, groupA, numA);
			break;
		}
	}

	for (int i = 0; i < N; i++)
	{
		if (group[i] == groupB)
		{
			visit.assign(N, 0);
			numB++;
			spread(i, groupB, numB);
			break;
		}
	}

	if (numA == 0 || numB == 0 || numA + numB < N)
		return;
	
	for (int i = 0; i < N; i++)
	{
		if (group[i] == groupA)
			popA += population[i];
		else
			popB += population[i];
	}
	answer = min(answer, abs(popA - popB));
}

void inputAndInit()
{
	int a, b;
	cin >> N;
	answer = INT_MAX;
	population.assign(N, 0);
	link.assign(N, vector<int>());
	group.assign(N, false);
	for (int i = 0; i < N; i++)
	{
		cin >> a;
		population[i] = a;
	}
	for (int i = 0; i < N; i++)
	{
		cin >> a;
		link[i].assign(a, 0);
		for (int j = 0; j < a; j++)
		{
			cin >> b;
			link[i][j] = b - 1;
		}
	}
}

void solve()
{
	grouping(0);
}

void output()
{
	if (answer == INT_MAX)
		cout << "-1\n";
	else
		cout << answer << "\n";
}