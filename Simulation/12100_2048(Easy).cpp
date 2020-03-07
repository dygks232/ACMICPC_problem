// 2019/10/17 NYH
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
#include<string>
using namespace std;

#define MOVE_MAX 5

#define BLANK 0

void inputAndInit();
void init();
void solve();
void output();

bool isOutOfRange(int nIndex);
bool isOutOfRange(int nRow, int nCol);
bool isStartBetweenEnd(int nIndex, int nStartIndex, int nEndIndex);
void moveBlock(int nDir, vector<int>& nVecClone);
void DFS(int nDir, int nMoveNum, vector<int> nVecOrg);
int maxNum(const vector<int>& nVecMapClone);

int nDirR[4] = { 1,0,-1,0 };
int nDirC[4] = { 0,-1,0,1 };

int nStartIndex[4];
int nEndIndex[4];

int nInputMapLen;
int nMapSize;
int nOutputResult;

vector<int> nVecMap;

vector<int> nVecCache;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isStartBetweenEnd(int nIndex, int nStartIndex, int nEndIndex)
{
	int nMin = min(nStartIndex, nEndIndex);
	int nMax = max(nStartIndex, nEndIndex);
	return nIndex >= nMin && nIndex <= nMax;
}

bool isOutOfRange(int nIndex)
{
	return nIndex < 0 || nIndex >= nMapSize;
}

bool isOutOfRange(int nRow, int nCol)
{
	return nRow < 0 || nCol < 0 || nRow >= nInputMapLen || nCol >= nInputMapLen;
}

int maxNum(const vector<int>& nVecMapClone)
{
	int nRet = INT_MIN;
	for (int i = 0; i < nMapSize; i++)
	{
		nRet = max(nRet, nVecMapClone[i]);
	}
	return nRet;
}

void DFS(int nDir, int nMoveNum, vector<int> nVecOrg)
{
	vector<int> nVecMapClone;
	nVecMapClone.assign(nVecOrg.begin(), nVecOrg.end());

	moveBlock(nDir, nVecMapClone);

	if (nMoveNum == MOVE_MAX)
	{
		nOutputResult = max(nOutputResult, maxNum(nVecMapClone));
		nVecMapClone.clear();
		return;
	}

	for (int dir = 0; dir < 4; dir++)
	{
		DFS(dir, nMoveNum + 1, nVecMapClone);
	}

	nVecMapClone.clear();
}

void moveBlock(int nDir, vector<int>& nVecClone)
{
	int nCurrIndex, nCurrRow, nCurrCol, nNextIndex, nNextRow, nNextCol, nWeight;
	int i, j, nMoveIndex;

	i = nStartIndex[nDir];
	nWeight = nDirR[nDir] * nInputMapLen + nDirC[nDir];
	while (isStartBetweenEnd(i, nStartIndex[nDir], nEndIndex[nDir]))
	{
		nMoveIndex = 0;
		init();

		nCurrRow = i / nInputMapLen;
		nCurrCol = i % nInputMapLen;
		while (!isOutOfRange(nCurrRow, nCurrCol))
		{
			j = nCurrRow * nInputMapLen + nCurrCol;
			if (nVecClone[j] == BLANK)
			{
				nCurrRow += nDirR[nDir];
				nCurrCol += nDirC[nDir];
				continue;
			}
			nCurrIndex = j;
			nNextRow = nCurrIndex / nInputMapLen;
			nNextCol = nCurrIndex % nInputMapLen;
			do
			{
				nNextRow += nDirR[nDir];
				nNextCol += nDirC[nDir];
				nNextIndex = nNextRow * nInputMapLen + nNextCol;
			} while (!isOutOfRange(nNextRow, nNextCol) && nVecClone[nNextIndex] == BLANK);

			if (!isOutOfRange(nNextRow, nNextCol))
			{
				if (nVecClone[nCurrIndex] == nVecClone[nNextIndex])
				{
					nVecCache[nMoveIndex++] = nVecClone[nCurrIndex] + nVecClone[nNextIndex];
					nCurrRow = nNextRow + nDirR[nDir];
					nCurrCol = nNextCol + nDirC[nDir];
				}
				else
				{
					nVecCache[nMoveIndex++] = nVecClone[nCurrIndex];
					nCurrRow = nNextRow;
					nCurrCol = nNextCol;
				}
			}
			else
			{
				nVecCache[nMoveIndex++] = nVecClone[nCurrIndex];
				break;
			}
		}

		for (j = 0; j < nInputMapLen; j++)
			nVecClone[i + j * nWeight] = nVecCache[j];

		nCurrRow = i / nInputMapLen;
		nCurrCol = i % nInputMapLen;
		nNextRow = nCurrRow + nDirR[(nDir + 3) % 4];
		nNextCol = nCurrCol + nDirC[(nDir + 3) % 4];
		i = nNextRow * nInputMapLen + nNextCol;
	}
}

void inputAndInit()
{
	int nInput;
	cin >> nInputMapLen;
	nOutputResult = 0;
	nMapSize = nInputMapLen * nInputMapLen;
	nVecMap.assign(nMapSize, 0);
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nInput;
		nVecMap[i] = nInput;
	}

	nStartIndex[0] = nEndIndex[3] = 0;
	nStartIndex[1] = nEndIndex[0] = nInputMapLen - 1;
	nStartIndex[2] = nEndIndex[1] = nMapSize - 1;
	nStartIndex[3] = nEndIndex[2] = nMapSize - nInputMapLen;
}

void init()
{
	nVecCache.clear();
	nVecCache.assign(nInputMapLen, 0);
}

void solve()
{
	for (int nDir = 0; nDir < 4; nDir++)
	{
		DFS(nDir, 1, nVecMap);
	}
}

void output()
{
	cout << nOutputResult << "\n";
}