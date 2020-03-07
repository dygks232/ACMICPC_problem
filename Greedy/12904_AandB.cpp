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

int answer;
bool flag;

string S, T;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	cin >> S;
	cin >> T;
	flag = false;
}

void reverseStr(string& in, int len)
{
	string temp = "";
	for (int i = len - 1; i >= 0; i--)
		temp += in[i];
	in = temp;
}

void solve()
{
	int lenS = S.length();
	int lenT = T.length();
	int idx = 0;
	string temp = "";
	while (lenS < lenT)
	{
		if (T[lenT - 1] == 'B')
		{
			T.pop_back();
			lenT--;
			reverseStr(T, lenT);
		}
		else
		{
			T.pop_back();
			lenT--;
		}
	}
	if (S == T)
		answer = 1;
	else
		answer = 0;
}

void output()
{
	printf("%d\n", answer);
}