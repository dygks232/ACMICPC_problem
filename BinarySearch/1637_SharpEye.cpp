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

struct st {
	int start, end, K;
	st() { start = end = K = 0; }
	st(int s, int e, int k) { start = s; end = e; K = k; }
};

void inputAndInit();
void solve();
void output();

void binSearch(unsigned int start, unsigned int end);
int cntNum(int n);

int N, START, END, ans, ansNum;
bool isAnswer;

st input[20000];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int cntNum(int n)
{
	int ret = 0;                     
	for (int i = 0; i < N; i++)
	{
		if (input[i].start > n)
			continue;
		if (input[i].K != 1)
			ret += min((n - input[i].start) / input[i].K, (input[i].end - input[i].start) / input[i].K) + 1;
		else
			ret += (min(n, input[i].end) - input[i].start + 1);
 	}
	return ret;
}

void binSearch(unsigned int start, unsigned int end)
{
	if (start == end)
	{
		ansNum = cntNum(start);
		ans = start;
		if (ansNum & 1)
		{
			ansNum -= cntNum(start - 1);
			isAnswer = true;
		}
		return;
	}
	unsigned int mid = (start + end) / 2;
	if (cntNum(mid) & 1)
	{
		binSearch(start, mid);
	}
	else
	{
		binSearch(mid + 1, end);
	}
}

void inputAndInit()
{
	int s, e, k;
	//cin >> N;
	scanf("%d", &N);
	//input = vector<st>(N);
	START = INT_MAX;
	END = INT_MIN;
	isAnswer = false;
	ans = ansNum = 0;
	for (int i = 0; i < N; i++)
	{
		//cin >> s >> e >> k;
		scanf("%d %d %d", &s, &e, &k);
		input[i] = st(s, e, k);
		START = min(START, s);
		END = max(END, e);
	}
}

void solve()
{
	binSearch(START, END);
}

void output()
{
	if (isAnswer)
	{
		printf("%d %d\n", ans, ansNum);
	}
	else
		printf("NOTHING\n");
}
