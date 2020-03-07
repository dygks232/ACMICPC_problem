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

int N, Q, num;

class BIT2D_1 {
public:
	int len;
	vector<vector<int> > tree;
	BIT2D_1(int n) {
		len = n + 1;
		tree = vector<vector<int> >(len, vector<int>(len));
	}
	void update(int r, int c, int diff)
	{
		int cc;
		r += N + 1;
		c += N + 1;
		if (r < 1) r = 1;
		if (c < 1) c = 1;
		while (r < len)
		{
			cc = c;
			while (cc < len)
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
		r += N + 1;
		c += N + 1;
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

class BIT2D_2 {
public:
	int lenR, lenC;
	vector<vector<int> > tree;
	BIT2D_2(int n) {
		lenR = n + 1;
		lenC = n + n;
		tree = vector<vector<int> >(lenR, vector<int>(lenC));
	}
	void update(int r, int c, int diff)
	{
		int cc, temp = c;
		c = N + N + r - c + 1;
		r = temp + N + 1;
		if (r < 1) r = 1;
		if (c < 1) c = 1;
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
		int ret = 0, cc, temp = c;
		c = N + N + r - c + 1;
		r = temp + N + 1;
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

int main()
{
	int in, r, c, d;
	//cin >> N >> Q;
	scanf("%d %d", &N, &Q);
	num = N + N + 1;
	BIT2D_1 tree1(num);
	BIT2D_2 tree2(num);
	for (int i = 0; i < Q; i++)
	{
		//cin >> in;
		scanf("%d", &in);
		if (in - 1)
		{
			//cin >> r >> c;
			scanf("%d %d", &r, &c);
			printf("%d\n", tree1.sum(r, c) + tree2.sum(r, c));
		}
		else
		{
			//cin >> r >> c >> d;
			scanf("%d %d %d", &r, &c, &d);

			tree1.update(r - d, c - d, 1);
			tree1.update(r - d, c + 1, -1);
			tree2.update(r + 1, c - d, -1);
			tree2.update(r + d + 2, c + 1, 1);

			tree2.update(r - d + 1, c + 1, 1);
			tree2.update(r + 1, c + d + 1, -1);
			tree1.update(r + d + 1, c + 1, -1);
			tree1.update(r + d + 1, c + d + 1, 1);
		}
	}
	return 0;
}
