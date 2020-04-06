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

void inputAndInit();
void solve();
void output();

bool calcAns1();
bool calcAns2();
bool calcAns3();
void SWAP(double& a, double& b);

int T, N, answer;
bool isAnswer;

int arr[12];
int coef[3];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

void SWAP(double& a, double& b)
{
	double t = a;
	a = b;
	b = t;
}

void inputAndInit()
{
	scanf("%d", &N);
	isAnswer = false;
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
}

bool calcAns1()
{
	if (fmod(arr[1], arr[0]) != 0)
		return false;
	coef[0] = arr[1] / arr[0];
	for (int i = 2; i < N; i++)
		if (arr[i] != coef[0] * arr[i-1])
			return false;
	answer = coef[0] * arr[N - 1];
	return true;
}

bool calcAns2()
{
	int temp1 = arr[0] * arr[2] - arr[1] * arr[1], temp2 = arr[2] * arr[2] - arr[1] * arr[3];
	if (!temp1 || fmod(temp2, temp1) != 0)
		return false;
	coef[0] = temp2 / temp1;
	if (fmod(arr[2] - arr[0] * coef[0], arr[1]) != 0)
		return false;
	coef[1] = (arr[2] - arr[0] * coef[0]) / arr[1];
	for (int i = 3; i < N; i++)
		if (arr[i] != coef[1] * arr[i - 1] + coef[0] * arr[i - 2])
			return false;
	answer = coef[1] * arr[N - 1] + coef[0] * arr[N - 2];
	return true;
}

bool calcAns3()
{
	double mat[3][4] = {
		{arr[2],arr[1],arr[0],arr[3]},
		{arr[3],arr[2],arr[1],arr[4]},
		{arr[4],arr[3],arr[2],arr[5]}
	};

	if (mat[0][0] * mat[1][1] == mat[1][0] * mat[0][1])
	{
		for (int i = 0; i < 4; i++)
			SWAP(mat[0][i], mat[2][i]);
	}

	if (mat[0][0] != 1.0)
	{
		for (int i = 1; i < 4; i++)
			mat[0][i] /= mat[0][0];
		mat[0][0] = 1.0;
	}
	if (mat[1][0] != 0.0)
	{
		for (int i = 1; i < 4; i++)
			mat[1][i] -= (mat[0][i] * mat[1][0]);
		mat[1][0] = 0.0;
	}
	if (mat[1][1] != 1.0)
	{
		for (int i = 2; i < 4; i++)
			mat[1][i] /= mat[1][1];
		mat[1][1] = 1.0;
	}
	if (mat[2][0])
	{
		for (int i = 1; i < 4; i++)
			mat[2][i] -= (mat[0][i] * mat[2][0]);
		mat[2][0] = 0.0;
	}
	if (mat[2][1])
	{
		for (int i = 2; i < 4; i++)
			mat[2][i] -= (mat[1][i] * mat[2][1]);
		mat[2][1] = 0.0;
	}
	if (mat[2][2] != 1.0)
	{
		mat[2][3] /= mat[2][2];
		mat[2][2] = 1.0;
	}
	if (mat[1][2])
	{
		mat[1][3] -= mat[1][2] * mat[2][3];
		mat[1][2] = 0.0;
	}
	if (mat[0][2])
	{
		mat[0][3] -= mat[0][2] * mat[2][3];
		mat[0][2] = 0.0;
	}
	if (mat[0][1])
	{
		mat[0][3] -= mat[0][1] * mat[1][3];
		mat[0][1] = 0.0;
	}

	for (int i = 0; i < 3; i++)
		coef[i] = (int)round(mat[i][3]);

	answer = coef[0] * arr[N - 1] + coef[1] * arr[N - 2] + coef[2] * arr[N - 3];
	return true;
}

void solve()
{
	if (!calcAns1())
		if (!calcAns2())
			calcAns3();
}

void output()
{
	printf("%d\n", answer);
}