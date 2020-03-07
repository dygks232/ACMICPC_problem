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

#define CITY 10000
#define CHOICE 20

void dijkstra();

int N, M, K;
long long answer;

vector<pair<int, int> > link[CITY];
vector<vector<long long> > dist;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void dijkstra()
{
	priority_queue<pair<long long, pair<int, int> >, vector<pair<long long, pair<int, int> > >, greater<pair<long long, pair<int, int> > > > pq;
	long long cost, nextCost;
	int choiceNum, curr, next, size;

	pq.push(make_pair(0, make_pair(0, 0)));

	while (!pq.empty())
	{
		cost = pq.top().first;
		choiceNum = pq.top().second.first;
		curr = pq.top().second.second;

		pq.pop();

		if (dist[curr][choiceNum] < cost)
			continue;

		size = link[curr].size();

		for(int it = 0; it < size; it++)
		{
			next = link[curr][it].first;

			nextCost = cost + (long long)link[curr][it].second;
			if (dist[next][choiceNum] > nextCost)
			{
				dist[next][choiceNum] = nextCost;
				pq.push(make_pair(nextCost, make_pair(choiceNum, next)));
			}

			if (choiceNum < K)
			{
				nextCost = cost;
				if (dist[next][choiceNum + 1] > nextCost)
				{
					dist[next][choiceNum + 1] = nextCost;
					pq.push(make_pair(nextCost, make_pair(choiceNum + 1, next)));
				}
			}
		}
	}
}

void inputAndInit()
{
	int c1, c2, cost;
	//cin >> N >> M >> K;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < M; i++)
	{
		//cin >> c1 >> c2 >> cost;
		scanf("%d %d %d", &c1, &c2, &cost);
		link[c1 - 1].push_back(make_pair(c2 - 1, cost));
		link[c2 - 1].push_back(make_pair(c1 - 1, cost));
	}
	answer = LLONG_MAX;
	dist.assign(N, vector<long long>(K + 1, LLONG_MAX));
	dist[0][0] = 0;
}

void solve()
{
	dijkstra();
	for (int i = 0; i <= K; i++)
		answer = min(answer, dist[N - 1][i]);
}

void output()
{
	//cout << answer << "\n";
	printf("%lld\n", answer);
}
