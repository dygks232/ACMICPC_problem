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

struct pos {
	int row;
	int col;
	pos() {
		row = col = 0;
	}
	pos(int r, int c) {
		row = r; col = c;
	}
};

struct edgeInfo {
	int start;
	int end;
	int weight;
	edgeInfo() {
		start = end = weight = 0;
	}
	edgeInfo(int s, int e, int w) {
		start = s; end = e; weight = w;
	}
};

void inputAndInit();
void init();
void solve();
void output();
void solveAndOutput();

void divideIsland();
void makeIsland(int r, int c, int idx);
bool isOutOfRange(int r, int c);
void makeEdge(int islandIdx);
void refreshEdge(int start, int end, int weight);

void MST_kruskal();
bool compare(edgeInfo e1, edgeInfo e2);
int find(int u);
void merge(int u, int v);

int R, C, answer, numV, numE;
bool check;

int dirR[4] = { -1,1,0,0 };
int dirC[4] = { 0,0,-1,1 };

vector<vector<int> > input;
vector<vector<bool> > visit;
vector<pos> land; // 땅들의 집합
vector<set<int> > island; // island[0] : 0번 섬을 이루는 땅들의 집합
vector<edgeInfo> edge;

vector<int> parent;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool compare(edgeInfo e1, edgeInfo e2)
{
	return e1.weight < e2.weight;
}

void MST_kruskal()
{
	int linkNum = 0;
	sort(edge.begin(), edge.end(), compare);
	numE = edge.size();
	parent.assign(numV, 0);
	for (int i = 1; i < numV; i++)
		parent[i] = i;
	for (int i = 0; i < numE; i++)
	{
		merge(edge[i].start, edge[i].end);
		if (check)
		{
			linkNum++;
			answer += edge[i].weight;
		}
	}
	if (linkNum < numV - 1)
		answer = -1;
}

int find(int u)
{
	if (u == parent[u])
		return u;
	return parent[u] = find(parent[u]);
}

void merge(int u, int v)
{
	check = false;
	u = find(u);
	v = find(v);

	// 사이클 존재 여부 확인
	if (u == v)
		return;

	parent[u] = v;
	check = true;
}

void refreshEdge(int start, int end, int weight)
{
	bool found = false;
	for (int i = 0; i < edge.size(); i++)
	{
		if (edge[i].start == start && edge[i].end == end)
		{
			found = true;
			if (edge[i].weight > weight)
				edge[i].weight = weight;
			break;
		}
	}
	if (!found)
		edge.push_back(edgeInfo(start, end, weight));
}

void makeEdge(int islandIdx)
{
	set<int>::iterator it;
	int currR, currC, nextR, nextC, len;
	for (it = island[islandIdx].begin(); it != island[islandIdx].end(); it++)
	{
		currR = (*it) / 10;
		currC = (*it) % 10;

		for (int dir = 0; dir < 4; dir++)
		{
			len = 0;
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];

			while (!isOutOfRange(nextR, nextC))
			{
				if (input[nextR][nextC])
				{
					if (len < 2)
						break;
					else
					{
						for (int i = 0; i < numV; i++)
						{
							if (island[i].find(nextR * 10 + nextC) != island[i].end())
							{
								refreshEdge(min(islandIdx, i), max(islandIdx, i), len);
								break;
							}
						}
						break;
					}
				}
				else
					len++;

				nextR += dirR[dir];
				nextC += dirC[dir];
			}
		}
	}
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

void makeIsland(int r, int c, int idx)
{
	int nextR, nextC;
	visit[r][c] = true;
	island[idx].insert(r * 10 + c);
	for (int dir = 0; dir < 4; dir++)
	{
		nextR = r + dirR[dir];
		nextC = c + dirC[dir];
		if (isOutOfRange(nextR, nextC) || !input[nextR][nextC])
			continue;
		if (!visit[nextR][nextC])
		{
			makeIsland(nextR, nextC, idx);
		}
	}
}

void divideIsland()
{
	int landSize = land.size(), islandIdx = 0;
	for (int i = 0; i < landSize; i++)
	{
		if (!visit[land[i].row][land[i].col])
		{
			island.push_back(set<int>());
			makeIsland(land[i].row, land[i].col, islandIdx);
			islandIdx++;
		}
	}
	numV = islandIdx;
}

void inputAndInit()
{
	cin >> R >> C;
	numV = numE = answer = 0;
	input.assign(R, vector<int>(C, 0));
	visit.assign(R, vector<bool>(C, false));
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++)
		{
			cin >> input[i][j];
			if (input[i][j])
				land.push_back(pos(i, j));
		}
}

void solve()
{
	divideIsland();
	for (int i = 0; i < numV - 1; i++)
		makeEdge(i);
	MST_kruskal();
}

void output()
{
	cout << answer << "\n";
}
