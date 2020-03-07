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
using namespace std;

void inputAndInit();
void init();
void solve();
void output();

void dfs(int numA, int numZ, int& remainedK, bool& correct);

bool isImpossible();
long long NumOfCase(int numA, int numZ, int remainedK);
double factorial(int num);

int N, M, K;
string answer;
bool impossible = false;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

double factorial(int num)
{
	if (num == 0 || num == 1)
		return 1.0;
	if (num == 2)
		return 2.0;
	return factorial(num - 1) * num;
}

void dfs(int numA, int numZ, int& remainedK, bool& correct)
{
	int nextNumA = numA, nextNumZ = numZ, currentK = remainedK;
	long long caseNum;
	caseNum = NumOfCase(numA, numZ, remainedK);

	if (caseNum > remainedK)
	{
		if (numA)
		{
			answer += "a";
			dfs(numA - 1, numZ, remainedK, correct);
			if (correct)
				return;
		}
		if (remainedK != currentK)
		{
			currentK = remainedK;
			if (numZ)
			{
				answer += "z";
				dfs(numA, numZ - 1, remainedK, correct);
				if (correct)
					return;
			}
		}
	}
	else if (caseNum < remainedK)
	{
		answer.pop_back();
		remainedK -= caseNum;
		return;
	}
	else
	{
		if (remainedK == 1)
		{
			for (int i = 0; i < numA; i++)
				answer += "a";
			for (int i = 0; i < numZ; i++)
				answer += "z";
		}
		else
		{
			for (int i = 0; i < numZ; i++)
				answer += "z";
			for (int i = 0; i < numA; i++)
				answer += "a";
		}
		correct = true;
		return;
	}
}

long long NumOfCase(int numA, int numZ, int remainedK)
{
	int small, big;
	if (numA < numZ)
	{
		small = numA;
		big = numZ;
	}
	else
	{
		small = numZ;
		big = numA;
	}
	if (!small)
		return 1;

	double cmp = (small + big) / factorial(small);
	for (int i = small + big - 1; i >= big + 1; i--)
	{
		cmp *= i;
		if ((long long)round(cmp) > remainedK)
		{
			return round(cmp);
		}
	}
	return round(cmp);
}

bool isImpossible()
{
	bool bRet = false;
	int small, big;
	if (N < M)
	{
		small = N;
		big = M;
	}
	else
	{
		small = M;
		big = N;
	}
	if (!small)
	{
		if (K > 1)
			return true;
		else
			return false;
	}

	double cmp = (small + big) / factorial(small);
	for (int i = small + big - 1; i >= big + 1; i--)
	{
		cmp *= i;
		if (cmp > 1000000000)
			break;
	}

	return cmp < K ? true : false;
}

void inputAndInit()
{
	cin >> N >> M >> K;
	answer = "";
}

void solve()
{
	bool correct = false;
	if (impossible = isImpossible())
		return;

	dfs(N, M, K, correct);
}

void output()
{
	if (impossible)
		cout << "-1\n";
	else
		cout << answer << "\n";
}
