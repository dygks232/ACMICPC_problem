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

int nInputTestPlaceNum, nInputSupervisorAbility, nInputSemiAbility;
vector<int> nVecCandidateNum;
long long llOutputResult;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	cin >> nInputTestPlaceNum;
	nVecCandidateNum.assign(nInputTestPlaceNum, 0);
	for (int i = 0; i < nInputTestPlaceNum; i++)
		cin >> nVecCandidateNum[i];
	cin >> nInputSupervisorAbility >> nInputSemiAbility;
	llOutputResult = 0;
}

void solve()
{
	for (int i = 0; i < nInputTestPlaceNum; i++)
	{
		nVecCandidateNum[i] -= nInputSupervisorAbility;
		if (nVecCandidateNum[i] <= 0) {
			llOutputResult += 1;
			continue;
		}
		llOutputResult += (1 + (int)ceil(nVecCandidateNum[i] / (float)nInputSemiAbility));
	}
}

void output()
{
	cout << llOutputResult << "\n";
}