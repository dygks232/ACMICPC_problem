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

#define MAX_LEN 100001

using namespace std;

int tree[MAX_LEN];

int sum(int i)
{
	int ans = 0;
	while (i > 0)
	{
		ans += tree[i];
		i -= (i & -i);
	}

	return ans;
}

void update(int i, int diff)
{
	while (i < MAX_LEN)
	{
		tree[i] += diff;
		i += (i & -i);
	}
}

int main()
{
	int n, a, b;
	int getA, getB;

	scanf("%d", &n);
	//cin >> n;

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &a, &b);
		//cin >> a >> b;

		getA = sum(a);
		getB = sum(b);

		// a부분은 모든 꽃이 피었으니 0이 되고, 
		// a + 1부분부터는 다시 복구해준다.
		update(a, -getA); 
		update(a + 1, getA);
		update(b, -getB); 
		update(b + 1, getB);

		// 새로 들어온 식물로 인해 a + 1부분부터 꽃이 필 수 있는 곳이 생긴다.
		// b부터는 꽃이 필 수 없으니 다시 -1로 빼준다.
		// 1 4일경우 1,2,3,4중 2,3에만 꽃이 필 수 있다.
		update(a + 1, 1);
		update(b, -1);

		printf("%d\n", getA + getB);
	}

	return 0;
}