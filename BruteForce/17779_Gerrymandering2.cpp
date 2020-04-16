#define _CRT_SECURE_NO_WARNINGS
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

#define MAXN 20

void inputAndInit();
void solve();
void output();

void calcAns(int row, int col, int left, int right);
int calc1(int row, int col, int left, int right);
int calc2(int row, int col, int left, int right);
int calc3(int row, int col, int left, int right);
int calc4(int row, int col, int left, int right);
int calc5(int row, int col, int left, int right);

int N, answer;

int arr[MAXN + 1][MAXN + 1] = { 0, };
int sorted[5];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	int in;
	scanf("%d", &N);
	answer = INT_MAX;
	for(int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		{
			scanf("%d", &in);
			arr[i][j] = arr[i - 1][j] + in;
		}
}

int calc1(int row, int col, int left, int right)
{
	int ret = 0, r = row + left - 1;

	for (int c = 1; c <= col; c++)
	{
		ret += arr[r][c];
		if (c >= col - left)
			r--;
	}

	return ret;
}

int calc2(int row, int col, int left, int right)
{
	int ret = 0, r = row;

	for (int c = col + 1; c <= N; c++)
	{
		ret += arr[r][c];
		if (c <= col + right)
			r++;
	}

	return ret;
}

int calc3(int row, int col, int left, int right)
{
	int ret = 0, r = row + left - 1;

	for (int c = 1; c < col - left + right; c++)
	{
		if (c >= col - left)
			r++;
		ret += arr[N][c] - arr[r][c];
	}

	return ret;
}

int calc4(int row, int col, int left, int right)
{
	int ret = 0, r = row + right;

	for (int c = N; c >= col - left + right; c--)
	{
		ret += arr[N][c] - arr[r][c];
		if (c <= col + right)
			r++;
	}

	return ret;
}

int calc5(int row, int col, int left, int right)
{
	int ret = 0, r2 = row + left, r1 = row + left - 1;

	for (int c = col - left; c <= col + right; c++)
	{
		ret += arr[r2][c] - arr[r1][c];
		if (c >= col - left + right)
			r2--;
		else
			r2++;
		if (c >= col)
			r1++;
		else
			r1--;
	}

	return ret;
}

void calcAns(int row, int col, int left, int right)
{
	sorted[0] = calc1(row, col, left, right);
	sorted[1] = calc2(row, col, left, right);
	sorted[2] = calc3(row, col, left, right);
	sorted[3] = calc4(row, col, left, right);
	sorted[4] = calc5(row, col, left, right);
	sort(sorted, sorted + 5);
	answer = min(answer, abs(sorted[4] - sorted[0]));
}

void solve()
{
	calcAns(3, 3, 1, 1);
	for (int r = 1; r <= N - 2; r++)
	{
		for (int c = 2; c <= N - 1; c++)
		{
			for (int left = 1; c - left >= 1; left++)
			{
				for (int right = 1; c + right <= N && r + left + right <= N; right++)
				{
					calcAns(r, c, left, right);
				}
			}
		}
	}
}

void output()
{
	printf("%d\n", answer);
}