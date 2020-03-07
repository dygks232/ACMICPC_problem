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

bool isAnswer();
void calc(int idx);

int N, M, K;
bool answer;

vector<set<int> > link;
vector<int> destroy;
vector<bool> checked;
vector<bool> isDestroy;
set<int> answerList;
set<int>::iterator it;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

void inputAndInit()
{
	int a, b;
	//cin >> N >> M;
	scanf("%d %d", &N, &M);
	link.assign(N, set<int>());
	isDestroy.assign(N, false);
	for (int i = 0; i < M; i++)
	{
		//cin >> a >> b;
		scanf("%d %d", &a, &b);
		link[a - 1].insert(b - 1);
		link[b - 1].insert(a - 1);
	}
	cin >> K;
	destroy.assign(K, 0);
	checked.assign(K, true);
	for (int i = 0; i < K; i++)
	{
		//cin >> destroy[i];
		scanf("%d", &destroy[i]);
		destroy[i]--;
		isDestroy[destroy[i]] = true;
	}
}

void calc(int idx)
{
	for (it = link[idx].begin(); it != link[idx].end(); it++)
		if (!isDestroy[*it])
			return;
	answerList.insert(idx);
}

bool isAnswer()
{
	bool find;

	for (int i = 0; i < K; i++)
	{
		find = false;
		for (it = answerList.begin(); it != answerList.end(); it++)
		{
			if (destroy[i] == *it || link[destroy[i]].find(*it) != link[destroy[i]].end())
			{
				find = true;
				break;
			}
		}
		if (!find)
			return false;
	}
	return true;
}

void solve()
{
	for (int i = 0; i < K; i++)
		calc(destroy[i]);
	answer = isAnswer();
}

void output()
{
	if (!answer)
		printf("-1\n");
	else
	{
		int size = answerList.size();
		printf("%d\n", size);
		for (it = answerList.begin(); it != answerList.end(); it++)
			printf("%d ", (*it) + 1);
	}
}