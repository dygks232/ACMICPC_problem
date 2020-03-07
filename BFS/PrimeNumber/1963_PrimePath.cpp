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
#define WRONG_ANSWER -1

void inputAndInit();
void solve();
void output();

void calcPrime(int num);
void bfs(int num);

int T, answer, input1, input2;

int prime[MAXN + 1];
bool visit[MAXN + 1];

int main()
{
	scanf("%d", &T);
	for (int i = 2; i <= MAXN; i++)
		prime[i] = i;
	calcPrime(MAXN);
	prime[1] = -1;
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

void calcPrime(int num)
{
	int i;
	for (i = 2; i <= num; i++)
	{
		if (prime[i] > 0)
			break;
		else if (i == num)
			return;
	}
	prime[i] = 0;
	for (int j = 2; i * j <= num; j++)
		prime[i * j] = -1;
	calcPrime(num);
}

void inputAndInit()
{
	scanf("%d %d", &input1, &input2);
	answer = WRONG_ANSWER;
	memset(visit, 0, sizeof(visit));
}

void bfs(int num)
{
	int curr, next, currDist, div, a, b;
	queue<pair<int, int> > Q;
	Q.push({ 0,num });
	visit[num] = true;

	while (!Q.empty())
	{
		curr = Q.front().second;
		currDist = Q.front().first;
		Q.pop();
		div = 10;
		for (int i = 0; i < 4; i++)
		{
			b = curr % div;
			a = curr - b;
			for (int j = 1; j <= 9; j++)
			{
				next = a + (b + j * div / 10) % div;
				if (i == 3 && !(next / 1000))
					continue;
				if (visit[next] || prime[next])
					continue;
				if (next == input2)
				{
					answer = currDist + 1;
					return;
				}
				visit[next] = true;
				Q.push({ currDist + 1,next });
			}
			div *= 10;
		}
	}
}

void solve()
{
	if (input1 == input2)
		answer = 0;
	else
	{
		bfs(input1);
	}
}

void output()
{
	if (answer != WRONG_ANSWER)
		printf("%d\n", answer);
	else
		printf("Impossible\n");
}
