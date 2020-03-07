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

#define MAX 1000000000
#define LIMIT_PLUS 500000001
#define LIMIT_MUL 31623

void inputAndInit();
void solve();
void output();

void bfs(int num);
void divAfterBfs();

int T, input1, input2;
int flag = 0;
string answer, tempAns;

int main()
{
	inputAndInit();
	solve();
	output();
	return 0;
}

void inputAndInit()
{
	scanf("%d %d", &input1, &input2);
	answer = "";
}

void divAfterBfs(int n)
{
	switch (n)
	{
	case 1: tempAns = "/+";	break;
	case 2: tempAns = "/+*";	break;
	case 3: tempAns = "/+*+";	break;
	case 4: tempAns = "/+**";	break;
	case 5: tempAns = "/+**+";	break;
	case 6: tempAns = "/+*+*";	break;
	case 7: tempAns = "/+*+*+";	break;
	case 8: tempAns = "/+***";	break;
	case 9: tempAns = "/+***+";	break;
	case 10: tempAns = "/+**+*";	break;
	case 11: tempAns = "/+**+*+";	break;
	case 12: tempAns = "/+*+**";	break;
	case 13: tempAns = "/+*+**+";	break;
	case 14: tempAns = "/+*+*+*";	break;
	case 15: tempAns = "/+*+*+*+";	break;
	case 16: tempAns = "/+****";	break;
	case 17: tempAns = "/+****+";	break;
	case 18: tempAns = "/+***+*";	break;
	case 19: tempAns = "/+***+*+";	break;
	case 20: tempAns = "/+**+**";	break;
	case 21: tempAns = "/+**+**+";	break;
	case 22: tempAns = "/+**+*+*";	break;
	case 23: tempAns = "/+**+*+*+";	break;
	case 24: tempAns = "/+*+***";	break;
	case 25: tempAns = "/+*+***+";	break;
	case 26: tempAns = "/+*+**+*";	break;
	case 27: tempAns = "/+*+**+*+";	break;
	case 28: tempAns = "/+*+*+**";	break;
	case 29: tempAns = "/+*+*+**+";	break;
	}
}

void bfs(int num)
{
	queue<pair<int, string> > Q;
	int curr, next;
	int mulL = min(LIMIT_MUL, (int)sqrt(input2) + 1);
	int mulP = min(LIMIT_PLUS, input2 / 2 + 1);
	string currAns;
	Q.push({ num,"" });

	while (!Q.empty())
	{
		curr = Q.front().first;
		currAns = Q.front().second;
		Q.pop();

		if (curr <= mulL && curr > 1)
		{
			next = curr * curr;
			if (next == input2)
			{
				answer = currAns + "*";
				return;
			}
			Q.push({ next,currAns + "*" });
		}
		if (curr <= mulP)
		{
			next = curr + curr;
			if (next == input2)
			{
				answer = currAns + "+";
				return;
			}
			Q.push({ next,currAns + "+" });
		}
	}
}

void solve()
{
	if (input1 == input2)
		flag = 1;
	else if (input2 == 1)
		flag = 2;
	else
	{
		bfs(input1);
		double temp = log2(input2);
		if (fmod(temp, 1.0) == 0.0)
		{
			divAfterBfs(temp);
			if (answer == "" || answer.length() > tempAns.length())
				answer = tempAns;
		}
	}
}

void output()
{
	if (flag == 1)
		printf("0\n");
	else if (flag == 2)
		printf("/\n");
	else if (answer == "")
		printf("-1\n");
	else
	{
		cout << answer << "\n";
	}
}