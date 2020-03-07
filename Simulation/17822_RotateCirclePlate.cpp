#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<algorithm>
#include<cmath>
#include<climits>
#include<set>
#include<map>
#include<string>
#include<cstring>
#include<functional>
using namespace std;

void inputAndInit();
void init();
void solve();
void output();
void solveAndOutput();

void rotate(int rotIdx);
bool findSame(int r, int c);
void updateByAvg();
int calSum();

int N, M, T, answer, num;

struct info {
	int x;
	int d;
	int k;
	info() { x = d = k = 0; }
	info(int X, int D, int K)
	{
		x = X;
		d = D;
		k = K;
	}
};

vector<vector<int> > plate;
vector<vector<bool> > del;
vector<int> rot;
vector<info> rotInfo;

int dirR[4], dirC[4];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int calSum()
{
	int ret = 0;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			ret += plate[r][c];
	return ret;
}

void updateByAvg()
{
	if (!num)
		return;
	float avg = calSum() / (float)num;
	for(int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
		{
			if (plate[r][c] > avg)
				plate[r][c]--;
			else if (!del[r][c] && plate[r][c] < avg)
				plate[r][c]++;
		}
}

void rotate(int rotIdx)
{
	for (int i = rotInfo[rotIdx].x - 1; i < N; i += rotInfo[rotIdx].x)
	{
		if (rotInfo[rotIdx].d)
			rot[i] += rotInfo[rotIdx].k;
		else
			rot[i] += (M - rotInfo[rotIdx].k);
		rot[i] %= M;
	}
}

bool findSame(int r, int c)
{
	bool ret = false;
	int currR, currC, nextR, nextC, value;
	queue<pair<int, int> > Q;
	Q.push(make_pair(r, c));
	value = plate[r][c];

	while (!Q.empty())
	{
		currR = Q.front().first;
		currC = (Q.front().second + M - rot[currR]) % M;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			if (nextR < 0 || nextR >= N)
				continue;
			nextC = (currC + dirC[dir] + rot[nextR]) % M;
			if (plate[nextR][nextC] != value)
				continue;
			if (del[nextR][nextC])
				continue;
			if (!ret)
			{
				plate[r][c] = 0;
				del[r][c] = true;
				num--;
				ret = true;
			}
			plate[nextR][nextC] = 0;
			del[nextR][nextC] = true;
			num--;
			Q.push(make_pair(nextR, nextC));
		}
	}

	return ret;
}

void inputAndInit()
{
	cin >> N >> M >> T;
	answer = 0;
	num = N * M;
	plate.assign(N, vector<int>(M, 0));
	del.assign(N, vector<bool>(M, false));
	rot.assign(N, 0);
	rotInfo.assign(T, info());
	dirR[0] = -1; dirR[1] = 0; dirR[2] = 1; dirR[3] = 0;
	dirC[0] = 0; dirC[1] = 1; dirC[2] = 0; dirC[3] = M - 1;
	for(int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			cin >> plate[i][j];
		}
	for (int i = 0; i < T; i++)
		cin >> rotInfo[i].x >> rotInfo[i].d >> rotInfo[i].k;
}

void solve()
{
	bool find;
	for (int i = 0; i < T; i++)
	{
		rotate(i);
		find = false;
		for (int r = 0; r < N; r++)
		{
			for (int c = 0; c < M; c+=2)
			{
				if (findSame(r, (c + r % 2 + rot[r])%M))
					find = true;
			}
		}
		if (!find)
			updateByAvg();
	}
	answer = calSum();
}

void output()
{
	cout << answer << "\n";
}
