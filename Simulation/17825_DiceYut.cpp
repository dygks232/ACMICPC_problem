#if 1
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

#define BLUE1 5
#define BLUE1_LINK 21
#define BLUE2 10
#define BLUE2_LINK 29
#define BLUE3 15
#define BLUE3_LINK 36
#define END0 20
#define END1 28
#define END2 35
#define END_LINK 43
#define END_REAL 44
/*
0~END0 -> END_LINK~>END_REAL
0~BLUE1 -> BLUE1_LINK~END1 -> END_LINK~>END_REAL
0~BLUE2 -> BLUE2_LINK~END2 -> END_LINK~>END_REAL
0~BLUE3 -> BLUE3_LINK~END_LINK
*/

void inputAndInit();
void init();
void solve();
void output();
void solveAndOutput();

int fixIndex(int idx);
int fixMove(int currIdx, int move);
void game(int time, int currIdx, int idx0, int idx1, int idx2, int idx3, int tempAns);

vector<int> arr;
vector<int> boardScore;
vector<int> pos;

int answer, tempAnswer;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

int fixIndex(int idx)
{
	if (idx == END0 || idx == END1 || idx == END2)
		return END_LINK;
	else if (idx == BLUE1)
		return BLUE1_LINK;
	else if (idx == BLUE2)
		return BLUE2_LINK;
	else if (idx == BLUE3)
		return BLUE3_LINK;
	else
		return idx;
}

int fixMove(int currIdx, int move)
{
	if (currIdx + move == BLUE1)
		return BLUE1_LINK;
	else if (currIdx + move == BLUE2)
		return BLUE2_LINK;
	else if (currIdx + move == BLUE3)
		return BLUE3_LINK;

	if (BLUE1_LINK <= currIdx && currIdx <= END1)
	{
		if (currIdx + move > END1)
			return END_REAL;
		else if (currIdx + move == END1)
			return END_LINK;
	}
	else if (BLUE2_LINK <= currIdx && currIdx <= END2)
	{
		if (currIdx + move > END2)
			return END_REAL;
		else if (currIdx + move == END2)
			return END_LINK;
	}
	else if (BLUE3 < currIdx && currIdx < END0)
	{
		if (currIdx + move > END0)
			return END_REAL;
		else if (currIdx + move == END0)
			return END_LINK;
	}

	if (currIdx + move >= END_REAL)
		return END_REAL;
	return currIdx + move;
}

void game(int time, int currIdx, int idx0, int idx1, int idx2, int idx3, int tempAns)
{
	int moveIdx;
	bool impossible;
	moveIdx = fixIndex(fixMove(pos[currIdx], arr[time]));
	tempAns += boardScore[moveIdx];
	if (time == 9)
	{
		answer = max(answer, tempAns);
		return;
	}

	pos[0] = idx0;
	pos[1] = idx1;
	pos[2] = idx2;
	pos[3] = idx3;
	pos[currIdx] = moveIdx;

	for (int i = 0; i <= min(time + 1, 3); i++)
	{
		if (pos[i] == END_REAL)
			continue;

		impossible = false;
		for (int j = 0; j < 4; j++)
		{
			if (i != j && pos[j] != END_REAL && fixIndex(fixMove(pos[i], arr[time + 1])) == pos[j])
			{
				impossible = true;
				break;
			}
		}
		if (impossible)
			continue;

		game(time + 1, i, pos[0], pos[1], pos[2], pos[3], tempAns);

		pos[0] = idx0;
		pos[1] = idx1;
		pos[2] = idx2;
		pos[3] = idx3;
		pos[currIdx] = moveIdx;
	}
}

void inputAndInit()
{
	int board0[] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,10,13,16,19,25,30,35,40,20,22,24,25,30,35,40,30,28,27,26,25,30,35,40,0 };
	answer = tempAnswer = 0;
	arr.assign(10, 0);
	pos.assign(4, 0);
	for (int i = 0; i < 10; i++)
	{
		cin >> arr[i];
	}
	boardScore = vector<int>(board0, board0 + sizeof(board0) / sizeof(int));
}

void solve()
{
	game(0, 0, pos[0], pos[1], pos[2], pos[3], 0);
}

void output()
{
	printf("%d\n", answer);
}

#else
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
int dice[10];
#define END 32
//�̵� ��Ģ�� ������ �� �����Ƿ� Look-up ���̺��� ���� ����Ѵ�.
//jump[index][0] = �ش� �� ����
//jump[index][1~5] => �ֻ��� �ش� ���� ������ �̵��ϴ� �� 
int jump[33][6] = {
	{0,1,2,3,4,5}, //0���ڸ� 
	{2,2,3,4,5,9}, //1���ڸ� 
	{4,3,4,5,9,10}, //2���ڸ� 
	{6,4,5,9,10,11}, //3���ڸ� 
	{8,5,9,10,11,12},//4���ڸ� 
	{10,6,7,8,20,29},//5���ڸ� 
	{13,7,8,20,29,30}, //6���ڸ� 
	{16,8,20,29,30,31}, //7���ڸ� 
	{19,20,29,30,31,32}, //8���ڸ� 
	{12,10,11,12,13,14}, //9���ڸ� 
	{14,11,12,13,14,15}, //10���ڸ� 
	{16,12,13,14,15,16}, //11���ڸ� 
	{18,13,14,15,16,17}, //12���ڸ� 
	{20,18,19,20,29,30}, //13���ڸ� 
	{22,15,16,17,24,25}, //14���ڸ� 
	{24,16,17,24,25,26}, //15���ڸ� 
	{26,17,24,25,26,27}, //16���ڸ� 
	{28,24,25,26,27,28}, //17���ڸ� 
	{22,19,20,29,30,31}, //18���ڸ� 
	{24,20,29,30,31,32}, //19���ڸ� 
	{25,29,30,31,32,32}, //20���ڸ� 
	{26,20,29,30,31,32}, //21���ڸ� 
	{27,21,20,29,30,31}, //22���ڸ� 
	{28,22,21,20,29,30}, //23���ڸ� 
	{30,23,22,21,20,29}, //24���ڸ� 
	{32,26,27,28,31,32}, //25���ڸ� 
	{34,27,28,31,32,32}, //26���ڸ� 
	{36,28,31,32,32,32}, //27���ڸ� 
	{38,31,32,32,32,32}, //28���ڸ� 
	{30,30,31,32,32,32}, //29���ڸ� 
	{35,31,32,32,32,32}, //30���ڸ� 
	{40,32,32,32,32,32}, //31���ڸ� 
	{0,32,32,32,32,32} //32���ڸ� 
};
int ans;
void check(int bit)
{
	int score = 0;
	int occupation[35];
	int pos[4];
	memset(occupation, 0, sizeof(occupation));
	memset(pos, 0, sizeof(pos));
	occupation[0] = 4;
	for (int turn = 0; turn < 10; turn++)
	{
		//�̹��� �ű� �� 
		int horse = (bit >> (turn * 2)) & 0x3;
		//�̵��ϴ� �Ÿ� 
		int move = dice[turn];
		//���� ��ġ 
		int& current_pos = pos[horse];
		//�̵��� ��ġ 
		int next_pos = jump[current_pos][move];
		//�̹� �̵����� ���� ���� 
		int get_score = jump[next_pos][0];
		//ó���̳� �� ��ġ�� �ƴѵ� ���� ��ġ�� ��� 
		if (occupation[next_pos] > 0 && next_pos && next_pos != END)
		{
			//�Ұ����� �̵� 
			return;
		}
		else
		{
			score += get_score;
			occupation[next_pos]++;
			occupation[current_pos]--;
			current_pos = next_pos;
		}
	}
	ans = max(ans, score);
}

int main()
{
	for (int i = 0; i < 10; i++)
		cin >> dice[i];
	for (int bit = 0; bit < (1 << 20); bit++)
	{
		check(bit);
	}
	cout << ans << endl;
}

#endif