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

void inputAndInit();
void init();
void solve();
void output();

void dragonCurve(int nStartIndex, int nPreEndIndex, int nDir, int nCurrGen, int nDestGen);
int countAnswer();

struct curve
{
	int index;
	int dir;
	int gen;
	void input(int nIndex, int nDir, int nGen)
	{
		index = nIndex;
		dir = nDir;
		gen = nGen;
	}
};

int nDirR[4] = { 0,-1,0,1 };
int nDirC[4] = { 1,0,-1,0 };

int nInputCurveNum;
int nMapLen, nMapSize;
int nOutputResult;

vector<bool> bVecCurveVertex;
vector<curve> stVecCurve;

set<int> nSetCurveIndex;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int countAnswer()
{
	int nRet = 0;

	for (int i = 0; i < nMapSize - nMapLen; i++)
	{
		if (i % nMapLen == nMapLen - 1)
			continue;
		if (bVecCurveVertex[i] && bVecCurveVertex[i + 1] && bVecCurveVertex[i + nMapLen] && bVecCurveVertex[i + nMapLen + 1])
		{
			nRet++;
		}
	}

	return nRet;
}

void dragonCurve(int nStartIndex, int nPreEndIndex, int nDir, int nCurrGen, int nDestGen)
{
	int nStartRow, nStartCol, nEndRow, nEndCol, nDiffR, nDiffC, nNextRow, nNextCol, nNextIndex;
	set<int>::iterator setIter;

	if (nCurrGen == 0)
	{
		nStartRow = nStartIndex / nMapLen;
		nStartCol = nStartIndex % nMapLen;
		nEndRow = nStartRow + nDirR[nDir];
		nEndCol = nStartCol + nDirC[nDir];
		nNextIndex = nEndRow * nMapLen + nEndCol;
		nSetCurveIndex.insert(nStartIndex);
		nSetCurveIndex.insert(nNextIndex);
	}
	else
	{
		nEndRow = nPreEndIndex / nMapLen;
		nEndCol = nPreEndIndex % nMapLen;
		set<int> nSetNewCurveIndex;
		for (setIter = nSetCurveIndex.begin(); setIter != nSetCurveIndex.end(); setIter++)
		{
			if (*setIter == nPreEndIndex)
				continue;
			nStartRow = (*setIter) / nMapLen;
			nStartCol = (*setIter) % nMapLen;
			nDiffR = nEndRow - nStartRow;
			nDiffC = nEndCol - nStartCol;
			nNextRow = nEndRow - nDiffC;
			nNextCol = nEndCol + nDiffR;
			nNextIndex = nNextRow * nMapLen + nNextCol;
			nSetNewCurveIndex.insert(nNextIndex);
		}
		for (setIter = nSetNewCurveIndex.begin(); setIter != nSetNewCurveIndex.end(); setIter++)
		{
			nSetCurveIndex.insert(*setIter);
		}
		nSetNewCurveIndex.clear();

		nStartRow = nStartIndex / nMapLen;
		nStartCol = nStartIndex % nMapLen;
		nDiffR = nEndRow - nStartRow;
		nDiffC = nEndCol - nStartCol;
		nNextRow = nEndRow - nDiffC;
		nNextCol = nEndCol + nDiffR;
		nNextIndex = nNextRow * nMapLen + nNextCol;
	}

	if (nCurrGen == nDestGen)
	{
		for (setIter = nSetCurveIndex.begin(); setIter != nSetCurveIndex.end(); setIter++)
		{
			bVecCurveVertex[*setIter] = true;
		}
		nSetCurveIndex.clear();
		return;
	}
	else
		dragonCurve(nStartIndex, nNextIndex, nDir, nCurrGen + 1, nDestGen);

}

void inputAndInit()
{
	int nX, nY, nDir, nGen;
	curve stInput;
	nOutputResult = 0;
	nMapLen = 101;
	nMapSize = nMapLen * nMapLen;
	bVecCurveVertex.assign(nMapSize, false);

	cin >> nInputCurveNum;
	stVecCurve.assign(nInputCurveNum, curve());
	for (int i = 0; i < nInputCurveNum; i++)
	{
		cin >> nX >> nY >> nDir >> nGen;
		stInput.input(nY * nMapLen + nX, nDir, nGen);
		stVecCurve[i] = stInput;
	}
}

void init()
{
	nSetCurveIndex.clear();
}

void solve()
{
	for (int i = 0; i < nInputCurveNum; i++)
	{
		init();
		dragonCurve(stVecCurve[i].index, 0, stVecCurve[i].dir, 0, stVecCurve[i].gen);
	}
	nOutputResult = countAnswer();
}

void output()
{
	cout << nOutputResult << "\n";
}