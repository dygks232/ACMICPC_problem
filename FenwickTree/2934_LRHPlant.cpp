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

		// a�κ��� ��� ���� �Ǿ����� 0�� �ǰ�, 
		// a + 1�κк��ʹ� �ٽ� �������ش�.
		update(a, -getA); 
		update(a + 1, getA);
		update(b, -getB); 
		update(b + 1, getB);

		// ���� ���� �Ĺ��� ���� a + 1�κк��� ���� �� �� �ִ� ���� �����.
		// b���ʹ� ���� �� �� ������ �ٽ� -1�� ���ش�.
		// 1 4�ϰ�� 1,2,3,4�� 2,3���� ���� �� �� �ִ�.
		update(a + 1, 1);
		update(b, -1);

		printf("%d\n", getA + getB);
	}

	return 0;
}