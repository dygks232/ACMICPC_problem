// 2019/10/15 NYH
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

#define CLEANER_VALUE -1

void inputAndInit();
void init();
void solve();
void output();

bool isOutOfRange(int nRow, int nCol);
void dustSpread();
void cleaner();
int calDustNum();

int nDirR[4] = { -1,0,1,0 };
int nDirC[4] = { 0,-1,0,1 };

int nInputMapRow, nInputMapCol, nInputTime;
int nMapSize, nUpCleanerIndex, nUpCleanerRow, nDownCleanerIndex, nDownCleanerRow;
int nOutputResult;

vector<int> nVecMap;
vector<int> nVecMapClone;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfRange(int nRow, int nCol)
{
	return nRow < 0 || nCol < 0 || nRow >= nInputMapRow || nCol >= nInputMapCol || (!nCol && (nRow == nUpCleanerRow || nRow == nDownCleanerRow));
}

int calDustNum()
{
	int nRet = 0;

	for (int i = 0; i < nMapSize; i++)
	{
		if (nVecMap[i] == CLEANER_VALUE || !nVecMap[i])
			continue;
		nRet += nVecMap[i];
	}

	return nRet;
}

void inputAndInit()
{
	int nInput;
	bool bCheck = false;
	cin >> nInputMapRow >> nInputMapCol >> nInputTime;
	nMapSize = nInputMapRow * nInputMapCol;
	nVecMap.assign(nMapSize, 0);
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nInput;
		nVecMap[i] = nInput;
		if (nInput == CLEANER_VALUE)
		{
			if (!bCheck)
			{
				nUpCleanerIndex = i;
				nUpCleanerRow = i / nInputMapCol;
				bCheck = true;
			}
			else
			{
				nDownCleanerIndex = i;
				nDownCleanerRow = i / nInputMapCol;
			}
		}
	}
}

void dustSpread()
{
	int nCurrRow, nCurrCol, nNextRow, nNextCol, nNextIndex, nSpreadNum, nCurrDust;
	for (int i = 0; i < nMapSize; i++)
	{
		if (nVecMap[i] <= 0)
			continue;
		nCurrRow = i / nInputMapCol;
		nCurrCol = i % nInputMapCol;
		nSpreadNum = 0;
		nCurrDust = nVecMap[i];

		for (int nDir = 0; nDir < 4; nDir++)
		{
			nNextRow = nCurrRow + nDirR[nDir];
			nNextCol = nCurrCol + nDirC[nDir];
			if (isOutOfRange(nNextRow, nNextCol))
				continue;
			nNextIndex = nNextRow * nInputMapCol + nNextCol;
			nSpreadNum++;
			nVecMapClone[nNextIndex] += nCurrDust / 5;
		}

		nVecMapClone[i] += nVecMap[i] - nSpreadNum * (int)(nCurrDust / 5);
	}
	nVecMap.assign(nVecMapClone.begin(), nVecMapClone.end());
}

void cleaner()
{
	int nCurrIndex, nNextIndex;
	for (int nRow = nUpCleanerRow - 2; nRow >= 0; nRow--)
	{
		nCurrIndex = nRow * nInputMapCol;
		nNextIndex = (nRow + 1) * nInputMapCol;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}
	for (int nCol = 1; nCol < nInputMapCol; nCol++)
	{
		nCurrIndex = nCol;
		nNextIndex = nCol - 1;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}
	for (int nRow = 1; nRow <= nUpCleanerRow; nRow++)
	{
		nCurrIndex = nRow * nInputMapCol + nInputMapCol - 1;
		nNextIndex = (nRow - 1) * nInputMapCol + nInputMapCol - 1;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}
	for (int nCol = nInputMapCol - 2; nCol > 0; nCol--)
	{
		nCurrIndex = nUpCleanerRow * nInputMapCol + nCol;
		nNextIndex = nUpCleanerRow * nInputMapCol + nCol + 1;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}

	for (int nRow = nDownCleanerRow + 2; nRow < nInputMapRow; nRow++)
	{
		nCurrIndex = nRow * nInputMapCol;
		nNextIndex = (nRow - 1) * nInputMapCol;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}
	for (int nCol = 1; nCol < nInputMapCol; nCol++)
	{
		nCurrIndex = (nInputMapRow - 1) * nInputMapCol + nCol;
		nNextIndex = (nInputMapRow - 1) * nInputMapCol + nCol - 1;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}
	for (int nRow = nInputMapRow - 2; nRow >= nDownCleanerRow; nRow--)
	{
		nCurrIndex = nRow * nInputMapCol + nInputMapCol - 1;
		nNextIndex = (nRow + 1) * nInputMapCol + nInputMapCol - 1;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}
	for (int nCol = nInputMapCol - 2; nCol > 0; nCol--)
	{
		nCurrIndex = nDownCleanerRow * nInputMapCol + nCol;
		nNextIndex = nDownCleanerRow * nInputMapCol + nCol + 1;
		nVecMap[nNextIndex] = nVecMap[nCurrIndex];
	}

	nVecMap[nUpCleanerIndex + 1] = 0;
	nVecMap[nDownCleanerIndex + 1] = 0;
}

void init()
{
	nVecMapClone.assign(nMapSize, 0);
}

void solve()
{
	while (nInputTime--)
	{
		init();
		dustSpread();
		cleaner();
	}
	nOutputResult = calDustNum();
}

void output()
{
	cout << nOutputResult << "\n";
}