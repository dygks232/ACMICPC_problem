#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<cmath>
#include<climits>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

#define CLEAN_NO 0
#define WALL 1
#define CLEAN_YES 2

int nInputRowLen, nInputColLen, nInputCurRow, nInputCurCol, nInputCurDir;

vector<int> nVecMapOrigin;

int dir[4];
int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,1,0,-1 };

bool func(int& curRow, int& curCol, int& curDir, int& cleanNum)
{
	bool bRet = true;
	bool bConditionC = true; // 사방이 청소되었거나 벽인 상태이면 true
	bool bConditionD = false; // 뒤쪽 칸이 벽이면 true

	int nCurIndex = curRow * nInputColLen + curCol;

	for (int i = 0; i < 4; i++)
	{
		if (nVecMapOrigin[nCurIndex + dir[i]] == CLEAN_NO)
		{
			bConditionC = false;
			break;
		}
	}

	if (nVecMapOrigin[nCurIndex + dir[(curDir + 3) % 4]] == WALL)
		bConditionD = true;

	if (bConditionC)
	{
		if (bConditionD)
			bRet = false;
		else
		{
			curRow += dirR[(curDir + 2) % 4];
			curCol += dirC[(curDir + 2) % 4];
		}
	}
	else if (nVecMapOrigin[nCurIndex + dir[curDir]] == CLEAN_NO) // Condition A
	{
		curDir = (curDir + 3) % 4;
		curRow += dirR[curDir];
		curCol += dirC[curDir];
		++cleanNum;
		nVecMapOrigin[curRow * nInputColLen + curCol] = CLEAN_YES;
	}
	else
	{
		curDir = (curDir + 3) % 4;
	}

	return bRet;
}

int main()
{
	int nMapSize, nTemp, nResult = 1;
	bool isPossible = true;
	cin >> nInputRowLen >> nInputColLen >> nInputCurRow >> nInputCurCol >> nInputCurDir;
	nMapSize = nInputRowLen * nInputColLen;
	dir[0] = -1;	dir[1] = -nInputColLen;
	dir[2] = 1;		dir[3] = nInputColLen;
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nTemp;
		nVecMapOrigin.push_back(nTemp);
	}
	nVecMapOrigin[nInputCurRow * nInputColLen + nInputCurCol] = CLEAN_YES;

	do {
		isPossible = func(nInputCurRow, nInputCurCol, nInputCurDir, nResult);
	} while (isPossible);	

	cout << nResult << endl;

	return 0;
}