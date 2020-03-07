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

void makeAnswer(int curr, int index);

#define LOTTO 6

int K;

vector<int> S;
vector<int> answer;

int main()
{
	while (1)
	{
		cin >> K;
		if (!K)
			break;
		S.clear();
		S.assign(K, 0);
		answer.assign(LOTTO, 0);
		for (int i = 0; i < K; i++)
			cin >> S[i];

		for (int i = 0; i < K; i++)
		{
			if (i + LOTTO <= K)
				makeAnswer(i, 0);
			else
				break;
		}

		cout << "\n";
	}
	return 0;
}

void makeAnswer(int curr, int index)
{
	if (curr + LOTTO - index > K)
		return;

	answer[index] = S[curr];
	if (index == LOTTO - 1)
	{
		for (int i = 0; i < LOTTO; i++)
			cout << answer[i] << " ";
		cout << "\n";
		return;
	}
	
	for (int i = curr + 1; i < K; i++)
	{
		makeAnswer(i, index + 1);
	}
}