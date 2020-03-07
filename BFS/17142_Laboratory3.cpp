#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<cmath>
#include<climits>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

#define WALL INT_MIN
#define START 0
#define NOT_ACT INT_MAX

void inputAndInitialize();
void solve();
void virus(int nCurIndex, int nCurTime);
void output();

int nInputLen, nInputActVirusNum, nResult, nTempResult;
int nDelta[4];
int nDeltaR[4] = { 0,-1,0,1 };
int nDeltaC[4] = { -1,0,1,0 };

set<int> nSetVirusIndex;
vector<int> nVecVirusIndex;
vector<int> nVecPermuFlag;

vector<int> nVecTimeOrigin;
vector<int> nVecTimeClone;

map<int, int> nnMapSpreadIndex;
map<int, int> nnMapSpreadIndexClone;
map<int, int>::iterator iterMapSpreadIndex;

int main()
{
	inputAndInitialize();
	solve();
	output();

	return 0;
}

void inputAndInitialize()
{
	int nTemp, nSize;

	scanf("%d", &nInputLen);
	scanf("%d", &nInputActVirusNum);
	nSize = nInputLen * nInputLen;
	nResult = INT_MAX;
	nDelta[0] = -1;		nDelta[1] = -nInputLen;
	nDelta[2] = 1;		nDelta[3] = nInputLen;

	for (int i = 0; i < nSize; i++) {
		scanf("%d", &nTemp);
		if (!nTemp)
		{
			nVecTimeOrigin.push_back(NOT_ACT);
		}
		else if (nTemp == 2)
		{
			nVecVirusIndex.push_back(i);
			nVecTimeOrigin.push_back(NOT_ACT);
			nSetVirusIndex.insert(i);
		}
		else
			nVecTimeOrigin.push_back(WALL);
	}

	nVecPermuFlag.assign(nVecVirusIndex.size(), 1);
	for (int i = 0; i < nInputActVirusNum; i++)
		nVecPermuFlag[i] = 0;
}

void solve()
{
	int nVirusNum = nVecVirusIndex.size(),
		nSize = nInputLen * nInputLen,
		nTime;

	do {
		nTime = 0;
		nTempResult = 0;

		nVecTimeClone.assign(nVecTimeOrigin.begin(), nVecTimeOrigin.end());
		nnMapSpreadIndex.clear();

		for (int i = 0; i < nVirusNum; i++)
		{
			if (!nVecPermuFlag[i])
			{
				nVecTimeClone[nVecVirusIndex[i]] = START;
				nnMapSpreadIndex.insert(make_pair(nVecVirusIndex[i], nTime));
			}
		}

		while (!nnMapSpreadIndex.empty())
		{
			for (iterMapSpreadIndex = nnMapSpreadIndex.begin(); iterMapSpreadIndex != nnMapSpreadIndex.end(); iterMapSpreadIndex++)
			{
				virus(iterMapSpreadIndex->first, iterMapSpreadIndex->second);
			}
			nnMapSpreadIndex = nnMapSpreadIndexClone;
			nnMapSpreadIndexClone.clear();
			++nTime;
		}

		for (int j = 0; j < nSize; j++)
		{
			if (nSetVirusIndex.find(j) != nSetVirusIndex.end())
				continue;
			if (nVecTimeClone[j] == NOT_ACT)
			{
				nTempResult = INT_MAX;
				break;
			}
			else
			{
				nTempResult = max(nTempResult, nVecTimeClone[j]);
			}
		}

		nResult = min(nResult, nTempResult);

	} while (next_permutation(nVecPermuFlag.begin(), nVecPermuFlag.end()));
}

void virus(int nCurIndex, int nCurTime)
{
	int nNextTime = nCurTime + 1;
	int newIndex, newRow, newCol, curRow, curCol;

	for (int i = 0; i < 4; i++)
	{
		curRow = nCurIndex / nInputLen;
		curCol = nCurIndex % nInputLen;
		newRow = curRow + nDeltaR[i];
		newCol = curCol + nDeltaC[i];
		if (newRow < 0 || newRow >= nInputLen) continue;
		if (newCol < 0 || newCol >= nInputLen) continue;

		newIndex = nCurIndex + nDelta[i];
		if (nVecTimeClone[newIndex] == NOT_ACT || nVecTimeClone[newIndex] > nNextTime)
		{
			nVecTimeClone[newIndex] = nNextTime;
			nnMapSpreadIndexClone.insert(make_pair(newIndex, nNextTime));
		}
	}
}

void output()
{
	if (nResult != INT_MAX) printf("%d\n", nResult);
	else printf("-1\n");
}