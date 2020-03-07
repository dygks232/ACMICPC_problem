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

#define ENCODING_VALUE 1000
#define NOT_EXIST_SHARK -1

void input();
void init();
void solve();
void output();

void sharkMove();
void sharkCatch(int nCurrTime);
void sharkFeed(int nIndex1, int nIndex2);
int encodingSharkPos(int nRow, int nCol);
int findIndexByScale(int nScale);

bool isOutOfRange(int nSpeed);

struct shark
{
public:
	int row;
	int col;
	int speed;
	int dir; // 1:up, 2:down, 3:right, 4:left
	int scale;
	void input(int r, int c, int s, int d, int z)
	{
		row = r;
		col = c;
		speed = s;
		dir = d;
		scale = z;
	}
};

int nInputBoardRow, nInputBoardCol, nInputSharkNum;
int nOutputResult;

vector<shark> stVecShark;
map<int, int> nnMapEncodingSharkPosScale;
vector<int> nVecTargetSharkIndex;

int main()
{
	input();
	init();
	solve();
	output();
	return 0;
}

bool isOutOfRange(int nSpeed)
{
	return nSpeed > 0;
}

int encodingSharkPos(int nRow, int nCol)
{
	return nRow * ENCODING_VALUE + nCol;
}

int findIndexByScale(int nScale)
{
	int nSize = stVecShark.size();
	for (int i = 0; i < nSize; i++)
	{
		if (stVecShark[i].scale == nScale)
			return i;
	}
	return -1;
}

void sharkMove()
{
	int nCurrSharkNum = stVecShark.size();
	int nRealSpeed, nCurrDir, nRealMove, nCurrEncodingSharkPos, nCompareIndex;

	int nDirR[5] = { INT_MAX, -1, 1, 0, 0 };
	int nDirC[5] = { INT_MAX, 0, 0, 1, -1 };
	int nBoundary[5] = { INT_MAX, 1, nInputBoardRow, nInputBoardCol, 1 };

	nnMapEncodingSharkPosScale.clear();

	for (int i = 0; i < nCurrSharkNum; i++)
	{
		nRealSpeed = stVecShark[i].speed;
		nCurrDir = stVecShark[i].dir;
		if (nCurrDir < 3)
		{
			nRealMove = min(abs(stVecShark[i].row - nBoundary[nCurrDir]), nRealSpeed);
			stVecShark[i].row += nDirR[nCurrDir] * nRealMove;
			nRealSpeed -= nRealMove;
			while (isOutOfRange(nRealSpeed))
			{
				nCurrDir = nCurrDir % 2 + 1;
				nRealMove = min(abs(stVecShark[i].row - nBoundary[nCurrDir]), nRealSpeed);
				stVecShark[i].row += nDirR[nCurrDir] * nRealMove;
				nRealSpeed -= nRealMove;
			}
			stVecShark[i].dir = nCurrDir;
		}
		else
		{
			nRealMove = min(abs(stVecShark[i].col - nBoundary[nCurrDir]), nRealSpeed);
			stVecShark[i].col += nDirC[nCurrDir] * nRealMove;
			nRealSpeed -= nRealMove;
			while (isOutOfRange(nRealSpeed))
			{
				nCurrDir = nCurrDir % 2 + 3;
				nRealMove = min(abs(stVecShark[i].col - nBoundary[nCurrDir]), nRealSpeed);
				stVecShark[i].col += nDirC[nCurrDir] * nRealMove;
				nRealSpeed -= nRealMove;
			}
			stVecShark[i].dir = nCurrDir;
		}

		nCurrEncodingSharkPos = encodingSharkPos(stVecShark[i].row, stVecShark[i].col);
		if (nnMapEncodingSharkPosScale.find(nCurrEncodingSharkPos) == nnMapEncodingSharkPosScale.end())
		{
			nnMapEncodingSharkPosScale.insert(pair<int, int>(nCurrEncodingSharkPos, stVecShark[i].scale));
		}
		else
		{
			nCompareIndex = findIndexByScale(nnMapEncodingSharkPosScale.find(nCurrEncodingSharkPos)->second);
			sharkFeed(nCompareIndex, i);
			i--;
			nCurrSharkNum--;
		}
	}
}

void sharkFeed(int nIndex1, int nIndex2)
{
	if (stVecShark[nIndex1].scale > stVecShark[nIndex2].scale)
	{
		stVecShark.erase(stVecShark.begin() + nIndex2);
	}
	else
	{
		nnMapEncodingSharkPosScale.erase(encodingSharkPos(stVecShark[nIndex1].row, stVecShark[nIndex1].col));
		nnMapEncodingSharkPosScale.insert(pair<int, int>(encodingSharkPos(stVecShark[nIndex2].row, stVecShark[nIndex2].col), stVecShark[nIndex2].scale));
		stVecShark.erase(stVecShark.begin() + nIndex1);
	}
}

void sharkCatch(int nCurrTime)
{
	int nCurrSharkNum = stVecShark.size();
	int nCurrSharkRow, nTargetIndex;

	nVecTargetSharkIndex.clear();
	nVecTargetSharkIndex.assign(nInputBoardCol + 1, NOT_EXIST_SHARK);

	for (int i = 0; i < nCurrSharkNum; i++)
	{
		if (stVecShark[i].col != nCurrTime) continue;

		nCurrSharkRow = stVecShark[i].row;
		nTargetIndex = nVecTargetSharkIndex[nCurrTime];
		if (nTargetIndex == NOT_EXIST_SHARK)
		{
			nVecTargetSharkIndex[nCurrTime] = i;
		}
		else
		{
			if (stVecShark[nTargetIndex].row > nCurrSharkRow)
			{
				nVecTargetSharkIndex[nCurrTime] = i;
			}
		}
	}

	nTargetIndex = nVecTargetSharkIndex[nCurrTime];
	if (nTargetIndex == NOT_EXIST_SHARK)
		return;

	nOutputResult += stVecShark[nTargetIndex].scale;
	stVecShark.erase(stVecShark.begin() + nTargetIndex);
}

void input()
{
	int nRow, nCol, nSpeed, nDir, nScale;
	shark stInputShark;
	cin >> nInputBoardRow >> nInputBoardCol >> nInputSharkNum;
	for (int i = 0; i < nInputSharkNum; i++)
	{
		cin >> nRow >> nCol >> nSpeed >> nDir >> nScale;
		stInputShark.input(nRow, nCol, nSpeed, nDir, nScale);
		stVecShark.push_back(stInputShark);
	}
}

void init()
{
	nOutputResult = 0;
}

void solve()
{
	for (int nCurrTime = 1; nCurrTime <= nInputBoardCol; nCurrTime++)
	{
		sharkCatch(nCurrTime);
		sharkMove();
	}
}

void output()
{
	cout << nOutputResult << "\n";
}