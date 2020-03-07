#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<climits>
#include<stack>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<deque>
using namespace std;

#define NONE_TARGET -1

int distance(int nArcherIndex, int nEnemyIndex);
bool isExistEnemy();
void refreshBoard();
int targetIndex(int nArcherIndex);
void removeEnemy();

void inputAndInit();
void solve();
void output();

int nInputBoardRow, nInputBoardCol, nInputArrowRange, nBoardSize;
int nOutputResult, nTempResult;

vector<int> nVecBoard;
vector<int> nVecBoardClone;
vector<int> nVecPermuFlag;
set<int> nSetCurrTargetIndex;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int distance(int nArcherIndex, int nEnemyIndex)
{
	int nArcherRow = nArcherIndex / nInputBoardCol;
	int nArcherCol = nArcherIndex % nInputBoardCol;
	int nEnemyRow = nEnemyIndex / nInputBoardCol;
	int nEnemyCol = nEnemyIndex % nInputBoardCol;
	return abs(nEnemyRow - nArcherRow) + abs(nEnemyCol - nArcherCol);
}

bool isExistEnemy()
{
	bool bResult = false;
	for (int i = 0; i < nBoardSize; i++)
	{
		if (nVecBoardClone[i])
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}

void refreshBoard()
{
	for (int r = nInputBoardRow - 1; r > 0; r--)
	{
		for (int c = 0; c < nInputBoardCol; c++)
		{
			nVecBoardClone[r * nInputBoardCol + c] = nVecBoardClone[(r - 1) * nInputBoardCol + c];
		}
	}
	for (int i = 0; i < nInputBoardCol; i++)
	{
		nVecBoardClone[i] = 0;
	}
}

int targetIndex(int nArcherIndex)
{
	int nMostLeftCol = INT_MAX;
	int nCurrCol, nCurrDistance;
	int nMostIndex = NONE_TARGET, nNearestDistance = nInputArrowRange + 1;
	for (int nEnemySearchIndex = nBoardSize - 1; nEnemySearchIndex >= 0; nEnemySearchIndex--)
	{
		if (nVecBoardClone[nEnemySearchIndex])
		{
			nCurrDistance = distance(nArcherIndex, nEnemySearchIndex);
			if (nCurrDistance <= nNearestDistance && nCurrDistance <= nInputArrowRange) {
				nCurrCol = nEnemySearchIndex % nInputBoardCol;
				if (nCurrDistance < nNearestDistance) {
					nMostLeftCol = INT_MAX;
				}
				if (nMostLeftCol >= nCurrCol)
				{
					nMostLeftCol = nCurrCol;
					nNearestDistance = nCurrDistance;
					nMostIndex = nEnemySearchIndex;
				}
			}
		}
	}
	return nMostIndex;
}

void removeEnemy()
{
	set<int>::iterator iter;
	for (iter = nSetCurrTargetIndex.begin(); iter != nSetCurrTargetIndex.end(); iter++)
	{
		nVecBoardClone[*iter] = 0;
	}
}

void inputAndInit()
{
	int nInput;
	cin >> nInputBoardRow >> nInputBoardCol >> nInputArrowRange;
	nBoardSize = nInputBoardRow * nInputBoardCol;

	nVecPermuFlag.assign(nInputBoardCol, 1);
	for (int i = 0; i < 3; i++)
		nVecPermuFlag[i] = 0;
	for (int i = 0; i < nBoardSize; i++)
	{
		cin >> nInput;
		nVecBoard.push_back(nInput);
	}
}

void solve()
{
	int nCurrTargetIndex;

	nOutputResult = 0;

	do
	{
		nTempResult = 0;
		nVecBoardClone.assign(nVecBoard.begin(), nVecBoard.end());

		do
		{
			nSetCurrTargetIndex.clear();
			for (int i = 0; i < nInputBoardCol; i++)
			{
				if (!nVecPermuFlag[i] && (nCurrTargetIndex = targetIndex(i + nBoardSize)) != NONE_TARGET)
				{
					nSetCurrTargetIndex.insert(nCurrTargetIndex);
				}
			}
			nTempResult += nSetCurrTargetIndex.size();

			removeEnemy();
			refreshBoard();
		} while (isExistEnemy());
		nOutputResult = max(nOutputResult, nTempResult);

	} while (next_permutation(nVecPermuFlag.begin(), nVecPermuFlag.end()));
}

void output()
{
	cout << nOutputResult << "\n";
}