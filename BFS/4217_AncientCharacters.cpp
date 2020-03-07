#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<deque>
#include<vector>
#include<set>
#include<map>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<climits>
#include<functional>
using namespace std;

bool inputAndInit();
void solve();
void output(int i);

bool isOutOfBoundary(int r, int c);
void clustering(int r, int c);
void removeBackground(int r, int c);

int R, C, pBsize;
int clusterBtag;

bool board[400][400];
int pixelBR[160000];
int pixelBC[160000];
int clusterB[400][400];
int clusterW[400][400];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };
multiset<char> answer;

int main()
{
	int T = 1;
	do
	{
		if (!inputAndInit())
			break;
		solve();
		output(T);
		T++;
	} while (1);
	//system("pause");
	return 0;
}

bool isOutOfBoundary(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

bool inputAndInit()
{
	string in;
	int len;
	cin >> R >> C;
	if (R == 0 && C == 0) return false;
	memset(board, 0, 160000);
	memset(clusterB, 0, 160000 * sizeof(int));
	memset(clusterW, 0, 160000 * sizeof(int));
	answer.clear();
	clusterBtag = 1;
	pBsize = 0;
	for (int r = 0; r < R; r++)
	{
		cin >> in;
		for (int c = 0; c < C; c++)
		{
			switch (in[c])
			{
			case '1':
				board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			case '2':
				board[r][c * 4 + 2] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				break;
			case '3':
				board[r][c * 4 + 2] = board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			case '4':
				board[r][c * 4 + 1] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				break;
			case '5':
				board[r][c * 4 + 1] = board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			case '6':
				board[r][c * 4 + 1] = board[r][c * 4 + 2] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				break;
			case '7':
				board[r][c * 4 + 1] = board[r][c * 4 + 2] = board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			case '8':
				board[r][c * 4] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				break;
			case '9':
				board[r][c * 4] = board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			case 'a':
				board[r][c * 4] = board[r][c * 4 + 2] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				break;
			case 'b':
				board[r][c * 4] = board[r][c * 4 + 2] = board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			case 'c':
				board[r][c * 4] = board[r][c * 4 + 1] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				break;
			case 'd':
				board[r][c * 4] = board[r][c * 4 + 1] = board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			case 'e':
				board[r][c * 4] = board[r][c * 4 + 1] = board[r][c * 4 + 2] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				break;
			case 'f':
				board[r][c * 4] = board[r][c * 4 + 1] = board[r][c * 4 + 2] = board[r][c * 4 + 3] = 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 1;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 2;
				pixelBR[pBsize] = r; pixelBC[pBsize++] = c * 4 + 3;
				break;
			}
		}
	}
	C = C << 2;
	return true;
}

void removeBackground(int r, int c)
{
	if (clusterW[r][c] || board[r][c]) return;
	queue<pair<int, int> > Q;
	int currR, currC, nextR, nextC;
	clusterW[r][c] = -1;
	Q.push(make_pair(r, c));

	while (!Q.empty())
	{
		currR = Q.front().first;
		currC = Q.front().second;
		Q.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfBoundary(nextR, nextC))
				continue;
			if (board[nextR][nextC])
				continue;
			if (clusterW[nextR][nextC] == -1)
				continue;
			clusterW[nextR][nextC] = -1;
			Q.push(make_pair(nextR, nextC));
		}
	}
}

void clustering(int r, int c)
{
	if (clusterB[r][c]) return;
	queue<pair<int, int> > Q, Q2;
	queue<pair<int, pair<int, int> > > QW;
	int currR, currC, nextR, nextC, currDist;
	int clusterWnum = 0;
	clusterB[r][c] = clusterBtag;
	Q.push(make_pair(r, c));

	while (!Q.empty())
	{
		currR = Q.front().first;
		currC = Q.front().second;
		Q.pop();
		Q2.push(make_pair(currR, currC));
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfBoundary(nextR, nextC))
				continue;
			if (!board[nextR][nextC])
				continue;
			if (clusterB[nextR][nextC])
				continue;
			clusterB[nextR][nextC] = clusterBtag;
			Q.push(make_pair(nextR, nextC));
		}
	}

	while (!Q2.empty())
	{
		currR = Q2.front().first;
		currC = Q2.front().second;
		Q2.pop();
		while (currC + 1 < C && board[currR][currC + 1])
			currC++;
		currC++;
		if (currC == C) continue;
		if (clusterW[currR][currC]) continue;

		clusterWnum++;
		clusterW[currR][currC] = clusterBtag;
		QW.push(make_pair(0, make_pair(currR, currC)));
		while (!QW.empty())
		{
			currR = QW.front().second.first;
			currC = QW.front().second.second;
			currDist = QW.front().first;
			QW.pop();
			for (int dir = 0; dir < 4; dir++)
			{
				nextR = currR + dirR[dir];
				nextC = currC + dirC[dir];
				if (isOutOfBoundary(nextR, nextC))
					continue;
				if (clusterW[nextR][nextC])
					continue;
				if (board[nextR][nextC])
					continue;
				clusterW[nextR][nextC] = clusterBtag;
				QW.push(make_pair(currDist + 1, make_pair(nextR, nextC)));
			}
		}
	}

	switch (clusterWnum)
	{
	case 0: answer.insert('W'); break;
	case 1: answer.insert('A'); break;
	case 2: answer.insert('K'); break;
	case 3: answer.insert('J'); break;
	case 4: answer.insert('S'); break;
	case 5: answer.insert('D'); break;
	}

	clusterBtag++;
}

void solve()
{
	for (int c = 0; c < C; c++)
	{
		removeBackground(0, c);
		removeBackground(R - 1, c);
	}
	for (int r = 0; r < R; r++)
	{
		removeBackground(r, 0);
		removeBackground(r, C - 1);
	}
	for (int i = 0; i < pBsize; i++)
	{
		clustering(pixelBR[i], pixelBC[i]);
	}
}

void output(int i)
{
	multiset<char>::iterator it;
	printf("Case %d: ", i);
	for (it = answer.begin(); it != answer.end(); it++)
		printf("%c", *it);
	printf("\n");
}