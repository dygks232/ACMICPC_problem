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

#define DEADTREE INT_MAX

void inputAndInit();
void init();
void solve();
void output();

bool isOutOfBoundary(const int nRow, const int nCol);
bool isPossibleAbsorption(const int nAge, const int nNutrient);
bool isPossibleBreeding(const int nAge);
int calTreeNum();
void spring();
void summer();
void autumn();
void winter();

int nDirR[8] = { -1,-1,-1,0,0,1,1,1 };
int nDirC[8] = { -1,0,1,-1,1,-1,0,1 };

int nInputMapLen, nInputStartTreeNum, nInputResultYear;
int nMapSize;
int nOutputResult;

vector<int> nVecSupply;
vector<int> nVecNutrients;

vector<vector<int> > nVecVecTree;
vector<vector<int> > nVecVecDeadTree;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfBoundary(int nRow, int nCol)
{
	return nRow < 1 || nCol < 1 || nRow > nInputMapLen || nCol > nInputMapLen;
}

void inputAndInit()
{
	int nInput, nInputRow, nInputCol;
	cin >> nInputMapLen >> nInputStartTreeNum >> nInputResultYear;
	nMapSize = nInputMapLen * nInputMapLen;
	nVecSupply.assign(nMapSize, 0);
	nVecNutrients.assign(nMapSize, 5);
	nVecVecTree.assign(nMapSize, vector<int>());
	nVecVecDeadTree.assign(nMapSize, vector<int>());
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nInput;
		nVecSupply[i] = nInput;
	}
	for (int i = 0; i < nInputStartTreeNum; i++)
	{
		cin >> nInputRow >> nInputCol >> nInput;
		nVecVecTree[(nInputRow - 1) * nInputMapLen + nInputCol - 1].push_back(nInput);
	}
}

bool isPossibleAbsorption(const int nAge, const int nNutrient)
{
	return nNutrient >= nAge;
}

bool isPossibleBreeding(const int nAge)
{
	return nAge % 5 == 0;
}

void spring()
{
	for (int nIndex = 0; nIndex < nMapSize; nIndex++)
	{
		sort(nVecVecTree[nIndex].begin(), nVecVecTree[nIndex].end());
		for (int i = 0; i < nVecVecTree[nIndex].size(); i++)
		{
			if (isPossibleAbsorption(nVecVecTree[nIndex][i], nVecNutrients[nIndex]))
			{
				nVecNutrients[nIndex] -= nVecVecTree[nIndex][i];
				nVecVecTree[nIndex][i]++;
			}
			else
			{
				nVecVecDeadTree[nIndex].push_back(nVecVecTree[nIndex][i]);
				nVecVecTree[nIndex].erase(nVecVecTree[nIndex].begin() + i);
				i--;
			}
		}
	}
}

void summer()
{
	for (int nIndex = 0; nIndex < nMapSize; nIndex++)
	{
		for (int i = 0; i < nVecVecDeadTree[nIndex].size(); i++)
		{
			nVecNutrients[nIndex] += nVecVecDeadTree[nIndex][i] / 2;
		}
	}
}

void autumn()
{
	int nCurrRow, nCurrCol, nNextRow, nNextCol, nNextIndex;

	for (int nIndex = 0; nIndex < nMapSize; nIndex++)
	{
		nCurrRow = nIndex / nInputMapLen + 1;
		nCurrCol = nIndex % nInputMapLen + 1;
		for (int i = 0; i < nVecVecTree[nIndex].size(); i++)
		{
			if (isPossibleBreeding(nVecVecTree[nIndex][i]))
			{
				for (int dir = 0; dir < 8; dir++)
				{
					nNextRow = nCurrRow + nDirR[dir];
					nNextCol = nCurrCol + nDirC[dir];
					if (isOutOfBoundary(nNextRow, nNextCol)) continue;
					nNextIndex = (nNextRow - 1) * nInputMapLen + nNextCol - 1;

					nVecVecTree[nNextIndex].push_back(1);
				}
			}
		}
	}
}

void winter()
{
	for (int i = 0; i < nMapSize; i++)
	{
		nVecNutrients[i] += nVecSupply[i];
	}
}

int calTreeNum()
{
	int nRet = 0;
	for (int i = 0; i < nMapSize; i++)
	{
		nRet += nVecVecTree[i].size();
	}
	return nRet;
}

void init()
{
	for (int i = 0; i < nMapSize; i++)
		nVecVecDeadTree[i].clear();
}

void solve()
{
	while (nInputResultYear--)
	{
		init();
		spring();
		summer();
		autumn();
		winter();
	}
	nOutputResult = calTreeNum();
}

void output()
{
	cout << nOutputResult << "\n";
}