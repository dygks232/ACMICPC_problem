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

bool canGrowth();
bool isExistFood();
bool searchFood();
void eatFood(int nFoodIndex);
bool isOutOfRange(int nRow, int nCol);
bool isFoundInMinDist(int nPreDist, int nCurrDist);

int nDirR[4] = { -1,0,0,1 };
int nDirC[4] = { 0,-1,1,0 };

int nInputMapLen;
int nMapSize, nSharkSize, nSharkEatNum, nSharkIndex;
int nOutputResult;

vector<int> nVecMap;
vector<bool> bVecVisit;
vector<int> nVecSharkNum;

vector<int> nVecFood;

vector<set<int> > nSetVecIndexOfSameDist;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfRange(int nRow, int nCol)
{
	return nRow < 0 || nCol < 0 || nRow >= nInputMapLen || nCol >= nInputMapLen;
}

bool canGrowth()
{
	return nSharkSize == nSharkEatNum;
}

bool isExistFood()
{
	bool bRet = false;
	int nRange = min(nSharkSize, 7);

	for (int i = 1; i < nRange; i++)
	{
		if (nVecSharkNum[i])
		{
			bRet = true;
			break;
		}
	}

	return bRet;
}

void inputAndInit()
{
	int nInput;
	nSharkSize = 2;
	nSharkEatNum = 0;
	nOutputResult = 0;
	cin >> nInputMapLen;
	nMapSize = nInputMapLen * nInputMapLen;
	nVecMap.assign(nMapSize, 0);
	nVecSharkNum.assign(7, 0);
	nSetVecIndexOfSameDist.assign(nMapSize + 1, set<int>());
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nInput;
		nVecMap[i] = nInput;
		if (nInput)
		{
			if (nInput != 9)
				nVecSharkNum[nInput]++;
			else
			{
				nSharkIndex = i;
				nVecMap[i] = 0;
			}
		}
	}
}

bool isFoundInMinDist(int nPreDist, int nCurrDist)
{
	return nPreDist != nCurrDist && nVecFood.size() > 0;
}

bool searchFood()
{
	queue<int> nQIndex;
	set<int>::iterator nSetIter;
	int nCurrIndex, nCurrRow, nCurrCol, nNextRow, nNextCol, nNextIndex;
	int nCurrDist = 0, nNextDist;
	bool bFindFood = false;

	nQIndex.push(nSharkIndex);
	nSetVecIndexOfSameDist[nCurrDist].insert(nSharkIndex);
	bVecVisit[nSharkIndex] = true;

	while (!nQIndex.empty())
	{
		nCurrIndex = nQIndex.front();
		nCurrRow = nCurrIndex / nInputMapLen;
		nCurrCol = nCurrIndex % nInputMapLen;

		for (int i = nCurrDist; i < nMapSize + 1; i++)
		{
			if (nSetVecIndexOfSameDist[i].find(nCurrIndex) != nSetVecIndexOfSameDist[i].end())
			{
				if (isFoundInMinDist(nCurrDist,i))
				{
					bFindFood = true;
					nCurrDist = i;
					break;
				}
				nCurrDist = i;
				nNextDist = i + 1;
				break;
			}
		}

		if (bFindFood)
		{
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nCurrRow + nDirR[i];
			nNextCol = nCurrCol + nDirC[i];
			if (isOutOfRange(nNextRow, nNextCol))
				continue;
			nNextIndex = nNextRow * nInputMapLen + nNextCol;
			if (bVecVisit[nNextIndex])
				continue;
			if (nVecMap[nNextIndex] > nSharkSize)
				continue;

			nSetVecIndexOfSameDist[nNextDist].insert(nNextIndex);
			nQIndex.push(nNextIndex);
			bVecVisit[nNextIndex] = true;

			if (nVecMap[nNextIndex] && nVecMap[nNextIndex] < nSharkSize)
				nVecFood.push_back(nNextIndex);
		}

		nQIndex.pop();
	}

	if (nVecFood.size() > 0)
	{
		sort(nVecFood.begin(), nVecFood.end());
		eatFood(nVecFood[0]);
		nOutputResult += nCurrDist;
		return true;
	}
	return false;
}

void eatFood(int nFoodIndex)
{
	nVecSharkNum[nVecMap[nFoodIndex]]--;
	nVecMap[nFoodIndex] = 0;
	nSharkIndex = nFoodIndex;
	nSharkEatNum++;
}

void init()
{
	bVecVisit.clear();
	bVecVisit.assign(nMapSize, false);
	nVecFood.clear();
	for (int i = 0; i < nMapSize + 1; i++)
		nSetVecIndexOfSameDist[i].clear();
	nSetVecIndexOfSameDist.clear();
	nSetVecIndexOfSameDist.assign(nMapSize + 1, set<int>());
}

void solve()
{
	while (isExistFood())
	{
		init();

		if (!searchFood())
			break;

		if (canGrowth())
		{
			nSharkSize++;
			nSharkEatNum = 0;
		}

	}
}

void output()
{
	cout << nOutputResult << "\n";
}