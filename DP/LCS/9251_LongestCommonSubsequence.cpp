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

#define MAXN 1000

void inputAndInit();
void solve();
void output();

int DP(int idx1, int idx2);

int answer, len1, len2;
string input1, input2;

int cache[MAXN + 1][MAXN + 1];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	cin >> input1 >> input2;
	len1 = input1.length();
	len2 = input2.length();
	memset(cache, -1, sizeof(cache));
	memset(cache, 0, sizeof(cache[0]));
	for (int i = 1; i < MAXN + 1; i++)
		cache[i][0] = 0;
}

int DP(int idx1, int idx2)
{
	int& ret = cache[idx1][idx2];
	if (ret != -1)
		return ret;

	if (input1[idx1 - 1] != input2[idx2 - 1])
		ret = max(DP(idx1 - 1, idx2), DP(idx1, idx2 - 1));
	else
		ret = DP(idx1 - 1, idx2 - 1) + 1;

	return ret;
}

void solve()
{
	answer = DP(len1, len2);
}

void output()
{
	printf("%d\n", answer);
}

/*
Reference
https://www.crocus.co.kr/787
*/
