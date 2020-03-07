#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<climits>
#include<stack>
#include<queue>
#include<deque>
#include<vector>
#include<set>
#include<map>
using namespace std;

void inputAndInit();
void solve();
void output();

int DP(int nCurrDay);

int nInputDayNum;
int nOutputResult;
vector<int> nVecTime;
vector<int> nVecPrice;
int nArrCacheDP[20];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int DP(int nCurrDay)
{
	if (nCurrDay >= nInputDayNum)
		return 0;
	if (nCurrDay + nVecTime[nCurrDay] - 1 >= nInputDayNum)
		return DP(nCurrDay + 1);
	int& ret = nArrCacheDP[nCurrDay];
	if (ret != -1)
		return ret;

	ret = max(nVecPrice[nCurrDay] + DP(nCurrDay + nVecTime[nCurrDay]), DP(nCurrDay + 1));

	return ret;
}

void inputAndInit()
{
	int nTime, nPrice;
	cin >> nInputDayNum;
	nVecTime.assign(nInputDayNum, 0);
	nVecPrice.assign(nInputDayNum, 0);
	for (int i = 0; i < nInputDayNum; i++)
	{
		cin >> nTime >> nPrice;
		nVecTime[i] = nTime;
		nVecPrice[i] = nPrice;
	}
	nOutputResult = 0;
	for (int i = 0; i < 20; i++)
		nArrCacheDP[i] = -1;
}

void solve()
{
	nOutputResult = DP(0);
}

void output()
{
	cout << nOutputResult << "\n";
}