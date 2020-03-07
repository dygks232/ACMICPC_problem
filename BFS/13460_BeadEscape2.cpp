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
#include<string>
using namespace std;

#define WALL -1
#define BLANK 0
#define RED 1
#define BLUE 2
#define END 3

#define RESULT_ERROR -1

void inputAndInit();
void init();
void solve();
void output();

int BFS();
int encounterBlock(int nDir, int nCurrIndex, int& nEncounterIndex);
bool isImpossibleMove(int nDir, int nCurrRedIndex, int nCurrBlueIndex);

int nInputRowLen, nInputColLen;
int nMapSize, nEndIndex, nRedIndex, nBlueIndex;
int nOutputResult;

int nDirR[4] = { -1,0,1,0 };
int nDirC[4] = { 0,-1,0,1 };

vector<int> nVecMap;
vector<int> nVecMapClone;

vector<vector<bool> > bVecVecVisit;
vector<vector<int> > nVecVecMoveCount;

queue<pair<int, int> > nnQRedBlueIndex;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isImpossibleMove(int nDir, int nCurrRedIndex, int nCurrBlueIndex)
{
	bool bRet = true;
	int nEncounterIndexRed, nEncounterIndexBlue, nEncounterRedFlag, nEncounterBlueFlag;

	nEncounterRedFlag = encounterBlock(nDir, nCurrRedIndex, nEncounterIndexRed);
	nEncounterBlueFlag = encounterBlock(nDir, nCurrBlueIndex, nEncounterIndexBlue);

	if (nEncounterBlueFlag == END)
		return true;
	if (nEncounterRedFlag == END && nEncounterBlueFlag == RED)
		return true;

	if (nCurrRedIndex != nEncounterIndexRed || nCurrBlueIndex != nEncounterIndexBlue || nEncounterRedFlag == END)
		bRet = false;

	return bRet;
}

int encounterBlock(int nDir, int nCurrIndex, int& nEncounterIndex)
{
	int nRow, nCol, nNextIndex;
	nRow = nCurrIndex / nInputColLen;
	nCol = nCurrIndex % nInputColLen;

	do
	{
		nRow += nDirR[nDir];
		nCol += nDirC[nDir];
		nNextIndex = nRow * nInputColLen + nCol;
	} while (nVecMapClone[nNextIndex] == BLANK);

	nRow -= nDirR[nDir];
	nCol -= nDirC[nDir];
	nEncounterIndex = nRow * nInputColLen + nCol;

	return nVecMapClone[nNextIndex];
}

int BFS()
{
	int nCurrIndexR, nNextIndexR, nCurrIndexB, nNextIndexB;
	int nEncountFlagR, nEncountFlagB;
	nnQRedBlueIndex.push(make_pair(nRedIndex, nBlueIndex));
	bVecVecVisit[nRedIndex][nBlueIndex] = true;
	nVecVecMoveCount[nRedIndex][nBlueIndex] = 0;
	nCurrIndexR = nRedIndex;
	nCurrIndexB = nBlueIndex;

	while (!nnQRedBlueIndex.empty())
	{
		if (nVecVecMoveCount[nCurrIndexR][nCurrIndexB] == 10)
			return RESULT_ERROR;
		nVecMap[nCurrIndexR] = BLANK;
		nVecMap[nCurrIndexB] = BLANK;
		nCurrIndexR = nnQRedBlueIndex.front().first;
		nCurrIndexB = nnQRedBlueIndex.front().second;
		nVecMap[nCurrIndexR] = RED;
		nVecMap[nCurrIndexB] = BLUE;

		for (int dir = 0; dir < 4; dir++)
		{
			init();
			if (isImpossibleMove(dir, nCurrIndexR, nCurrIndexB))
				continue;

			nEncountFlagR = encounterBlock(dir, nCurrIndexR, nNextIndexR);
			if (nEncountFlagR == WALL)
			{
				nVecMapClone[nCurrIndexR] = BLANK;
				nVecMapClone[nNextIndexR] = RED;
				nEncountFlagB = encounterBlock(dir, nCurrIndexB, nNextIndexB);
				if (bVecVecVisit[nNextIndexR][nNextIndexB])
					continue;
				nnQRedBlueIndex.push(make_pair(nNextIndexR, nNextIndexB));
				bVecVecVisit[nNextIndexR][nNextIndexB] = true;
				nVecVecMoveCount[nNextIndexR][nNextIndexB] = nVecVecMoveCount[nCurrIndexR][nCurrIndexB] + 1;
			}
			else if (nEncountFlagR == BLUE)
			{
				nEncountFlagB = encounterBlock(dir, nCurrIndexB, nNextIndexB);
				nVecMapClone[nCurrIndexB] = BLANK;
				nVecMapClone[nNextIndexB] = BLUE;
				encounterBlock(dir, nCurrIndexR, nNextIndexR);
				if (bVecVecVisit[nNextIndexR][nNextIndexB])
					continue;
				nnQRedBlueIndex.push(make_pair(nNextIndexR, nNextIndexB));
				bVecVecVisit[nNextIndexR][nNextIndexB] = true;
				nVecVecMoveCount[nNextIndexR][nNextIndexB] = nVecVecMoveCount[nCurrIndexR][nCurrIndexB] + 1;
			}
			else // END
			{
				return nVecVecMoveCount[nCurrIndexR][nCurrIndexB] + 1;
			}
		}

		nnQRedBlueIndex.pop();
	}

	return RESULT_ERROR;
}

void init()
{
	nVecMapClone.assign(nVecMap.begin(), nVecMap.end());
}

void inputAndInit()
{
	string strInput;
	cin >> nInputRowLen >> nInputColLen;
	nMapSize = nInputRowLen * nInputColLen;
	nVecMap.assign(nMapSize, 0);
	bVecVecVisit.assign(nMapSize, vector<bool>(nMapSize, false));
	nVecVecMoveCount.assign(nMapSize, vector<int>(nMapSize, 0));
	for (int i = 0; i < nInputRowLen; i++)
	{
		cin >> strInput;
		for (int j = 0; j < nInputColLen; j++)
		{
			switch (strInput[j])
			{
			case '#':
				nVecMap[i * nInputColLen + j] = WALL;
				break;
			case 'O':
				nEndIndex = i * nInputColLen + j;
				nVecMap[nEndIndex] = END;
				break;
			case 'R':
				nRedIndex = i * nInputColLen + j;
				nVecMap[nRedIndex] = RED;
				break;
			case 'B':
				nBlueIndex = i * nInputColLen + j;
				nVecMap[nBlueIndex] = BLUE;
				break;
			}
		}
	}
}

void solve()
{
	nOutputResult = BFS();
}

void output()
{
	cout << nOutputResult << "\n";
}