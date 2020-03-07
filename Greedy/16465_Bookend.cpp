#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<deque>
#include<vector>
#include<set>
#include<map>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<climits>
#include<functional>
using namespace std;

void inputAndInit();
void solve();
void output();

int answer, N, M, L, sum;

vector<int> X;

int main()
{
	inputAndInit();
	solve();
	output();
	//system("pause");
	return 0;
}

void inputAndInit()
{
	cin >> N >> M >> L;
	X = vector<int>(N);
	answer = 0;
	sum = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> X[i];
		sum += X[i];
	}
}

void solve()
{
	if (L > sum)
	{
		if (sum == M) answer = 0;
		else answer = -1;
	}
	else if (L == sum)
	{
		if (M < L) answer = -1;
		else if (M == L) answer = 0;
		else answer = 1;
	}
	else
	{
		if (sum > M) answer = -1;
		else if (sum == M) answer = 0;
		else answer = 1;
	}
	if (answer == -1)
		if (sum + L <= M) answer = 1;
}

void output()
{
	printf("%d\n", answer);
}
