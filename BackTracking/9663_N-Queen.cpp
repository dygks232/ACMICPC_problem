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

void calcAnswer(int row, int col);

int N, answer;

vector<int> pos;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void calcAnswer(int row, int col)
{
	pos[row] = col;
	for (int i = 0; i < row; i++)
	{
		if (pos[i] == col || row - i == abs(col - pos[i]))
			return;
	}
	if (row == N - 1)
	{
		answer++;
		return;
	}
	for (int i = 0; i < N; i++)
	{
		calcAnswer(row + 1, i);
	}
}

void inputAndInit()
{
	cin >> N;
	answer = 0;
	pos.assign(N, 0);
}

void solve()
{
	for (int i = 0; i < N; i++)
		calcAnswer(0, i);
}

void output()
{
	cout << answer << "\n";
}
