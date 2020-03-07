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

#define NORTH_INDEX 0
#define EAST_INDEX 2
#define WEST_INDEX 6

void initialize();
void input();
void output();
void gear(int gearIndex, int rotDir, int spreadDir);

vector<deque<bool>> deqVecGear;
vector<pair<int, int>> nnVecRotMethod;

int main()
{
	initialize();
	input();
	output();

	return 0;
}

void initialize()
{
	deqVecGear.assign(4, deque<bool>());
}

void input()
{
	int nInputRotNum, nTemp, nTemp2;
	for (int i = 0; i < 4; i++)
	{
		cin >> nTemp;
		while (nTemp)
		{
			deqVecGear[i].push_front(nTemp % 10);
			nTemp /= 10;
		}
		while (deqVecGear[i].size() < 8)
			deqVecGear[i].push_front(0);
	}
	cin >> nInputRotNum;
	for (int i = 0; i < nInputRotNum; i++)
	{
		cin >> nTemp >> nTemp2;
		nnVecRotMethod.push_back(make_pair(nTemp, nTemp2));
	}

}

void output()
{
	int nInputRotNum = nnVecRotMethod.size();
	int nResult = 0;

	for (int i = 0; i < nInputRotNum; i++)
	{
		gear(nnVecRotMethod[i].first, nnVecRotMethod[i].second, 0);
	}
	for (int i = 0; i < 4; i++)
	{
		if (deqVecGear[i][NORTH_INDEX])
			nResult += (int)pow(2.0, i);
	}

	cout << nResult << endl;
}

void gear(int gearIndex, int rotDir, int spreadDir)
{
	if (spreadDir >= 0)
	{
		if (gearIndex != 4 && deqVecGear[gearIndex - 1][EAST_INDEX] != deqVecGear[gearIndex][WEST_INDEX])
		{
			gear(gearIndex + 1, -rotDir, 1);
		}
	}
	if (spreadDir <= 0)
	{
		if (gearIndex != 1 && deqVecGear[gearIndex - 1][WEST_INDEX] != deqVecGear[gearIndex - 2][EAST_INDEX])
		{
			gear(gearIndex - 1, -rotDir, -1);
		}
	}

	int nTemp;
	if (rotDir > 0)
	{
		nTemp = deqVecGear[gearIndex - 1][7];
		deqVecGear[gearIndex - 1].pop_back();
		deqVecGear[gearIndex - 1].push_front(nTemp);
	}
	else
	{
		nTemp = deqVecGear[gearIndex - 1][0];
		deqVecGear[gearIndex - 1].pop_front();
		deqVecGear[gearIndex - 1].push_back(nTemp);
	}
}