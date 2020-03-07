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

#define BYTE unsigned char
#define INSTRUCTION_NUM 32

void inputAndInit();
void init();
void solve();
void output();
void solveAndOutput();

void (*program[8])(BYTE x);
void program0(BYTE x);
void program1(BYTE x);
void program2(BYTE x);
void program3(BYTE x);
void program4(BYTE x);
void program5(BYTE x);
void program6(BYTE x);
void program7(BYTE x);

BYTE instruction(string str);
string answer();

BYTE pc, adder;

vector<BYTE> memory;

int main()
{
	inputAndInit();
	return 0;
}

void program0(BYTE x)
{
	memory[x] = adder;
}

void program1(BYTE x)
{
	adder = memory[x];
}

void program2(BYTE x)
{
	if (!adder)
		pc = x;
}

void program3(BYTE x)
{
	return;
}

void program4(BYTE x)
{
	adder--;
}

void program5(BYTE x)
{
	adder++;
}

void program6(BYTE x)
{
	pc = x;
}

void program7(BYTE x)
{
	return;
}

string answer()
{
	string ret(8, '0');
	int iter = 1;
	while (adder)
	{
		ret[8 - iter] = (adder % 2) + '0';
		adder /= 2;
		iter++;
	}
	return ret;
}

BYTE instruction(string str)
{
	BYTE ret = 0;
	char c;
	for (int i = 0; i < 8; i++)
	{
		c = str[i];
		ret += (c - '0') << (7 - i);
	}
	return ret;
}

void inputAndInit()
{
	string in(8,'0');
	char c;
	int i = 0, idx = 0;;
	memory.assign(INSTRUCTION_NUM, 0);
	program[0] = program0;
	program[1] = program1;
	program[2] = program2;
	program[3] = program3;
	program[4] = program4;
	program[5] = program5;
	program[6] = program6;
	program[7] = program7;

	while(scanf("%c",&c) != EOF)
	{
		if (c >= '0' && c <= '1')
		{
			in[idx++] = c;
		}
		else if (c == '\n' || c == '\r')
		{
			memory[i++] = instruction(in);
			idx = 0;
		}
		if (i == INSTRUCTION_NUM)
		{
			pc = 0;
			adder = 0;
			solve();
			output();
			i = 0;
		}
	}
}

void solve()
{
	BYTE instructionIdx = 0;
	BYTE operand;
	while (instructionIdx != 7)
	{
		instructionIdx = memory[pc] / 32;
		operand = memory[pc] % 32;
		pc = (pc + 1) % 32;
		program[instructionIdx](operand);
	}
}

void output()
{
	cout << answer() << "\n";
}