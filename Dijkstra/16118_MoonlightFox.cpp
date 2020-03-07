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
void solve();
void output();

void dijkstra_fox();
void dijkstra_wolf();
void calcAnswer();

#define TREE 4000

int N, M;
long long answer;

vector<long long> distFox;
vector<double> distWolf[2];
vector<pair<int, int> > cost[TREE];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void dijkstra_fox()
{
	int curr, next, size;
	long long currCost, nextCost;
	priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int > > > pqFox;
	pqFox.push(make_pair(0, 0));

	while (!pqFox.empty())
	{
		currCost = pqFox.top().first;
		curr = pqFox.top().second;

		pqFox.pop();

		if (distFox[curr] < currCost)
			continue;

		size = cost[curr].size();
		for (int i = 0; i < size; i++)
		{
			next = cost[curr][i].first;
			nextCost = cost[curr][i].second + currCost;
			if (nextCost < distFox[next])
			{
				distFox[next] = nextCost;
				pqFox.push(make_pair(nextCost, next));
			}
		}
	}
}

void dijkstra_wolf()
{
	int curr, next, size, flag, nextFlag;
	double currCost, nextCost;
	priority_queue<pair<pair<double, int>, int>, vector<pair<pair<double, int>, int> >, greater<pair<pair<double, int>, int> > > pqWolf;
	pqWolf.push(make_pair(make_pair(0.0, 0), 0));

	while (!pqWolf.empty())
	{
		flag = pqWolf.top().second;
		currCost = pqWolf.top().first.first;
		curr = pqWolf.top().first.second;

		pqWolf.pop();

		if (distWolf[flag][curr] < currCost)
			continue;

		size = cost[curr].size();
		for (int i = 0; i < size; i++)
		{
			next = cost[curr][i].first;
			nextCost = cost[curr][i].second;
			if (flag)
				nextCost *= 2;
			else
				nextCost *= 0.5;
			nextCost += currCost;
			nextFlag = (flag + 1) % 2;
			if (nextCost < distWolf[nextFlag][next])
			{
				distWolf[nextFlag][next] = nextCost;
				pqWolf.push(make_pair(make_pair(nextCost, next), nextFlag));
			}
		}
	}
}

void inputAndInit()
{
	int a, b, d;
	cin >> N >> M;
	distFox.assign(N, LLONG_MAX);
	distWolf[0].assign(N, 1.79e+308);
	distWolf[1].assign(N, 1.79e+308);
	distFox[0] = 0;
	distWolf[0][0] = 0.0;
	answer = 0;
	for (int i = 0; i < M; i++)
	{
		cin >> a >> b >> d;
		cost[a - 1].push_back(make_pair(b - 1, d));
		cost[b - 1].push_back(make_pair(a - 1, d));
	}
}

void calcAnswer()
{
	double minWolf;
	for (int i = 1; i < N; i++)
	{
		minWolf = distWolf[0][i] < distWolf[1][i] ? distWolf[0][i] : distWolf[1][i];
		if ((double)distFox[i] < minWolf && distFox[i] != LLONG_MAX)
			answer++;
	}

}

void solve()
{
	dijkstra_fox();
	dijkstra_wolf();
	calcAnswer();
}

void output()
{
	cout << answer << "\n";
}
