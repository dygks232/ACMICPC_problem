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
pair<int, int> calTeamStatus();

int nInputPeopleNum, nSynergySize, nTeamSize;
int nOutputResult;
vector<int> nVecSynergy;
vector<int> nVecPermuFlag;
vector<int> nVecTeam1Index;
vector<int> nVecTeam2Index;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int nInput;
	nOutputResult = INT_MAX;
	cin >> nInputPeopleNum;
	nTeamSize = nInputPeopleNum / 2;
	nSynergySize = nInputPeopleNum * nInputPeopleNum;
	nVecSynergy.assign(nSynergySize, 0);
	for (int i = 0; i < nSynergySize; i++)
	{
		cin >> nInput;
		nVecSynergy[i] = nInput;
	}

	nVecPermuFlag.assign(nInputPeopleNum, 1);
	for (int i = 0; i < nTeamSize; i++)
		nVecPermuFlag[i] = 0;
}

pair<int, int> calTeamStatus()
{
	int nTeam1 = 0, nTeam2 = 0;
	int nSynergyIndex;
	nVecTeam1Index.clear();
	nVecTeam2Index.clear();
	for (int i = 0; i < nInputPeopleNum; i++)
	{
		if (nVecPermuFlag[i] == 0)
			nVecTeam1Index.push_back(i);
		else
			nVecTeam2Index.push_back(i);
	}

	for (int i = 0; i < nTeamSize; i++)
	{
		for (int j = 0; j < nTeamSize; j++)
		{
			if (i == j)
				continue;
			nSynergyIndex = nVecTeam1Index[i] * nInputPeopleNum + nVecTeam1Index[j];
			nTeam1 += nVecSynergy[nSynergyIndex];
			nSynergyIndex = nVecTeam2Index[i] * nInputPeopleNum + nVecTeam2Index[j];
			nTeam2 += nVecSynergy[nSynergyIndex];
		}
	}

	return make_pair(nTeam1, nTeam2);
}

void solve()
{
	pair<int, int> nnPairTemp;
	do
	{
		nnPairTemp = calTeamStatus();
		nOutputResult = min(nOutputResult, abs(nnPairTemp.first - nnPairTemp.second));
	} while (next_permutation(nVecPermuFlag.begin(), nVecPermuFlag.end()));
}

void output()
{
	cout << nOutputResult << "\n";
}