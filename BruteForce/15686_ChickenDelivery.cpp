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

int nInputLen, nInputPick;

vector<int> nVecMapOrigin;
vector<int> nVecMapClone;

vector<int> nVecChickenIndex;
vector<int> nVecHomeIndex;

vector<int> nVecPermuFlag;

int chickenDist(int homeIndex, int chickenIndex)
{
	int nHomeRow = homeIndex / nInputLen;
	int nHomeCol = homeIndex % nInputLen;
	int nChikenRow = chickenIndex / nInputLen;
	int nChickenCol = chickenIndex % nInputLen;

	return abs(nHomeRow - nChikenRow) + abs(nHomeCol - nChickenCol);
}

int main()
{
	int nTemp, nSize, nHomeNum, nChickenNum, nResult, nTempResult, nOneChickenDist;
	cin >> nInputLen >> nInputPick;
	nSize = nInputLen * nInputLen;
	for (int i = 0; i < nSize; i++)
	{
		cin >> nTemp;
		nVecMapOrigin.push_back(nTemp);
		if (nTemp == 2)
			nVecChickenIndex.push_back(i);
		else if (nTemp == 1)
			nVecHomeIndex.push_back(i);
	}

	nResult = INT_MAX;
	nHomeNum = nVecHomeIndex.size();
	nChickenNum = nVecChickenIndex.size();
	nVecPermuFlag.assign(nChickenNum, 1);
	for (int i = 0; i < nInputPick; i++)
		nVecPermuFlag[i] = 0;

	do {
		nTempResult = 0;
		for (int i = 0; i < nHomeNum; i++)
		{
			nOneChickenDist = INT_MAX;
			for (int j = 0; j < nVecPermuFlag.size(); j++)
			{
				if (nVecPermuFlag[j] == 0)
				{
					nOneChickenDist = min(nOneChickenDist, chickenDist(nVecHomeIndex[i], nVecChickenIndex[j]));
				}
			}
			nTempResult += nOneChickenDist;
		}

		nResult = min(nResult, nTempResult);

	} while (next_permutation(nVecPermuFlag.begin(), nVecPermuFlag.end()));

	cout << nResult << endl;
	return 0;
}