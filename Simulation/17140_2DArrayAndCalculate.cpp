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
using namespace std;

void inputAndInit();
void init();
void solve();
void output();

void calR();
void calC();
void fixR();
void fixC();
bool isAnswer();
void SWAP(int& a, int& b);

int nInputAnswerRow, nInputAnswerCol, nInputValue;
int nRowLen, nColLen, nMaxLen;
int nOutputResult;

vector<vector<int> > nVecVecMatrixRow;
vector<vector<int> > nVecVecMatrixCol;

vector<int> nVecCache;
vector<pair<int, int> > nnVecValueNum;
vector<int> nVecNum;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void SWAP(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

void init()
{
	nVecCache.clear();
	nnVecValueNum.clear();
	nVecNum.assign(nMaxLen, 0);
}

void calR()
{
	int r, c, i, j, nPairSize, nMax = INT_MIN, nIter, nNewSize;
	for (r = 0; r < nRowLen; r++)
	{
		init();

		for (c = 0; c < nColLen; c++)
		{
			if (nVecVecMatrixRow[r][c] > 0)
			{
				nVecNum[nVecVecMatrixRow[r][c]]++;
			}
		}

		for (i = 1; i < nMaxLen; i++)
		{
			if (nVecNum[i] > 0)
				nnVecValueNum.push_back(make_pair(i, nVecNum[i]));
		}

		nPairSize = nnVecValueNum.size();
		for (i = 0; i < nPairSize; i++)
		{
			for (j = i + 1; j < nPairSize; j++)
			{
				if (nnVecValueNum[i].second > nnVecValueNum[j].second)
				{
					SWAP(nnVecValueNum[i].first, nnVecValueNum[j].first);
					SWAP(nnVecValueNum[i].second, nnVecValueNum[j].second);
				}
				else if (nnVecValueNum[i].second == nnVecValueNum[j].second
					&& nnVecValueNum[i].first > nnVecValueNum[j].first)
				{
					SWAP(nnVecValueNum[i].first, nnVecValueNum[j].first);
					SWAP(nnVecValueNum[i].second, nnVecValueNum[j].second);
				}
			}
		}
		for (i = 0; i < nPairSize; i++)
		{
			nVecCache.push_back(nnVecValueNum[i].first);
			nVecCache.push_back(nnVecValueNum[i].second);
		}
		nNewSize = min((int)(nVecCache.size()), 100);

		nVecVecMatrixRow[r].clear();
		nVecVecMatrixRow[r].assign(nNewSize, 0);
		for (i = 0; i < nNewSize; i++)
			nVecVecMatrixRow[r][i] = nVecCache[i];

		nMax = max(nMax, (int)(nVecVecMatrixRow[r].size()));
	}

	nColLen = nMax;

	for (r = 0; r < nRowLen; r++)
	{
		nIter = nColLen - nVecVecMatrixRow[r].size();
		for (i = 0; i < nIter; i++)
			nVecVecMatrixRow[r].push_back(0);
	}
}

void calC()
{
	int r, c, i, j, nPairSize, nMax = INT_MIN, nIter, nNewSize;
	for (c = 0; c < nColLen; c++)
	{
		init();

		for (r = 0; r < nRowLen; r++)
		{
			if (nVecVecMatrixCol[c][r] > 0)
			{
				nVecNum[nVecVecMatrixCol[c][r]]++;
			}
		}

		for (i = 1; i < nMaxLen; i++)
		{
			if (nVecNum[i] > 0)
				nnVecValueNum.push_back(make_pair(i, nVecNum[i]));
		}

		nPairSize = nnVecValueNum.size();
		for (i = 0; i < nPairSize; i++)
		{
			for (j = i + 1; j < nPairSize; j++)
			{
				if (nnVecValueNum[i].second > nnVecValueNum[j].second)
				{
					SWAP(nnVecValueNum[i].first, nnVecValueNum[j].first);
					SWAP(nnVecValueNum[i].second, nnVecValueNum[j].second);
				}
				else if (nnVecValueNum[i].second == nnVecValueNum[j].second
					&& nnVecValueNum[i].first > nnVecValueNum[j].first)
				{
					SWAP(nnVecValueNum[i].first, nnVecValueNum[j].first);
					SWAP(nnVecValueNum[i].second, nnVecValueNum[j].second);
				}
			}
		}
		for (i = 0; i < nPairSize; i++)
		{
			nVecCache.push_back(nnVecValueNum[i].first);
			nVecCache.push_back(nnVecValueNum[i].second);
		}
		nNewSize = min((int)(nVecCache.size()), 100);

		nVecVecMatrixCol[c].clear();
		nVecVecMatrixCol[c].assign(nNewSize, 0);
		for (i = 0; i < nNewSize; i++)
			nVecVecMatrixCol[c][i] = nVecCache[i];

		nMax = max(nMax, (int)(nVecVecMatrixCol[c].size()));
	}

	nRowLen = nMax;

	for (c = 0; c < nColLen; c++)
	{
		nIter = nRowLen - nVecVecMatrixCol[c].size();
		for (i = 0; i < nIter; i++)
			nVecVecMatrixCol[c].push_back(0);
	}
}

void fixR()
{
	nVecVecMatrixRow.clear();
	nVecVecMatrixRow.assign(nRowLen, vector<int>(nColLen, 0));
	for (int r = 0; r < nRowLen; r++)
		for (int c = 0; c < nColLen; c++)
			nVecVecMatrixRow[r][c] = nVecVecMatrixCol[c][r];
}

void fixC()
{
	nVecVecMatrixCol.clear();
	nVecVecMatrixCol.assign(nColLen, vector<int>(nRowLen, 0));
	for (int r = 0; r < nRowLen; r++)
		for (int c = 0; c < nColLen; c++)
			nVecVecMatrixCol[c][r] = nVecVecMatrixRow[r][c];
}

bool isAnswer()
{
	return nInputAnswerRow < nRowLen && nInputAnswerCol < nColLen && nVecVecMatrixRow[nInputAnswerRow][nInputAnswerCol] == nInputValue;
}

void inputAndInit()
{
	int nInput;
	nRowLen = nColLen = 3;
	nMaxLen = 101;
	cin >> nInputAnswerRow >> nInputAnswerCol >> nInputValue;
	nInputAnswerRow--; nInputAnswerCol--;
	nVecVecMatrixRow.assign(nRowLen, vector<int>(nColLen, 0));
	nVecVecMatrixCol.assign(nColLen, vector<int>(nRowLen, 0));

	for (int r = 0; r < nRowLen; r++)
	{
		for (int c = 0; c < nColLen; c++)
		{
			cin >> nInput;
			nVecVecMatrixRow[r][c] = nInput;
			nVecVecMatrixCol[c][r] = nInput;
		}
	}
}

void solve()
{
	while (!isAnswer() && nOutputResult <= 100)
	{
		if (nRowLen >= nColLen)
		{
			calR();
			fixC();
		}
		else
		{
			calC();
			fixR();
		}
		nOutputResult++;
	}
}

void output()
{
	if (nOutputResult > 100)
		cout << "-1\n";
	else
		cout << nOutputResult << "\n";
}