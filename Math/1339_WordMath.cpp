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

bool comp(int a, int b);

int N, answer;
char input[10][9];
int table[26];
int cnt[10][8];
int score[10];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int idx;
	scanf("%d", &N);
	idx = answer = 0;
	memset(table, -1, sizeof(table));
	memset(cnt, 0, sizeof(cnt));
	memset(score, 0, sizeof(score));
	for (int i = 0; i < N; i++)
	{
		scanf("%s", input[i]);
		for (int j = 0; j < strlen(input[i]); j++)
		{
			if (table[input[i][j] - 'A'] < 0)
				table[input[i][j] - 'A'] = idx++;
		}
	}
}

bool comp(int a, int b)
{
	if (a > b)
		return true;
	return false;
}

void solve()
{
	int digit;
	for (int i = 0; i < N; i++)
	{
		digit = 0;
		for (int j = strlen(input[i]) - 1; j >= 0; j--, digit++)
			cnt[table[input[i][j] - 'A']][digit]++;
	}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 8; j++)
			score[i] += cnt[i][j] * pow(10.0, j);
	sort(score, score + 10, comp);
	for (int i = 0; i < 10; i++)
		answer += score[i] * (9 - i);
}

void output()
{
	printf("%d\n", answer);
}