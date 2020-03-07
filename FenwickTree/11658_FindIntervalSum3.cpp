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

void updateTree(int x, int y, int diff);
int sumTree(int x, int y);
void SWAP(int& a, int& b);

int N, M, answer, len;
//vector<vector<int> > tree;
int tree[1025][1025] = { 0, };

int main()
{
	int in, x1, y1, x2, y2, r;
	//cin >> N >> M;
	scanf("%d %d", &N, &M);
	len = N + 1;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			//cin >> in;
			scanf("%d", &in);
			updateTree(i, j, in - (sumTree(i, j) - sumTree(i - 1, j) - sumTree(i, j - 1) + sumTree(i - 1, j - 1)));
		}
	}
	for (int i = 0; i < M; i++)
	{
		//cin >> in;
		scanf("%d", &in);
		if (in)
		{
			//cin >> x1 >> y1 >> x2 >> y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			printf("%d\n", sumTree(x2, y2) - sumTree(x1 - 1, y2) - sumTree(x2, y1 - 1) + sumTree(x1 - 1, y1 - 1));
		}
		else
		{
			//cin >> x1 >> y1 >> r;
			scanf("%d %d %d", &x1, &y1, &r);
			updateTree(x1, y1, r - (sumTree(x1, y1) - sumTree(x1 - 1, y1) - sumTree(x1, y1 - 1) + sumTree(x1 - 1, y1 - 1)));
		}
	}
	return 0;
}

void SWAP(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void updateTree(int x, int y, int diff)
{
	int yy;
	while (x < len)
	{
		yy = y;
		while (yy < len)
		{
			tree[x][yy] += diff;
			yy += (yy & -yy);
		}
		x += (x & -x);
	}
}

int sumTree(int x, int y)
{
	int ret = 0, yy;
	while (x)
	{
		yy = y;
		while (yy)
		{
			ret += tree[x][yy];
			yy -= (yy & -yy);
		}
		x -= (x & -x);
	}
	return ret;
}