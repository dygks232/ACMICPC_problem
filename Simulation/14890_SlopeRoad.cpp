// 2019/10/16 NYH
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

bool isAnswer(int nRoadIndex);
bool isPossibleSlope(bool bLeft, bool bRight, int nLeftIndex, int nRightIndex, int nRoadIndex, bool& isAlreadyVisit, bool& isBothSideHigh);

int nInputMapLen, nInputSlopeLen;
int nMapSize, nRoadNum;
int nOutputResult;

vector<vector<int> > nVecVecMap;

vector<bool> bVecVisit;
vector<int> nVecMinValue;
vector<int> nVecMaxValue;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isAnswer(int nRoadIndex)
{
	bool bRet = false, bAllSame = true, bPartSame, bOutOfLeftRange, bOutOfRightRange, isAlreadyVisit, isBothSideHigh;
	int nDiff, nLeftRange, nRightRange, nSameNum;
	int i, j;

	for (i = 0; i < nInputMapLen - 1; i++)
	{
		nDiff = abs(nVecVecMap[nRoadIndex][i] - nVecVecMap[nRoadIndex][i + 1]);
		
		if (nDiff)
		{
			bAllSame = false;
		}
		if (nDiff > 1)
			return false;
	}
	if (bAllSame)
		return true;

	for (int nValue = nVecMinValue[nRoadIndex]; nValue < nVecMaxValue[nRoadIndex]; nValue++)
	{
		for (i = 0; i < nInputMapLen; i++)
		{
			if (nVecVecMap[nRoadIndex][i] == nValue)
			{
				nSameNum = 0;
				for (j = i; j < nInputMapLen; j++)
				{
					if (nVecVecMap[nRoadIndex][j] != nValue)
						break;
					nSameNum++;
				}
				if (nSameNum < nInputSlopeLen)
					return false;
				i = j - 1;
			}
		}
	}

	for (i = 0; i < nInputMapLen - (nInputSlopeLen - 1); i++)
	{
		bPartSame = true;
		nLeftRange = i - 1;
		nRightRange = i + nInputSlopeLen;
		nLeftRange >= 0 ? bOutOfLeftRange = false : bOutOfLeftRange = true;
		nRightRange < nInputMapLen ? bOutOfRightRange = false : bOutOfRightRange = true;
		for (j = 0; j < nInputSlopeLen - 1; j++)
		{
			if (nVecVecMap[nRoadIndex][i + j] != nVecVecMap[nRoadIndex][i + j + 1])
			{
				bPartSame = false;
				break;
			}
		}

		if (bPartSame)
		{
			isAlreadyVisit = false;
			isBothSideHigh = false;
			if (isPossibleSlope(bOutOfLeftRange, bOutOfRightRange, nLeftRange, nRightRange, nRoadIndex, isAlreadyVisit, isBothSideHigh))
			{
				for (j = nLeftRange + 1; j < nRightRange; j++)
					bVecVisit[j] = true;
				bRet = true;
			}
			else if (isAlreadyVisit || isBothSideHigh)
				return false;

		}
	}

	return bRet;
}

bool isPossibleSlope(bool bLeft, bool bRight, int nLeftIndex, int nRightIndex, int nRoadIndex, bool &isAlreadyVisit, bool &isBothSideHigh)
{
	bool bRet = false;
	int nCurrIndex = nLeftIndex + 1;
	bool bVisit = false;

	for(int i = nCurrIndex; i < nRightIndex; i++)
		if (bVecVisit[i])
		{
			bVisit = true;
			break;
		}

	if (!bLeft && !bRight)
	{
		if (((nVecVecMap[nRoadIndex][nLeftIndex] == nVecVecMap[nRoadIndex][nCurrIndex] + 1 && (nVecVecMap[nRoadIndex][nRightIndex] == nVecVecMap[nRoadIndex][nCurrIndex] || nVecVecMap[nRoadIndex][nRightIndex] == nVecVecMap[nRoadIndex][nCurrIndex] - 1))
			|| (nVecVecMap[nRoadIndex][nRightIndex] == nVecVecMap[nRoadIndex][nCurrIndex] + 1 && (nVecVecMap[nRoadIndex][nLeftIndex] == nVecVecMap[nRoadIndex][nCurrIndex] || nVecVecMap[nRoadIndex][nLeftIndex] == nVecVecMap[nRoadIndex][nCurrIndex] - 1))))
		{
			if (!bVisit)
				return true;
			else
				isAlreadyVisit = true;
		}
		else if (nVecVecMap[nRoadIndex][nLeftIndex] == nVecVecMap[nRoadIndex][nCurrIndex] + 1 && nVecVecMap[nRoadIndex][nLeftIndex] == nVecVecMap[nRoadIndex][nCurrIndex] + 1)
			isBothSideHigh = true;
	}
	else if (!bLeft && bRight)
	{
		if (nVecVecMap[nRoadIndex][nLeftIndex] == nVecVecMap[nRoadIndex][nCurrIndex] + 1)
		{
			if (!bVisit)
				return true;
			else
				isAlreadyVisit = true;
		}
	}
	else if (bLeft && !bRight)
	{
		if (nVecVecMap[nRoadIndex][nRightIndex] == nVecVecMap[nRoadIndex][nCurrIndex] + 1)
		{
			if (!bVisit)
				return true;
			else
				isAlreadyVisit = true;
		}
	}

	return bRet;
}

void inputAndInit()
{
	int nInput, nMin, nMax;
	nOutputResult = 0;
	cin >> nInputMapLen >> nInputSlopeLen;
	nRoadNum = 2 * nInputMapLen;
	nVecVecMap.assign(nRoadNum, vector<int>(nInputMapLen, 0));
	nVecMinValue.assign(nRoadNum, 0);
	nVecMaxValue.assign(nRoadNum, 0);
	for (int i = 0; i < nInputMapLen; i++)
	{
		nMin = INT_MAX;
		nMax = INT_MIN;
		for (int j = 0; j < nInputMapLen; j++)
		{
			cin >> nInput;
			nMin = min(nMin, nInput);
			nMax = max(nMax, nInput);
			nVecVecMap[i][j] = nInput;
		}
		nVecMinValue[i] = nMin;
		nVecMaxValue[i] = nMax;
	}
	for (int i = nInputMapLen; i < nRoadNum; i++)
	{
		nMin = INT_MAX;
		nMax = INT_MIN;
		for (int j = 0; j < nInputMapLen; j++)
		{
			nMin = min(nMin, nVecVecMap[j][i - nInputMapLen]);
			nMax = max(nMax, nVecVecMap[j][i - nInputMapLen]);
			nVecVecMap[i][j] = nVecVecMap[j][i - nInputMapLen];
		}
		nVecMinValue[i] = nMin;
		nVecMaxValue[i] = nMax;
	}
}

void init()
{
	bVecVisit.assign(nInputMapLen, false);
}

void solve()
{
	for (int i = 0; i < nRoadNum; i++)
	{
		init();

		if (isAnswer(i))
			nOutputResult++;
	}
}

void output()
{
	cout << nOutputResult << "\n";
}