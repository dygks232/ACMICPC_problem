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

#define SPREAD_NORMAL 0
#define SPREAD_DUAL_RIGHT 1
#define SPREAD_DUAL_DOWN 2

#define RESULT_IMPOSSIBLE INT_MIN

void inputAndInit();
void solve();
void output();

bool isPossibleRightSpread(int nCol);
bool isPossibleDownSpread(int nRow);

int tetromino(int nCurrIndex, int nSpread, int nBlockNum);

int nInputBoardRow, nInputBoardCol;
int nBoardSize;
int nOutputResult;

vector<int> nVecBoard;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isPossibleRightSpread(int nCol)
{
	return nCol + 1 < nInputBoardCol;
}

bool isPossibleDownSpread(int nRow)
{
	return nRow + 1 < nInputBoardRow;
}

int tetromino(int nCurrIndex, int nSpread, int nBlockNum)
{
	int nDualValue = 0;
	if (nSpread == SPREAD_DUAL_RIGHT)
		nDualValue = nVecBoard[nCurrIndex + nInputBoardCol - 1];
	else if (nSpread == SPREAD_DUAL_DOWN)
		nDualValue = nVecBoard[nCurrIndex - nInputBoardCol + 1];

	if (nBlockNum == 4)
		return nVecBoard[nCurrIndex] + nDualValue;

	int nRet = RESULT_IMPOSSIBLE;

	int nCurrRow = nCurrIndex / nInputBoardCol;
	int nCurrCol = nCurrIndex % nInputBoardCol;
	int nDownIndex = nCurrIndex + nInputBoardCol;
	int nRightIndex = nCurrIndex + 1;

	bool bPossible1 = isPossibleRightSpread(nCurrCol);
	bool bPossible2 = isPossibleDownSpread(nCurrRow);

	if (bPossible1 && bPossible2)
	{
		nRet = max(nRet, nVecBoard[nCurrIndex] + nDualValue + tetromino(nRightIndex, SPREAD_NORMAL, nBlockNum + 1));
		nRet = max(nRet, nVecBoard[nCurrIndex] + nDualValue + tetromino(nDownIndex, SPREAD_NORMAL, nBlockNum + 1));
		if (nBlockNum <= 2)
		{
			nRet = max(nRet, nVecBoard[nCurrIndex] + nDualValue + tetromino(nRightIndex, SPREAD_DUAL_RIGHT, nBlockNum + 2));
			nRet = max(nRet, nVecBoard[nCurrIndex] + nDualValue + tetromino(nDownIndex, SPREAD_DUAL_DOWN, nBlockNum + 2));
		}
	}
	else if (bPossible1)
	{
		nRet = max(nRet, nVecBoard[nCurrIndex] + nDualValue + tetromino(nRightIndex, SPREAD_NORMAL, nBlockNum + 1));
	}
	else if (bPossible2)
	{
		nRet = max(nRet, nVecBoard[nCurrIndex] + nDualValue + tetromino(nDownIndex, SPREAD_NORMAL, nBlockNum + 1));
	}

	return nRet;
}

void inputAndInit()
{
	int nInput;
	nOutputResult = INT_MIN;
	cin >> nInputBoardRow >> nInputBoardCol;
	nBoardSize = nInputBoardRow * nInputBoardCol;
	nVecBoard.assign(nBoardSize, 0);
	for (int i = 0; i < nBoardSize; i++)
	{
		cin >> nInput;
		nVecBoard[i] = nInput;
	}
}

void solve()
{
	int nRow, nCol;

	for (int i = 0; i < nBoardSize; i++)
	{
		nOutputResult = max(nOutputResult, tetromino(i, SPREAD_NORMAL, 1));
	}

	// 3X2 크기이며, 좌측상단에 블럭이 없는 3가지 예외처리
	for (int i = 0; i < nBoardSize; i++)
	{
		nRow = i / nInputBoardCol;
		nCol = i % nInputBoardCol;
		if (nCol + 1 >= nInputBoardCol || nRow + 2 >= nInputBoardRow) continue;
		nOutputResult = max(nOutputResult, nVecBoard[i + 1] + nVecBoard[i + nInputBoardCol + 1] + nVecBoard[i + nInputBoardCol + nInputBoardCol] + nVecBoard[i + nInputBoardCol + nInputBoardCol + 1]);
		nOutputResult = max(nOutputResult, nVecBoard[i + 1] + nVecBoard[i + nInputBoardCol + 1] + nVecBoard[i + nInputBoardCol] + nVecBoard[i + nInputBoardCol + nInputBoardCol]);
		nOutputResult = max(nOutputResult, nVecBoard[i + 1] + nVecBoard[i + nInputBoardCol + 1] + nVecBoard[i + nInputBoardCol] + nVecBoard[i + nInputBoardCol + nInputBoardCol + 1]);
	}
	// 2X3 크기이며, 좌측상단에 블럭이 없는 3가지 예외처리
	for (int i = 0; i < nBoardSize; i++)
	{
		nRow = i / nInputBoardCol;
		nCol = i % nInputBoardCol;
		if (nCol + 2 >= nInputBoardCol || nRow + 1 >= nInputBoardRow) continue;
		nOutputResult = max(nOutputResult, nVecBoard[i + 2] + nVecBoard[i + nInputBoardCol] + nVecBoard[i + nInputBoardCol + 1] + nVecBoard[i + nInputBoardCol + 2]);
		nOutputResult = max(nOutputResult, nVecBoard[i + 1] + nVecBoard[i + nInputBoardCol] + nVecBoard[i + nInputBoardCol + 1] + nVecBoard[i + nInputBoardCol + 2]);
		nOutputResult = max(nOutputResult, nVecBoard[i + 1] + nVecBoard[i + nInputBoardCol] + nVecBoard[i + nInputBoardCol + 1] + nVecBoard[i + 2]);
	}
}

void output()
{
	cout << nOutputResult << "\n";
}