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

struct info {
	int index; // 몇번 후보
	int count; // 추천받은 수
	int time; // 등재 시간
	info(int i, int c, int t)
	{
		index = i;
		count = c;
		time = t;
	}
};

void apply(int rec);
bool cmp1(info a, info b);
bool cmp2(info a, info b);

int N, totalRec, candNum, time;

vector<int> recommend;
vector<info> candidate;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool cmp1(info a, info b)
{
	if (a.count < b.count)
		return true;
	else if (a.count == b.count && a.time < b.time)
		return true;
	return false;
}

bool cmp2(info a, info b)
{
	if (a.index < b.index)
		return true;
	return false;
}

void apply(int rec)
{
	for (int i = 0; i < candNum; i++)
	{
		if (candidate[i].index == rec)
		{
			candidate[i].count++;
			return;
		}
	}
	if (candNum == N)
	{
		// 1차-추천수 오름차순 2차-등재시간 오름차순 정렬
		sort(candidate.begin(), candidate.end(), cmp1);
		candidate[0] = info(rec, 1, time);
		time++;
	}
	else
	{
		candidate[candNum] = info(rec, 1, time);
		candNum++;
		time++;
	}
}

void inputAndInit()
{
	int in;
	cin >> N;
	candidate.assign(N, info(0, 0, 0));
	cin >> totalRec;
	recommend.assign(totalRec, 0);
	candNum = time = 0;
	for (int i = 0; i < totalRec; i++)
	{
		cin >> recommend[i];
	}
}

void solve()
{
	for (int i = 0; i < totalRec; i++)
	{
		apply(recommend[i]);
	}
}

void output()
{
	sort(candidate.begin(), candidate.begin() + candNum, cmp2);
	for (int i = 0; i < candNum; i++)
		cout << candidate[i].index << " ";
	cout << "\n";	
}