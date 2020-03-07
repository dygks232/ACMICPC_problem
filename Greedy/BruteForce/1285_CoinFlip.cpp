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

int N, answer;

int numR[20] = { 0, };

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	char in[21];
	scanf("%d", &N);
	answer = INT_MAX;
	for (int r = 0; r < N; r++)
	{
		scanf("%s", in);
		for (int c = 0; c < N; c++)
		{
			numR[r] *= 2;
			switch (in[c])
			{
			case 'H':
				numR[r] += 0;
				break;
			case 'T':
				numR[r] += 1;
				break;
			}
		}
	}
}

void solve()
{
	int flip, cnt, tempAns;
	for (int c = 0; c < (1 << N); c++)
	{
		tempAns = 0;
		for (int r = 0; r < N; r++)
		{
			cnt = 0;
			flip = numR[r] ^ c;
			while (flip)
			{
				flip -= (flip & -flip);
				cnt++;
			}
			tempAns += min(cnt, N - cnt);
		}
		answer = min(answer, tempAns);
	}
}

void output()
{
	printf("%d\n", answer);
}
