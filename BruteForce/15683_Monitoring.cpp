// 2019/10/14 NYH
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

#define BLIND 0
#define WALL 6
#define NOT_BLIND 7

void inputAndInit();
void init();
void solve();
void output();

bool isImpossibleMonitoring(const int nRow, const int nCol);
void monitoring(int nIndex, int nCam, int nDir);
int calBlindNum();

int nDirR[4] = { -1,0,1,0 };
int nDirC[4] = { 0,-1,0,1 };

int nInputMapRow, nInputMapCol;
int nMapSize;
int nOutputResult;

vector<int> nVecMap;
vector<int> nVecMapClone;

vector<int> nVecCamNum;
vector<vector<int> > nVecVecCamIndex;
vector<int> nVecBitmaskFlag;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isImpossibleMonitoring(const int nRow, const int nCol)
{
	int nIndex = nRow * nInputMapCol + nCol;
	return nRow < 0 || nCol < 0 || nRow >= nInputMapRow || nCol >= nInputMapCol || nVecMapClone[nIndex] == WALL;
}

void monitoring(int nIndex, int nCam, int nDir)
{
	// nDir - 0:UP, 1:LEFT, 2:DOWN, 3:RIGHT
	int nCurrRow, nCurrCol, nNextRow, nNextCol, nNextIndex, nNextDir;
	nCurrRow = nIndex / nInputMapCol;
	nCurrCol = nIndex % nInputMapCol;

	if (nDir < 0 || nDir > 3) nDir = 0;

	nNextRow = nCurrRow + nDirR[nDir];
	nNextCol = nCurrCol + nDirC[nDir];
	while (!isImpossibleMonitoring(nNextRow, nNextCol))
	{
		nNextIndex = nNextRow * nInputMapCol + nNextCol;
		if (nVecMapClone[nNextIndex] == BLIND)
			nVecMapClone[nNextIndex] = NOT_BLIND;
		nNextRow += nDirR[nDir];
		nNextCol += nDirC[nDir];
	}

	if (nCam >= 3)
	{
		nNextDir = (nDir + 1) % 4;
		nNextRow = nCurrRow + nDirR[nNextDir];
		nNextCol = nCurrCol + nDirC[nNextDir];
		while (!isImpossibleMonitoring(nNextRow, nNextCol))
		{
			nNextIndex = nNextRow * nInputMapCol + nNextCol;
			if (nVecMapClone[nNextIndex] == BLIND)
				nVecMapClone[nNextIndex] = NOT_BLIND;
			nNextRow += nDirR[nNextDir];
			nNextCol += nDirC[nNextDir];
		}
	}
	if (nCam != 3 && nCam >= 2)
	{
		nNextDir = (nDir + 2) % 4;
		nNextRow = nCurrRow + nDirR[nNextDir];
		nNextCol = nCurrCol + nDirC[nNextDir];
		while (!isImpossibleMonitoring(nNextRow, nNextCol))
		{
			nNextIndex = nNextRow * nInputMapCol + nNextCol;
			if (nVecMapClone[nNextIndex] == BLIND)
				nVecMapClone[nNextIndex] = NOT_BLIND;
			nNextRow += nDirR[nNextDir];
			nNextCol += nDirC[nNextDir];
		}
	}
	if (nCam == 5)
	{
		nNextDir = (nDir + 3) % 4;
		nNextRow = nCurrRow + nDirR[nNextDir];
		nNextCol = nCurrCol + nDirC[nNextDir];
		while (!isImpossibleMonitoring(nNextRow, nNextCol))
		{
			nNextIndex = nNextRow * nInputMapCol + nNextCol;
			if (nVecMapClone[nNextIndex] == BLIND)
				nVecMapClone[nNextIndex] = NOT_BLIND;
			nNextRow += nDirR[nNextDir];
			nNextCol += nDirC[nNextDir];
		}
	}
}

int calBlindNum()
{
	int nRet = 0;
	for (int i = 0; i < nMapSize; i++)
	{
		if (nVecMapClone[i] == BLIND)
			nRet++;
	}
	return nRet;
}

void inputAndInit()
{
	int nInput;
	cin >> nInputMapRow >> nInputMapCol;
	nMapSize = nInputMapRow * nInputMapCol;
	nVecMap.assign(nMapSize, 0);
	nVecCamNum.assign(6, 0);
	nVecVecCamIndex.assign(6, vector<int>());
	nOutputResult = INT_MAX;
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nInput;
		nVecMap[i] = nInput;
		if (nInput > BLIND && nInput < WALL)
		{
			nVecCamNum[nInput]++;
			nVecVecCamIndex[nInput].push_back(i);
		}
	}

	nVecBitmaskFlag.assign(6, 2);
	nVecBitmaskFlag[2] = 1;
	nVecBitmaskFlag[5] = 0;
}

void init()
{
	nVecMapClone.assign(nVecMap.begin(), nVecMap.end());
}

void solve()
{
	int nIter = 1, nSub;
	unsigned int nCamDir;

	for (int i = 1; i < 5; i++)
	{
		if (i != 2)
			nIter = nIter << (nVecCamNum[i] * 2);
		else
			nIter = nIter << nVecCamNum[i];
	}

	// bitmask
	for (unsigned int i = 0; i < nIter; i++)
	{
		init();
		nSub = 0;

		for (int nCam = 1; nCam <= 5; nCam++)
		{
			for (int j = 0; j < nVecCamNum[nCam]; j++)
			{
				nCamDir = i;
				nCamDir = nCamDir << (32 - (nVecBitmaskFlag[nCam] + nSub));
				nCamDir = nCamDir >> (32 - nVecBitmaskFlag[nCam]);
				nSub += nVecBitmaskFlag[nCam];
				monitoring(nVecVecCamIndex[nCam][j], nCam, nCamDir);
			}
		}		

		nOutputResult = min(nOutputResult, calBlindNum());
	}
}

void output()
{
	cout << nOutputResult << "\n";
}