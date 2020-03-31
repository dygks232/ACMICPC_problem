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

#define MAXN 1000
#define MAXN2 1000000
#define BLANK 0
#define ME 1
#define COM 2

void inputAndInit();
void solve();
void output();

bool isOutOfRange(int r, int c);
void bfs(int r, int c);
bool comp(int a, int b);

int R, C, answer, targetCnt;

int board[MAXN][MAXN];
bool visit[MAXN][MAXN];
bool isTarget[MAXN2];
bool use[MAXN2];
int targetIdx[MAXN2];
pair<int, int> comPos[MAXN2];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

struct _target {
	int num;
	int score;
	int alpha;
	int total;
	pair<int, int> info[4]; // {score, additionalPos}
	_target() {
		num = score = alpha = total = 0;
		memset(info, -1, sizeof(info));
	}
	void insert(int s, int a)
	{
		info[(this->num)++] = { s,a };
		if (a != -1)
			this->alpha += s;
		else
			this->score += s;
		this->total += s;
	}
};
_target target[MAXN2];

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

bool isOutOfRange(int r, int c)
{
	return r < 0 || r >= R || c < 0 || c >= C;
}

void inputAndInit()
{
	int idx = 0;
	scanf("%d %d", &R, &C);
	answer = targetCnt = 0;
	memset(visit, false, sizeof(visit));
	memset(comPos, -1, sizeof(comPos));
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
		{
			scanf("%d", &board[r][c]);
			if (board[r][c] == COM)
				comPos[idx++] = { r,c };
		}
}

void bfs(int r, int c)
{
	queue<pair<int, int> > Q;
	int myPos[2];
	int idx = 0, currR, currC, nextR, nextC, clusterNum = 1, targetPos;
	bool isNotAnswer = false;
	Q.push({ r,c });
	visit[r][c] = true;

	while (!Q.empty())
	{
		currR = Q.front().first;
		currC = Q.front().second;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC])
				continue;
			if (board[nextR][nextC] == BLANK)
			{
				targetPos = nextR * C + nextC;
				if (!use[targetPos])
				{
					if (idx >= 2)
						isNotAnswer = true;
					else
					{
						myPos[idx++] = targetPos;
						use[targetPos] = true;
					}
				}
			}
			else if (board[nextR][nextC] == COM)
			{
				visit[nextR][nextC] = true;
				clusterNum++;
				Q.push({ nextR,nextC });
			}
		}
	}

	for (int i = 0; i < idx; i++)
		use[myPos[i]] = false;

	if (isNotAnswer)
		return;

	if (idx == 1)
	{
		target[myPos[0]].insert(clusterNum, -1);
		if (!isTarget[myPos[0]])
		{
			isTarget[myPos[0]] = true;
			targetIdx[targetCnt++] = myPos[0];
		}
	}
	else if (idx == 2)
	{
		target[myPos[0]].insert(clusterNum, myPos[1]);
		target[myPos[1]].insert(clusterNum, myPos[0]);
		if (!isTarget[myPos[0]])
		{
			isTarget[myPos[0]] = true;
			targetIdx[targetCnt++] = myPos[0];
		}
		if (!isTarget[myPos[1]])
		{
			isTarget[myPos[1]] = true;
			targetIdx[targetCnt++] = myPos[1];
		}
	}
}

bool comp(int a, int b)
{
	if (target[a].score > target[b].score)
		return true;
	return false;
}

void solve()
{
	int idx = 0, targetIdx1, targetIdx2, temp = 0;
	map<int, int> test;
	map<int, int>::iterator it;
	while (comPos[idx].first >= 0)
	{
		if (visit[comPos[idx].first][comPos[idx].second])
		{
			idx++;
			continue;
		}
		bfs(comPos[idx].first, comPos[idx].second);
		idx++;
	}

	if (targetCnt >= 2)
	{
		// score 내림차순정렬 -> 앞의 2개의 score의 합	... (1)
		// 2개 모두 둬야 점수얻는 쌍 중, score1 + score2 + alpha 의 최대값	... (2)
		// (1)과 (2)중 큰값이 정답

		sort(targetIdx, targetIdx + targetCnt, comp);
		answer = target[targetIdx[0]].score + target[targetIdx[1]].score;
		for (int i = 0; i < targetCnt; i++)
		{
			test.clear();
			// 동일한 짝이 여러개 있을 경우, alpha값 누적
			// 양쪽 score 합 + 누적 alpha
			for (int j = 0; j < target[targetIdx[i]].num; j++)
			{
				if (target[targetIdx[i]].info[j].second != -1)
				{
					if (test.find(target[targetIdx[i]].info[j].second) == test.end())
						test[target[targetIdx[i]].info[j].second] = target[targetIdx[i]].info[j].first;
					else
						test[target[targetIdx[i]].info[j].second] += target[targetIdx[i]].info[j].first;
				}
			}
			for (it = test.begin(); it != test.end(); it++)
			{
				answer = max(answer, target[targetIdx[i]].score + target[it->first].score + it->second);
			}
		}
	}
	else if (targetCnt)
	{
		idx = targetIdx[0];
		answer = target[targetIdx[0]].score;
	}
}

void output()
{
	printf("%d\n", answer);
}