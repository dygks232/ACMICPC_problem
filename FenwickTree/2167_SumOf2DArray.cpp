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

int R, C, K;

class BIT2D {
public:
	int lenR, lenC;
	vector<vector<int> > tree;
	BIT2D() {
		lenR = lenC = 0;
		tree.clear();
	}
	BIT2D(int r, int c) {
		lenR = r + 1;
		lenC = c + 1;
		tree = vector<vector<int> >(lenR, vector<int>(lenC));
	}
	void update(int r, int c, int val)
	{
		int cc;
		int diff = val - sum(r, c, r, c);
		while (r < lenR)
		{
			cc = c;
			while (cc < lenC)
			{
				tree[r][cc] += diff;
				cc += (cc & -cc);
			}
			r += (r & -r);
		}
	}
	int sum(int r, int c)
	{
		int ret = 0, cc;
		while (r)
		{
			cc = c;
			while (cc)
			{
				ret += tree[r][cc];
				cc -= (cc & -cc);
			}
			r -= (r & -r);
		}
		return ret;
	}
	int sum(int r1, int c1, int r2, int c2)
	{
		return sum(r2, c2) - sum(r1 - 1, c2) - sum(r2, c1 - 1) + sum(r1 - 1, c1 - 1);
	}
};

BIT2D TREE;

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
	scanf("%d %d", &R, &C);
	TREE = BIT2D(R, C);
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			scanf("%d", &in);
			TREE.update(r, c, in);
		}
	}
	scanf("%d", &K);
}

void solve()
{

}

void output()
{
	int r1, c1, r2, c2;
	while (K--)
	{
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		printf("%d\n", TREE.sum(r1, c1, r2, c2));
	}
}
