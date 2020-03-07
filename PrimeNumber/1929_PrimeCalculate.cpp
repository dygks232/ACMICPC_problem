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

#define MAXN 1000001

void inputAndInit();
void solve();
void output();

void calcPrime(int num);

int T, answer, input1, input2;

bool prime[MAXN + 1];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void calcPrime(int num)
{
	for (int i = 0; i <= input2; i++)
		prime[i] = true;

	long long ii;
	for (int i = 2; i <= input2; i++)
	{
		if (prime[i])
		{
			ii = (long long)i * i;
			if (ii > MAXN)
				break;
			else
			{
				for (int j = ii; j <= input2; j += i)
				{
					prime[j] = false;
				}
			}
		}
	}
	prime[1] = false;
}

void inputAndInit()
{
	scanf("%d %d", &input1, &input2);
}

void solve()
{
	calcPrime(input2);
}

void output()
{
	for (int i = input1; i <= input2; i++)
	{
		if (prime[i])
			printf("%d\n", i);
	}
}
