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
void init();
void solve();
void output();

bool isEnd();
bool isOutOfBoundary(int nRow, int nCol);
bool isUnion(int nIndex1, int nIndex2);
void makeUnion();

int nInputMapLen, nInputLeftBound, nInputRightBound;
int nMapSize;
int nOutputResult;

int nDirR[4] = { -1,0,1,0 };
int nDirC[4] = { 0,-1,0,1 };

vector<int> nVecMap;
vector<bool> bVecVisit;

vector<int> nVecUnionIndex;

queue<int> nQIndex;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfBoundary(int nRow, int nCol)
{
	return nRow < 0 || nCol < 0 || nRow >= nInputMapLen || nCol >= nInputMapLen;
}

bool isUnion(int nIndex1, int nIndex2)
{
	int nUnionValue = abs(nVecMap[nIndex1] - nVecMap[nIndex2]);
	return nUnionValue >= nInputLeftBound && nUnionValue <= nInputRightBound;
}

bool isEnd()
{
	int nRow, nCol, nDiffH, nDiffV;
	bool bRet = true;
	for (int i = 0; i < nMapSize; i++)
	{
		nRow = i / nInputMapLen;
		nCol = i % nInputMapLen;

		if (nCol < nInputMapLen - 1)
		{
			nDiffH = abs(nVecMap[i] - nVecMap[i + 1]);
			if (nDiffH >= nInputLeftBound && nDiffH <= nInputRightBound)
			{
				bRet = false;
				break;
			}
		}

		if (nRow < nInputMapLen - 1)
		{
			nDiffV = abs(nVecMap[i] - nVecMap[i + nInputMapLen]);
			if (nDiffV >= nInputLeftBound && nDiffV <= nInputRightBound)
			{
				bRet = false;
				break;
			}
		}
	}
	return bRet;
}

void inputAndInit()
{
	int nInput;
	nOutputResult = 0;
	cin >> nInputMapLen >> nInputLeftBound >> nInputRightBound;
	nMapSize = nInputMapLen * nInputMapLen;
	nVecMap.assign(nMapSize, 0);
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nInput;
		nVecMap[i] = nInput;
	}
}

void init()
{
	bVecVisit.clear();
	bVecVisit.assign(nMapSize, false);
}

void makeUnion()
{
	int nCurrRow, nCurrCol, nCurrIndex, nNextRow, nNextCol, nNextIndex;
	int nUnionSum, nUnionNum, nUnionValue;

	for (int nHeadIndex = 0; nHeadIndex < nMapSize; nHeadIndex++)
	{
		if (bVecVisit[nHeadIndex])
			continue;

		nVecUnionIndex.clear();
		nUnionSum = 0;

		nQIndex.push(nHeadIndex);
		bVecVisit[nHeadIndex] = true;

		nVecUnionIndex.push_back(nHeadIndex);
		nUnionSum += nVecMap[nHeadIndex];

		while (!nQIndex.empty())
		{
			nCurrIndex = nQIndex.front();
			nCurrRow = nCurrIndex / nInputMapLen;
			nCurrCol = nCurrIndex % nInputMapLen;
			for (int i = 0; i < 4; i++)
			{
				nNextRow = nCurrRow + nDirR[i];
				nNextCol = nCurrCol + nDirC[i];
				nNextIndex = nNextRow * nInputMapLen + nNextCol;
				if (isOutOfBoundary(nNextRow, nNextCol)) continue;
				if (bVecVisit[nNextIndex]) continue;
				if (!isUnion(nCurrIndex, nNextIndex)) continue;

				nQIndex.push(nNextIndex);
				bVecVisit[nNextIndex] = true;

				nVecUnionIndex.push_back(nNextIndex);
				nUnionSum += nVecMap[nNextIndex];
			}
			nQIndex.pop();
		}

		nUnionNum = nVecUnionIndex.size();
		nUnionValue = nUnionSum / nUnionNum;
		for (int i = 0; i < nUnionNum; i++)
		{
			nVecMap[nVecUnionIndex[i]] = nUnionValue;
		}
	}
}

void solve()
{
	while (!isEnd())
	{
		init();

		makeUnion();

		nOutputResult++;
	}
}

void output()
{
	cout << nOutputResult << "\n";
}