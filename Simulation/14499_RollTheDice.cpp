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

#define ROLL_EAST 1
#define ROLL_WEST 2
#define ROLL_NORTH 3
#define ROLL_SOUTH 4

#define SIDE_VERTICAL 0
#define SIDE_HORIZONTAL 1
#define SIDE_SPARE 2

#define VERTICAL_TOP 0
#define VERTICAL_BOTTOM 2
#define HORIZONTAL_BOTTOM 2

void inputAndInit();
void solveAndOutput();

bool isOutOfRange();
void rotateDice(int nCommand);
void changeValue();
void calNextDicePos(int nCommand);
void moveDice();
void notMoveDice();

void SWAP(int &a, int &b);
void reverse(int nSide);
void right_shift(int nSide);
void left_shift(int nSide);
void copyCloneToOrigin(int nCloneSide, int nOriginSide);

int nInputMapRow, nInputMapCol, nInputDiceRowPos, nInputDiceColPos, nInputCommandNum;
int nMapSize, nNextDiceRowPos, nNextDiceColPos;
int nOutputResult;

vector<int> nVecMap;
vector<int> nVecCommand;

vector<vector<int> > nVecVecDiceSide;
vector<vector<int> > nVecVecDiceSideClone;

int main()
{
	inputAndInit();
	solveAndOutput();
	return 0;
}

void SWAP(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

bool isOutOfRange()
{
	return nNextDiceRowPos < 0 || nNextDiceRowPos >= nInputMapRow || nNextDiceColPos < 0 || nNextDiceColPos >= nInputMapCol;
}

void inputAndInit()
{
	int nInput;
	cin >> nInputMapRow >> nInputMapCol >> nInputDiceRowPos >> nInputDiceColPos >> nInputCommandNum;
	nMapSize = nInputMapRow * nInputMapCol;
	nNextDiceRowPos = nInputDiceRowPos;
	nNextDiceColPos = nInputDiceColPos;
	nVecMap.assign(nMapSize, 0);
	nVecCommand.assign(nInputCommandNum, 0);
	for (int i = 0; i < nMapSize; i++)
	{
		cin >> nInput;
		nVecMap[i] = nInput;
	}
	for (int i = 0; i < nInputCommandNum; i++)
	{
		cin >> nInput;
		nVecCommand[i] = nInput;
	}

	nVecVecDiceSide.assign(3, vector<int>(4, 0));
	nVecVecDiceSideClone.assign(3, vector<int>(4, 0));
}

void calNextDicePos(int nCommand)
{
	switch (nCommand) {
	case ROLL_EAST:
		nNextDiceColPos++;
		break;
	case ROLL_WEST:
		nNextDiceColPos--;
		break;
	case ROLL_NORTH:
		nNextDiceRowPos--;
		break;
	case ROLL_SOUTH:
		nNextDiceRowPos++;
		break;
	}
}

void moveDice()
{
	nInputDiceRowPos = nNextDiceRowPos;
	nInputDiceColPos = nNextDiceColPos;
}

void notMoveDice()
{
	nNextDiceRowPos = nInputDiceRowPos;
	nNextDiceColPos = nInputDiceColPos;
}

void reverse(int nSide)
{
	SWAP(nVecVecDiceSideClone[nSide][0], nVecVecDiceSideClone[nSide][3]);
	SWAP(nVecVecDiceSideClone[nSide][1], nVecVecDiceSideClone[nSide][2]);
}

void right_shift(int nSide)
{
	SWAP(nVecVecDiceSideClone[nSide][3], nVecVecDiceSideClone[nSide][2]);
	SWAP(nVecVecDiceSideClone[nSide][2], nVecVecDiceSideClone[nSide][1]);
	SWAP(nVecVecDiceSideClone[nSide][1], nVecVecDiceSideClone[nSide][0]);
}

void left_shift(int nSide)
{
	SWAP(nVecVecDiceSideClone[nSide][0], nVecVecDiceSideClone[nSide][1]);
	SWAP(nVecVecDiceSideClone[nSide][1], nVecVecDiceSideClone[nSide][2]);
	SWAP(nVecVecDiceSideClone[nSide][2], nVecVecDiceSideClone[nSide][3]);
}

void copyCloneToOrigin(int nCloneSide, int nOriginSide)
{
	nVecVecDiceSide[nOriginSide].assign(nVecVecDiceSideClone[nCloneSide].begin(), nVecVecDiceSideClone[nCloneSide].end());
}

void rotateDice(int nCommand)
{
	for (int i = 0; i < 3; i++)
		nVecVecDiceSideClone[i].assign(nVecVecDiceSide[i].begin(), nVecVecDiceSide[i].end());

	switch (nCommand)
	{
	case ROLL_EAST:
		reverse(SIDE_SPARE);
		right_shift(SIDE_HORIZONTAL);
		right_shift(SIDE_VERTICAL);
		copyCloneToOrigin(SIDE_SPARE, SIDE_VERTICAL);
		copyCloneToOrigin(SIDE_HORIZONTAL, SIDE_HORIZONTAL);
		copyCloneToOrigin(SIDE_VERTICAL, SIDE_SPARE);
		break;
	case ROLL_WEST:
		left_shift(SIDE_SPARE);
		left_shift(SIDE_HORIZONTAL);
		reverse(SIDE_VERTICAL);
		copyCloneToOrigin(SIDE_SPARE, SIDE_VERTICAL);
		copyCloneToOrigin(SIDE_HORIZONTAL, SIDE_HORIZONTAL);
		copyCloneToOrigin(SIDE_VERTICAL, SIDE_SPARE);
		break;
	case ROLL_NORTH:
		left_shift(SIDE_VERTICAL);
		reverse(SIDE_SPARE);
		left_shift(SIDE_SPARE);
		copyCloneToOrigin(SIDE_VERTICAL, SIDE_VERTICAL);
		copyCloneToOrigin(SIDE_SPARE, SIDE_HORIZONTAL);
		copyCloneToOrigin(SIDE_HORIZONTAL, SIDE_SPARE);
		break;
	case ROLL_SOUTH:
		right_shift(SIDE_VERTICAL);
		reverse(SIDE_HORIZONTAL);
		left_shift(SIDE_HORIZONTAL);
		copyCloneToOrigin(SIDE_VERTICAL, SIDE_VERTICAL);
		copyCloneToOrigin(SIDE_SPARE, SIDE_HORIZONTAL);
		copyCloneToOrigin(SIDE_HORIZONTAL, SIDE_SPARE);
		break;
	}
}

void changeValue()
{
	int nCurrPosIndex = nInputDiceRowPos * nInputMapCol + nInputDiceColPos;
	if (nVecMap[nCurrPosIndex])
	{
		nVecVecDiceSide[SIDE_VERTICAL][VERTICAL_BOTTOM] = nVecMap[nCurrPosIndex];
		nVecVecDiceSide[SIDE_HORIZONTAL][HORIZONTAL_BOTTOM] = nVecMap[nCurrPosIndex];
		nVecMap[nCurrPosIndex] = 0;
	}
	else
	{
		nVecMap[nCurrPosIndex] = nVecVecDiceSide[SIDE_VERTICAL][VERTICAL_BOTTOM];
	}
}

void solveAndOutput()
{
	for (int nRoll = 0; nRoll < nInputCommandNum; nRoll++)
	{
		calNextDicePos(nVecCommand[nRoll]);
		if (isOutOfRange())
		{
			notMoveDice();
			continue;
		}
		moveDice();
		rotateDice(nVecCommand[nRoll]);
		changeValue();

		nOutputResult = nVecVecDiceSide[SIDE_VERTICAL][VERTICAL_TOP];
		cout << nOutputResult << "\n";
	}
}