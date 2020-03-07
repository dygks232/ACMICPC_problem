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
void calcAnsStr(int idx1, int idx2);

int answer, len1, len2;
string input1, input2, ansStr;

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
	ansStr = "";
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

void calcAnsStr(int idx1, int idx2)
{
	if (!cache[idx1][idx2])
		return;
	if (cache[idx1][idx2] == cache[idx1 - 1][idx2])
		calcAnsStr(idx1 - 1, idx2);
	else if (cache[idx1][idx2] == cache[idx1][idx2 - 1])
		calcAnsStr(idx1, idx2 - 1);
	else if (cache[idx1][idx2] == cache[idx1 - 1][idx2 - 1] + 1)
	{
		ansStr = input1[idx1 - 1] + ansStr;
		calcAnsStr(idx1 - 1, idx2 - 1);
	}
}

void solve()
{
	answer = DP(len1, len2);
	calcAnsStr(len1, len2);
}

void output()
{
	cout << answer << "\n";
	cout << ansStr << "\n";
}

/*
Reference
https://www.crocus.co.kr/787
*/