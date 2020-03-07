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

int docking(int g);

int G, P, answer;

vector<int> gi;
vector<bool> visit;
vector<int> flag;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

int docking(int g)
{
	bool isPossible = false;
	int ret;
	for (int i = g; i >= 0; i--)
	{
		if (!visit[i])
		{
			ret = i;
			visit[i] = true;
			isPossible = true;
			break;
		}
	}
	if (isPossible)
		return ret;
	else
		return -1;
}

void inputAndInit()
{
	int in;
	cin >> G >> P;
	answer = 0;
	gi.assign(P, 0);
	visit.assign(G, false);
	flag.assign(G, 0);
	for (int i = 0; i < P; i++)
	{
		cin >> in;
		gi[i] = in - 1;
		if (flag[gi[i]])
		{
			flag[gi[i] - flag[gi[i]]]++;
			flag[gi[i]]++;
			answer++;
		}
		else
		{
			flag[gi[i]]++;
			answer++;
		}
	}
}

void solve()
{
	for (int i = 0; i < P; i++)
	{
		if (docking(gi[i]) < 0)
		{
			break;
		}
		else
			answer = i + 1;
	}
}

void output()
{
	cout << answer << "\n";
}