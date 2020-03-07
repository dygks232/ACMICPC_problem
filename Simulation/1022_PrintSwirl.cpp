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

int calcAnswer(int r, int c);
int calcDigit(int n);

int R1, C1, R2, C2, answer;

int arr[5001];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	cin >> R1 >> C1 >> R2 >> C2;
	arr[0] = 1;
	arr[1] = 2;
	for (int i = 2; i <= 5000; i++)
		arr[i] = arr[i - 1] + 8 * (i - 1);
}

void solve()
{

}

int calcDigit(int n)
{
	int ret = 1;
	while ((n /= 10))
		ret++;
	return ret;
}

int calcAnswer(int r, int c)
{
	int idx, orgR, orgC, tempR, tempC, tempV;
	if (r == 0 && c == 0)
		return arr[0];

	idx = max(abs(r), abs(c));
	orgR = idx - 1;
	orgC = idx;
	if (r - orgR <= c - orgC)
		return arr[idx] + orgR - r + orgC - c;

	tempC = idx << 1;
	tempC = ~tempC + 1;
	tempR = tempC + 1;
	tempV = arr[idx] - tempR - tempC;
	return tempV + r - orgR - tempR + c - orgC - tempC;
}

void output()
{
	int currDigit, maxDigit = calcDigit(calcAnswer(R1, C1));
	maxDigit = max(maxDigit, calcDigit(calcAnswer(R1, C2)));
	maxDigit = max(maxDigit, calcDigit(calcAnswer(R2, C1)));
	maxDigit = max(maxDigit, calcDigit(calcAnswer(R2, C2)));
	for (int r = R1; r <= R2; r++)
	{
		for (int c = C1; c <= C2; c++)
		{
			answer = calcAnswer(r, c);
			currDigit = calcDigit(answer);
			for (int i = 0; i < maxDigit - currDigit; i++)
				printf(" ");
			printf("%d ", answer);
		}
		printf("\n");
	}
}
