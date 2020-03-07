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

void input();
void init();
void solve();
void output();
bool isOutOfRange(int nIndex);
bool isOutOfRange(int nRow, int nCol);

int nInputTestCase, nInputBoardLen, nInputStartRow, nInputStartCol, nInputEndRow, nInputEndCol, nOutputResult;

vector<bool> bVecVisitIndex;
vector<int> nVecIndexResult;

bool isOutOfRange(int nIndex)
{
	int nRow = nIndex / nInputBoardLen;
	int nCol = nIndex % nInputBoardLen;
	return nRow < 0 || nRow >= nInputBoardLen || nCol < 0 || nCol >= nInputBoardLen;
}

bool isOutOfRange(int nRow, int nCol)
{
	return nRow < 0 || nRow >= nInputBoardLen || nCol < 0 || nCol >= nInputBoardLen;
}

int main()
{
	cin >> nInputTestCase;
	while (nInputTestCase--) {
		input();
		init();
		solve();
		output();
	}
	return 0;
}

void input()
{
	cin >> nInputBoardLen >> nInputStartRow >> nInputStartCol >> nInputEndRow >> nInputEndCol;
}

void init()
{
	bVecVisitIndex.clear();
	bVecVisitIndex.assign(nInputBoardLen * nInputBoardLen, false);
	nVecIndexResult.clear();
	nVecIndexResult.assign(nInputBoardLen * nInputBoardLen, 0);
}

void solve()
{
	queue<int> Q;
	int nCurrIndex = nInputStartRow * nInputBoardLen + nInputStartCol;
	int nEndIndex = nInputEndRow * nInputBoardLen + nInputEndCol;
	if (nCurrIndex == nEndIndex) {
		nOutputResult = 0;
		return;
	}
	int nDirR[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int nDirC[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	int nCurrRow = nInputStartRow;
	int nCurrCol = nInputStartCol;
	int nNextIndex, nNextRow, nNextCol;

	bVecVisitIndex[nCurrIndex] = true;
	Q.push(nCurrIndex);

	while (!Q.empty()) {
		nCurrIndex = Q.front();
		nCurrRow = nCurrIndex / nInputBoardLen;
		nCurrCol = nCurrIndex % nInputBoardLen;
		for (int i = 0; i < 8; i++) {
			nNextRow = nCurrRow + nDirR[i];
			nNextCol = nCurrCol + nDirC[i];
			nNextIndex = nNextRow * nInputBoardLen + nNextCol;

			if (isOutOfRange(nNextRow, nNextCol)) continue;
			if (bVecVisitIndex[nNextIndex]) continue;

			Q.push(nNextIndex);
			bVecVisitIndex[nNextIndex] = true;
			nVecIndexResult[nNextIndex] = nVecIndexResult[nCurrIndex] + 1;

			if (nNextIndex == nEndIndex) {
				nOutputResult = nVecIndexResult[nNextIndex];
				return;
			}
		}
		Q.pop();
	}
}

void output()
{
	cout << nOutputResult << "\n";
}
