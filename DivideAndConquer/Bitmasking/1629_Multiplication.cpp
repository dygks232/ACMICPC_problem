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

void inputAndInit();
void solve();
void output();

void makeArr();

long long answer, A, B, C;

long long arr[40];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void makeArr()
{
	arr[0] = A;
	for (int i = 1; i <= 32; i++)
		arr[i] = (arr[i - 1] * arr[i - 1]) % C;
}

void inputAndInit()
{
	scanf("%lld %lld %lld", &A, &B, &C);
	answer = 1;
	makeArr();
}

void solve()
{
	for (int i = 0; i < 32; i++)
	{
		if (B & (1 << i))
		{
			answer *= arr[i];
			answer %= C;
		}
	}
}

void output()
{
	printf("%d\n", answer);
}
