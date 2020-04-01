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

#define MAXN 250000

void inputAndInit();
void solve();
void output();

int N, H, halfN;
pair<int, int> answer;

int down[MAXN];
int up[MAXN];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int in;
	scanf("%d %d", &N, &H);
	halfN = N / 2;
	for (int i = 0; i < halfN; i++)
		scanf("%d %d", &down[i], &up[i]);
	sort(down, down + halfN);
	sort(up, up + halfN);
}

void solve()
{
	int tempAns;
	answer = { N - (lower_bound(down, down + halfN, 1) - down) - (lower_bound(up, up + halfN, H) - up),1 };
	for (int h = 2; h <= H; h++)
	{
		tempAns = N - (lower_bound(down, down + halfN, h) - down) - (lower_bound(up, up + halfN, H - h + 1) - up);
		if (answer.first > tempAns)
			answer = { tempAns,1 };
		else if (answer.first == tempAns)
			answer.second++;
	}
}

void output()
{
	printf("%d %d\n", answer.first, answer.second);
}