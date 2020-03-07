#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
set<int> child[50];

int answer = 0;

void cntLeaf(int node);
void removeNode(int node, int r);

void removeNode(int node, int r)
{
	if (child[node].find(r) != child[node].end())
	{
		child[node].erase(r);
		return;
	}
	set<int>::iterator it;

	for (it = child[node].begin(); it != child[node].end(); it++)
	{
		removeNode(*it,r);
	}
}

void cntLeaf(int node)
{
	if (!child[node].size())
	{
		answer++;
		return;
	}
	set<int>::iterator it;
	for (it = child[node].begin(); it != child[node].end(); it++)
	{
		cntLeaf(*it);
	}

}

int main()
{
	int N, in, remove, root = 0;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> in;
		if (in == -1) {
			root = i;
			continue;
		}
		child[in].insert(i);
	}
	cin >> remove;
	removeNode(root, remove);
	cntLeaf(root);
	if (remove == root) answer = 0;
	cout << answer << "\n";
	return 0;
}
