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

#define RESULT_ERROR -1

void inputAndInit();
void init();
void solve();
void output();

void SWAP(int &a, int &b);
bool isAnswer(const int nAddHLineNum);
bool isWrongLine(const int nIndex);
bool isSame();
void ladderGame();

int nInputVLineNum, nInputHLineNum, nInputRow;
int nLineAreaNum;
int nOutputResult;

vector<int> nVecHLineInfo;
vector<int> nVecHLineClone;

vector<int> nVecStartIndex;
vector<int> nVecEndIndex;

vector<int> nVecPermuFlag;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void SWAP(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

bool isWrongLine(const int nIndex)
{
	int nCurrHLineNum = nVecHLineClone.size();
	int nCompareRow, nCompareCol, nCurrRow, nCurrCol;

	nCurrRow = nIndex / (nInputVLineNum - 1);
	nCurrCol = nIndex % (nInputVLineNum - 1);

	for (int i = 0; i < nCurrHLineNum; i++)
	{
		nCompareRow = nVecHLineClone[i] / (nInputVLineNum - 1);
		nCompareCol = nVecHLineClone[i] % (nInputVLineNum - 1);
		if (nCurrRow == nCompareRow && abs(nCurrCol - nCompareCol) <= 1)
		{
			return true;
		}
	}

	nVecHLineClone.push_back(nIndex);
	return false;
}

bool isSame()
{
	bool bRet = true;
	for (int i = 0; i < nInputVLineNum; i++)
	{
		if (nVecStartIndex[i] != nVecEndIndex[i])
		{
			bRet = false;
			break;
		}
	}
	return bRet;
}

void ladderGame()
{
	int nCurrHLineNum = nVecHLineClone.size();
	int nCurrRow, nCurrCol, nCompareRow;

	for (int i = 0; i < nCurrHLineNum; i++)
	{
		nCurrRow = nVecHLineClone[i] / (nInputVLineNum - 1);
		for (int j = i + 1; j < nCurrHLineNum; j++)
		{
			nCompareRow = nVecHLineClone[j] / (nInputVLineNum - 1);
			if (nCurrRow > nCompareRow)
			{
				SWAP(nVecHLineClone[i], nVecHLineClone[j]);
				nCurrRow = nCompareRow;
			}
		}
	}

	for (int i = 0; i < nCurrHLineNum; i++)
	{
		nCurrCol = nVecHLineClone[i] % (nInputVLineNum - 1);
		SWAP(nVecEndIndex[nCurrCol], nVecEndIndex[nCurrCol + 1]);
	}

}

bool isAnswer(const int nAddHLineNum)
{
	bool bRet = false;
	bool isWrong;

	for (int i = 0; i < nAddHLineNum; i++)
		nVecPermuFlag[i] = 0;

	do
	{
		init();
		isWrong = false;

		for (int i = 0; i < nLineAreaNum; i++)
		{
			if (!nVecPermuFlag[i])
			{
				if (isWrongLine(i))
				{
					isWrong = true;
					break;
				}
			}
		}
		if (isWrong)
			continue;

		ladderGame();

		if (isSame())
		{
			bRet = true;
			break;
		}

	} while (next_permutation(nVecPermuFlag.begin(), nVecPermuFlag.end()));
	
	return bRet;
}

void inputAndInit()
{
	int nInputRowValue, nInputColValue;
	nOutputResult = RESULT_ERROR;
	cin >> nInputVLineNum >> nInputHLineNum >> nInputRow;
	nLineAreaNum = (nInputVLineNum - 1) * nInputRow;
	nVecHLineInfo.assign(nInputHLineNum, 0);
	for (int i = 0; i < nInputHLineNum; i++)
	{
		cin >> nInputRowValue >> nInputColValue;
		nVecHLineInfo[i] = (nInputRowValue - 1) * (nInputVLineNum - 1) + nInputColValue - 1;
	}
	nVecStartIndex.assign(nInputVLineNum, 0);
	for (int i = 0; i < nInputVLineNum; i++)
		nVecStartIndex[i] = i;
}

void init()
{
	nVecEndIndex.assign(nVecStartIndex.begin(), nVecStartIndex.end());
	nVecHLineClone.assign(nVecHLineInfo.begin(), nVecHLineInfo.end());
}

void solve()
{
	for (int i = 0; i <= 3; i++)
	{
		nVecPermuFlag.assign(nLineAreaNum, 1);
		if (isAnswer(i))
		{
			nOutputResult = i;
			break;
		}
	}
}

void output()
{
	cout << nOutputResult << "\n";
}