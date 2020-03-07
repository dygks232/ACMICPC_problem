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
void solve();
void output();
void moveSnake(int nRow, int nCol);
void removeTail();
void calNextSnakePos();
bool isOutOfBoundary();
bool isTimeToEat();
bool isGameEnd();

#define TURN_RIGHT 1
#define TURN_LEFT -1

int nDirR[4] = { 0, 1, 0, -1};
int nDirC[4] = { 1, 0, -1, 0};

int nInputBoardLen, nInputAppleNum, nInputTurnNum;
int nCurrDir, nNextTurnIndex, nCurrTime;
int nOutputResult;
vector<pair<int, int> > nnVecApplePos;
vector<pair<int, int> > nnVecTurnInfo;
deque<pair<int, int> > nnDeqSnake;

pair<int, int> nnNextSnakePos;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void moveSnake(int nRow, int nCol)
{
	nnDeqSnake.push_back(make_pair(nRow, nCol));
}

void removeTail()
{
	nnDeqSnake.pop_front();
}

void calNextSnakePos()
{
	if (nNextTurnIndex < nInputTurnNum && nnVecTurnInfo[nNextTurnIndex].first == nCurrTime)
	{
		nCurrDir = (nCurrDir + nnVecTurnInfo[nNextTurnIndex].second + 4) % 4;
		nNextTurnIndex++;
	}
	nnNextSnakePos.first += nDirR[nCurrDir];
	nnNextSnakePos.second += nDirC[nCurrDir];
}

bool isTimeToEat()
{
	bool bRet = false;
	for (int i = 0; i < nInputAppleNum; i++)
	{
		if (nnNextSnakePos.first == nnVecApplePos[i].first &&
			nnNextSnakePos.second == nnVecApplePos[i].second)
		{
			bRet = true;
			nnVecApplePos.erase(nnVecApplePos.begin() + i);
			nInputAppleNum--;
			break;
		}
	}
	return bRet;
}

bool isOutOfBoundary()
{
	bool bRet = false;
	if (nnNextSnakePos.first < 1 || nnNextSnakePos.first > nInputBoardLen || nnNextSnakePos.second < 1 || nnNextSnakePos.second > nInputBoardLen)
		bRet = true;
	return bRet;
}

bool isGameEnd()
{
	bool bRet = false;
	deque<pair<int, int> >::iterator deqIter;

	if (isOutOfBoundary())
	{
		bRet = true;
		return bRet;
	}

	for (deqIter = nnDeqSnake.begin(); deqIter != nnDeqSnake.end(); deqIter++)
	{
		if (deqIter->first == nnNextSnakePos.first &&
			deqIter->second == nnNextSnakePos.second)
		{
			bRet = true;
			break;
		}
	}	

	return bRet;
}

void inputAndInit()
{
	char cInput;
	bool isCorrectInput;
	int nInput1, nInput2;

	nCurrDir = nCurrTime = 0;
	nNextTurnIndex = 0;
	nOutputResult = 0;
	moveSnake(1, 1);
	nnNextSnakePos = make_pair(1, 2);

	cin >> nInputBoardLen >> nInputAppleNum;
	nnVecApplePos.assign(nInputAppleNum, pair<int, int>());
	for (int i = 0; i < nInputAppleNum; i++)
	{
		cin >> nInput1 >> nInput2;
		nnVecApplePos[i].first = nInput1;
		nnVecApplePos[i].second = nInput2;
	}

	cin >> nInputTurnNum;
	nnVecTurnInfo.assign(nInputTurnNum, pair<int, int>());
	for (int i = 0; i < nInputTurnNum; i++)
	{
		isCorrectInput = false;
		cin >> nInput1;
		while (!isCorrectInput)
		{
			cInput = getchar();
			if (cInput == 'D' || cInput == 'L')
				isCorrectInput = true;
		}
		nnVecTurnInfo[i].first = nInput1;
		if (cInput == 'D')
			nnVecTurnInfo[i].second = TURN_RIGHT;
		else
			nnVecTurnInfo[i].second = TURN_LEFT;
	}
}

void solve()
{
	while (!isGameEnd())
	{
		nCurrTime++;
		moveSnake(nnNextSnakePos.first, nnNextSnakePos.second);
		if (!isTimeToEat())
		{
			removeTail();
		}
		calNextSnakePos();
	}

	nOutputResult = nCurrTime + 1;
}

void output()
{
	cout << nOutputResult << "\n";
}
