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

void inputAndInit();
void solve();
void output();

void program0();
void program1();
void program2();
void program3();
void program4();
void program5();
void program6();
void program7();

int T, memSize, codeSize, inputSize, memPtr, codePtr, inputPtr;
bool isEnd;

unsigned char memory[100000];
char code[4096];
char input[4096];

struct info
{
	int pair;
	bool escape;
	info() { pair = -1; escape = false; }
	info(int p) { pair = p; }
	info(int p, bool e) { pair = p; escape = e; }
};

info loopInfo[4096];

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

void inputAndInit()
{
	stack<int> temp;
	scanf("%d %d %d", &memSize, &codeSize, &inputSize);
	memset(memory, 0, sizeof(memory));
	memPtr = codePtr = inputPtr = 0;
	isEnd = false;
	scanf("%s", code);
	scanf("%s", input);
	for (int i = 0; i < codeSize; i++)
	{
		if (code[i] == '[')
			temp.push(i);
		else if (code[i] == ']')
		{
			loopInfo[temp.top()] = info(i, false);
			loopInfo[i] = info(temp.top(), false);
			temp.pop();
		}
	}
}

void program0()
{
	memory[memPtr]--;
	codePtr++;
}

void program1()
{
	memory[memPtr]++;
	codePtr++;
}

void program2()
{
	memPtr = (memPtr + memSize - 1) % memSize;
	codePtr++;
}

void program3()
{
	memPtr = (memPtr + 1) % memSize;
	codePtr++;
}

void program4()
{
	if (!memory[memPtr])
		codePtr = loopInfo[codePtr].pair;
	else
		codePtr++;
}

void program5()
{
	if (memory[memPtr])
		codePtr = loopInfo[codePtr].pair;
	else
	{
		loopInfo[codePtr].escape = true;
		loopInfo[loopInfo[codePtr].pair].escape = true;
		codePtr++;
	}
}

void program6()
{
	codePtr++;
}

void program7()
{
	if (inputPtr == inputSize)
		memory[memPtr] = 255;
	else
		memory[memPtr] = (unsigned char)input[inputPtr++];
	codePtr++;
}

void solve()
{
	for (int a = 0; a < 50000000; a++)
	{
		if (codePtr == codeSize)
		{
			isEnd = true;
			break;
		}
		switch (code[codePtr])
		{
		case '-':
			program0(); break;
		case '+':
			program1(); break;
		case '<':
			program2(); break;
		case '>':
			program3(); break;
		case '[':
			program4(); break;
		case ']':
			program5(); break;
		case '.':
			program6(); break;
		case ',':
			program7(); break;
		}
	}
}

void output()
{
	if (isEnd)
		printf("Terminates\n");
	else
	{
		for (int i = codePtr; i < codeSize; i++)
		{
			if (code[i] == '[')
			{
				if (i != codePtr)
					i = loopInfo[i].pair;
				else
					i = loopInfo[i].pair - 1;
			}
			else if (code[i] == ']' && !loopInfo[i].escape)
			{
				printf("Loops %d %d\n", loopInfo[i].pair, i);
				break;
			}
		}
	}
}