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

int N, Q;

map<int, string> map1;
map<string, int> map2;

int main()
{
	inputAndInit();
	output();
	return 0;
}

void inputAndInit()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	string in;
	cin >> N >> Q;
	for (int i = 1; i <= N; i++)
	{
		cin >> in;
		map1[i] = in;
		map2[in] = i;
	}
}

void output()
{
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	string in;
	for (int i = 0; i < Q; i++)
	{
		cin >> in;
		if (in[0] >= '0' && in[0] <= '9')
		{
			cout << map1[stoi(in)] << "\n";
		}
		else
		{
			cout << map2[in] << "\n";
		}
	}

}
