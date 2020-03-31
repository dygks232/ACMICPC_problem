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

void solve();
void output();

void binarySearch();

int X, N, halfX, answer;
bool flag, existAnswer;

int input[1000000];

int main()
{
	int x, cnt;
	while (scanf("%d", &x) != EOF)
	{
		X = x * 10000000;
		halfX = X / 2;
		cnt = 0;
		flag = existAnswer = false;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &input[i]);
			if (!flag && input[i] == halfX)
			{
				cnt++;
				if (cnt > 1)
					flag = true;
			}
		}
		sort(input, input + N);

		solve();
		output();
	}
	return 0;
}

void binarySearch()
{
	if ((lower_bound(input, input + N, halfX) - input) < N / 2)
	{
		for (int i = 0; i < N; i++)
		{
			if (input[i] >= halfX)
				break;
			if (input[(lower_bound(input, input + N, X - input[i]) - input)] == X - input[i])
			{
				existAnswer = true;
				answer = input[i];
				break;
			}
		}
	}
	else
	{
		for (int i = N - 1; i >= 0; i--)
		{
			if (input[i] <= halfX)
				break;
			if (input[(lower_bound(input, input + N, X - input[i]) - input)] == X - input[i])
			{
				existAnswer = true;
				answer = X - input[i];
				break;
			}
		}
	}
}

void solve()
{
	binarySearch();
	if (!existAnswer && flag)
	{
		existAnswer = true;
		answer = halfX;
	}
}

void output()
{
	if (existAnswer)
		printf("yes %d %d\n", answer, X - answer);
	else
		printf("danger\n");
}