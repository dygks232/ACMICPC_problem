// 2019/10/18 NYH
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
#include<string>
using namespace std;

#define PLANE_NUM 6
#define BLOCK_NUM 9

#define DIR_CLOCK 0
#define DIR_ANTICLOCK 1

#define PLANE_UP 0
#define PLANE_FRONT 1
#define PLANE_RIGHT 2
#define PLANE_LEFT 3
#define PLANE_BACK 4
#define PLANE_DOWN 5

void inputAndInit();
void init();
void solve();
void output();

void firstInit();
void SWAP(char &a, char &b);
void rotateBlock(int nPlaneIndex, int nDir);
void rotateSide(int nPlaneIndex, int nDir);
void rotateCube(int nMethodIndex);

struct connectBlock
{
	int first;
	int second;
	int third;
	connectBlock()
	{
		first = 0; second = 0; third = 0;
	}
	connectBlock(int f, int s, int t)
	{
		first = f; second = s; third = t;
	}
};

int nInputTestCase, nInputRotNum;

vector<pair<int, int> > nnVecRotMethod;

vector<vector<char> > cVecVecCube;

vector<vector<pair<int, connectBlock> > > nstVecVecPlaneConnect;

int main()
{
	cin >> nInputTestCase;
	firstInit();
	while (nInputTestCase--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

void SWAP(char &a, char &b)
{
	char c = a;
	a = b;
	b = c;
}

void rotateBlock(int nPlaneIndex, int nDir)
{
	if (nDir == DIR_CLOCK)
	{
		SWAP(cVecVecCube[nPlaneIndex][0], cVecVecCube[nPlaneIndex][2]);
		SWAP(cVecVecCube[nPlaneIndex][3], cVecVecCube[nPlaneIndex][1]);
		SWAP(cVecVecCube[nPlaneIndex][6], cVecVecCube[nPlaneIndex][0]);
		SWAP(cVecVecCube[nPlaneIndex][7], cVecVecCube[nPlaneIndex][3]);
		SWAP(cVecVecCube[nPlaneIndex][8], cVecVecCube[nPlaneIndex][6]);
		SWAP(cVecVecCube[nPlaneIndex][5], cVecVecCube[nPlaneIndex][7]);
	}
	else
	{
		SWAP(cVecVecCube[nPlaneIndex][0], cVecVecCube[nPlaneIndex][6]);
		SWAP(cVecVecCube[nPlaneIndex][1], cVecVecCube[nPlaneIndex][3]);
		SWAP(cVecVecCube[nPlaneIndex][2], cVecVecCube[nPlaneIndex][0]);
		SWAP(cVecVecCube[nPlaneIndex][5], cVecVecCube[nPlaneIndex][1]);
		SWAP(cVecVecCube[nPlaneIndex][8], cVecVecCube[nPlaneIndex][2]);
		SWAP(cVecVecCube[nPlaneIndex][7], cVecVecCube[nPlaneIndex][5]);
	}
}

void rotateSide(int nPlaneIndex, int nDir)
{
	int i, j;
	if (nDir == DIR_CLOCK)
	{
		for (i = 3; i > 0; --i)
		{
			SWAP(cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][i].first][nstVecVecPlaneConnect[nPlaneIndex][i].second.first], cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][(i + 3) % 4].first][nstVecVecPlaneConnect[nPlaneIndex][(i + 3) % 4].second.first]);
			SWAP(cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][i].first][nstVecVecPlaneConnect[nPlaneIndex][i].second.second], cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][(i + 3) % 4].first][nstVecVecPlaneConnect[nPlaneIndex][(i + 3) % 4].second.second]);
			SWAP(cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][i].first][nstVecVecPlaneConnect[nPlaneIndex][i].second.third], cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][(i + 3) % 4].first][nstVecVecPlaneConnect[nPlaneIndex][(i + 3) % 4].second.third]);
		}
	}
	else
	{
		for (i = 0; i < 3; ++i)
		{
			SWAP(cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][i].first][nstVecVecPlaneConnect[nPlaneIndex][i].second.first], cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][(i + 1) % 4].first][nstVecVecPlaneConnect[nPlaneIndex][(i + 1) % 4].second.first]);
			SWAP(cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][i].first][nstVecVecPlaneConnect[nPlaneIndex][i].second.second], cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][(i + 1) % 4].first][nstVecVecPlaneConnect[nPlaneIndex][(i + 1) % 4].second.second]);
			SWAP(cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][i].first][nstVecVecPlaneConnect[nPlaneIndex][i].second.third], cVecVecCube[nstVecVecPlaneConnect[nPlaneIndex][(i + 1) % 4].first][nstVecVecPlaneConnect[nPlaneIndex][(i + 1) % 4].second.third]);
		}
	}
}

void firstInit()
{
	cVecVecCube.assign(PLANE_NUM, vector<char>());
	nstVecVecPlaneConnect.assign(PLANE_NUM, vector<pair<int, connectBlock> >(4, make_pair(0, connectBlock())));
	nstVecVecPlaneConnect[0][0] = make_pair(4, connectBlock(0, 1, 2));
	nstVecVecPlaneConnect[0][1] = make_pair(2, connectBlock(0, 1, 2));
	nstVecVecPlaneConnect[0][2] = make_pair(1, connectBlock(0, 1, 2));
	nstVecVecPlaneConnect[0][3] = make_pair(3, connectBlock(0, 1, 2));
	nstVecVecPlaneConnect[1][0] = make_pair(0, connectBlock(6, 7, 8));
	nstVecVecPlaneConnect[1][1] = make_pair(2, connectBlock(0, 3, 6));
	nstVecVecPlaneConnect[1][2] = make_pair(5, connectBlock(2, 1, 0));
	nstVecVecPlaneConnect[1][3] = make_pair(3, connectBlock(8, 5, 2));
	nstVecVecPlaneConnect[2][0] = make_pair(0, connectBlock(8, 5, 2));
	nstVecVecPlaneConnect[2][1] = make_pair(4, connectBlock(0, 3, 6));
	nstVecVecPlaneConnect[2][2] = make_pair(5, connectBlock(8, 5, 2));
	nstVecVecPlaneConnect[2][3] = make_pair(1, connectBlock(8, 5, 2));
	nstVecVecPlaneConnect[3][0] = make_pair(0, connectBlock(0, 3, 6));
	nstVecVecPlaneConnect[3][1] = make_pair(1, connectBlock(0, 3, 6));
	nstVecVecPlaneConnect[3][2] = make_pair(5, connectBlock(0, 3, 6));
	nstVecVecPlaneConnect[3][3] = make_pair(4, connectBlock(8, 5, 2));
	nstVecVecPlaneConnect[4][0] = make_pair(0, connectBlock(2, 1, 0));
	nstVecVecPlaneConnect[4][1] = make_pair(3, connectBlock(0, 3, 6));
	nstVecVecPlaneConnect[4][2] = make_pair(5, connectBlock(6, 7, 8));
	nstVecVecPlaneConnect[4][3] = make_pair(2, connectBlock(8, 5, 2));
	nstVecVecPlaneConnect[5][0] = make_pair(1, connectBlock(6, 7, 8));
	nstVecVecPlaneConnect[5][1] = make_pair(2, connectBlock(6, 7, 8));
	nstVecVecPlaneConnect[5][2] = make_pair(4, connectBlock(6, 7, 8));
	nstVecVecPlaneConnect[5][3] = make_pair(3, connectBlock(6, 7, 8));
}

void inputAndInit()
{
	string strInput;
	int nPlane, nDir;
	cin >> nInputRotNum;
	nnVecRotMethod.clear();
	nnVecRotMethod.assign(nInputRotNum, pair<int, int>());
	for (int i = 0; i < PLANE_NUM; i++)
		cVecVecCube[i].clear();
	cVecVecCube[0].assign(BLOCK_NUM, 'w');
	cVecVecCube[1].assign(BLOCK_NUM, 'r');
	cVecVecCube[2].assign(BLOCK_NUM, 'b');
	cVecVecCube[3].assign(BLOCK_NUM, 'g');
	cVecVecCube[4].assign(BLOCK_NUM, 'o');
	cVecVecCube[5].assign(BLOCK_NUM, 'y');
	for (int i = 0; i < nInputRotNum; i++)
	{
		cin >> strInput;
		switch (strInput[0])
		{
		case 'U': nPlane = PLANE_UP; break;
		case 'F': nPlane = PLANE_FRONT; break;
		case 'R': nPlane = PLANE_RIGHT; break;
		case 'L': nPlane = PLANE_LEFT; break;
		case 'B': nPlane = PLANE_BACK; break;
		case 'D': nPlane = PLANE_DOWN; break;
		}
		switch (strInput[1])
		{
		case '+': nDir = DIR_CLOCK; break;
		case '-': nDir = DIR_ANTICLOCK; break;
		}
		nnVecRotMethod[i] = make_pair(nPlane, nDir);
	}
}

void rotateCube(int nMethodIndex)
{
	int nRotPlane = nnVecRotMethod[nMethodIndex].first;
	int nRotDir = nnVecRotMethod[nMethodIndex].second;

	rotateBlock(nRotPlane, nRotDir);
	rotateSide(nRotPlane, nRotDir);
}

void solve()
{
	for (int i = 0; i < nInputRotNum; i++)
		rotateCube(i);
}

void output()
{
	for (int i = 0; i < BLOCK_NUM; i++)
	{
		cout << cVecVecCube[0][i];
		if (i % 3 == 2)
			cout << "\n";
	}
}