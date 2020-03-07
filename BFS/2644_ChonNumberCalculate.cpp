#include<iostream>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<map>
#include<set>
#include<deque>
#include<climits>
using namespace std;

void input();
void solve();
void output();

int nInputPeopleNum, nInputResultPerson1, nInputResultPerson2, nInputRelationNum;

vector<int> nVecChon;
vector<pair<int, int> > nnVecRelation;
vector<bool> bVecRelationVisit;
queue<int> Q;

int main()
{
	input();
	solve();
	output();
	//system("pause");
	return 0;
}

void input()
{
	int nInputFather, nInputChild;
	cin >> nInputPeopleNum;
	nVecChon.assign(nInputPeopleNum, 0);
	cin >> nInputResultPerson1 >> nInputResultPerson2;
	cin >> nInputRelationNum;
	bVecRelationVisit.assign(nInputRelationNum, false);
	for (int i = 0; i < nInputRelationNum; i++)
	{
		cin >> nInputFather >> nInputChild;
		nnVecRelation.push_back(make_pair(nInputFather, nInputChild));
	}
}

void solve()
{
	int nNowChonCalculation = nInputResultPerson1;
	int nChonNum = 1;
	Q.push(nNowChonCalculation);
	while (!Q.empty()) {
		nNowChonCalculation = Q.front();
		for (int i = 0; i < nInputRelationNum; i++)
		{
			if (bVecRelationVisit[i]) continue;
			if (nnVecRelation[i].first == nNowChonCalculation)
			{
				Q.push(nnVecRelation[i].second);
				nVecChon[nnVecRelation[i].second - 1] = nVecChon[nNowChonCalculation - 1] + 1;
				bVecRelationVisit[i] = true;
			}
			if (nnVecRelation[i].second == nNowChonCalculation)
			{
				Q.push(nnVecRelation[i].first);
				nVecChon[nnVecRelation[i].first - 1] = nVecChon[nNowChonCalculation - 1] + 1;
				bVecRelationVisit[i] = true;
			}
		}
		Q.pop();
		nChonNum++;
	}
}

void output()
{
	int nOutputResult = nVecChon[nInputResultPerson2 - 1];
	if (nOutputResult > 0) cout << nOutputResult << "\n";
	else cout << "-1\n";
}
