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
void init();
void solve();
void output();
void solveAndOutput();

long long answer;
int N, T;

multiset<long long> input;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int a;
	long long b;
	//cin >> N >> T;
	scanf("%d %d", &N, &T);
	answer = 0;
	for (int i = 0; i < N; i++)
	{
		//cin >> a >> b;
		scanf("%d %lld", &a, &b);
		answer += a;
		input.insert(b);
	}
}

void solve()
{
	int i;
	multiset<long long>::reverse_iterator rit;
	for (i = T - 1, rit = input.rbegin(); i >= T - N; i--, rit++)
		answer += (*rit) * i;
}

void output()
{
	printf("%lld\n", answer);
}