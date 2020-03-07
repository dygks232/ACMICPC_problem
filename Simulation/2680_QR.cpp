#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<deque>
#include<vector>
#include<set>
#include<map>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<climits>
#include<functional>
using namespace std;

#define NUM 1
#define ALPHA 2
#define CHAR 4
#define KANJI 8
#define END 0

void inputAndInit();
void solve();
void output();

void mapInit();
int getMode(string &input);
int getCount(string &input, int mode);
int binToDec(const string& input);
void getNum(string &input, int cnt);
void getAlpha(string &input, int cnt);
void getChar(string &input, int cnt);
void getKanji(string &input, int cnt);
string decToHex2(int num);
string decToHex4(int num);

const string alphaTable = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";
const string hexTable = "0123456789ABCDEF";
int countBit, T;
string decode, answer;

map<char, string> hexToBin;
stack<char> st;

int main()
{
	cin >> T;
	//scanf("%d",&T);
	mapInit();
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	//system("pause");
	return 0;
}

string decToHex2(int num)
{
	string ret = "";
	ret += hexTable[num / 16];
	ret += hexTable[num % 16];
	return ret;
}

string decToHex4(int num)
{
	string ret = "";
	int h1, h2, h3, h4;
	h4 = num % 16;
	num /= 16;
	h3 = num % 16;
	num /= 16;
	h2 = num % 16;
	h1 = num / 16;
	ret += hexTable[h1];
	ret += hexTable[h2];
	ret += hexTable[h3];
	ret += hexTable[h4];
	return ret;
}

void getKanji(string &input, int cnt)
{
	string temp;
	int dec;
	for (int i = 0; i < cnt; i++)
	{
		temp = input.substr(0, 13);
		input = input.substr(13);
		dec = binToDec(temp);
		if (dec >= 0x20 && dec <= 0x7e)
			answer += dec;
		else
		{
			answer += "\#";
			answer += decToHex4(dec);
		}
	}
}

void getChar(string &input, int cnt)
{
	string temp;
	int dec;
	for (int i = 0; i < cnt; i++)
	{
		temp = input.substr(0, 8);
		input = input.substr(8);
		dec = binToDec(temp);
		if (dec >= 0x20 && dec <= 0x7e)
			answer += dec;
		else
		{
			answer += "\\";
			answer += decToHex2(dec);
		}
	}
}

void getAlpha(string &input, int cnt)
{
	string temp;
	int div, mod, dec;
	div = cnt / 2;
	mod = cnt & 1;
	while (div--)
	{
		temp = input.substr(0, 11);
		input = input.substr(11);
		dec = binToDec(temp);
		answer += alphaTable[dec / 45];
		answer += alphaTable[dec % 45];
	}
	if (mod)
	{
		temp = input.substr(0, 6);
		input = input.substr(6);
		dec = binToDec(temp);
		answer += alphaTable[dec];
	}
}

void getNum(string &input, int cnt)
{
	string temp;
	int div, mod, dec;
	div = cnt / 3;
	mod = cnt % 3;
	while (div--)
	{
		temp = input.substr(0, 10);
		input = input.substr(10);
		dec = binToDec(temp);
		for (int i = 0; i < 3; i++)
		{
			st.push((dec % 10) + '0');
			dec /= 10;
		}
		while (!st.empty()) {
			answer += st.top();
			st.pop();
		}
	}
	if (mod == 1)
	{
		temp = input.substr(0, 4);
		input = input.substr(4);
		dec = binToDec(temp);
		answer += (dec + '0');
	}
	else if (mod == 2)
	{
		temp = input.substr(0, 7);
		input = input.substr(7);
		dec = binToDec(temp);
		for (int i = 0; i < 2; i++)
		{
			st.push((dec % 10) + '0');
			dec /= 10;
		}
		while (!st.empty()) {
			answer += st.top();
			st.pop();
		}
	}
}

int binToDec(const string& input)
{
	int ret = 0;
	int len = input.length();
	for (int i = 0; i < len; i++)
	{
		ret = ret << 1;
		ret += (input[i] - '0');
	}
	return ret;
}

int getCount(string &input, int mode)
{
	string CB;
	switch (mode)
	{
	case NUM:
		CB = input.substr(0, 10);
		input = input.substr(10);
		break;
	case ALPHA:
		CB = input.substr(0, 9);
		input = input.substr(9);
		break;
	case CHAR:
	case KANJI:
		CB = input.substr(0, 8);
		input = input.substr(8);
		break;
	default:
		break;
	}
	return binToDec(CB);
}

int getMode(string &input)
{
	string sub;
	sub = input.substr(0, 4);
	input = input.substr(4);
	if (sub == "0001") return NUM;
	if (sub == "0010") return ALPHA;
	if (sub == "0100") return CHAR;
	if (sub == "1000") return KANJI;
	if (sub == "0000") return END;
	return -1;
}

void mapInit()
{
	hexToBin['0'] = "0000";
	hexToBin['1'] = "0001";
	hexToBin['2'] = "0010";
	hexToBin['3'] = "0011";
	hexToBin['4'] = "0100";
	hexToBin['5'] = "0101";
	hexToBin['6'] = "0110";
	hexToBin['7'] = "0111";
	hexToBin['8'] = "1000";
	hexToBin['9'] = "1001";
	hexToBin['A'] = "1010";
	hexToBin['B'] = "1011";
	hexToBin['C'] = "1100";
	hexToBin['D'] = "1101";
	hexToBin['E'] = "1110";
	hexToBin['F'] = "1111";
}

void inputAndInit()
{
	string in;
	cin >> in;
	decode = answer = "";
	countBit = 0;
	for (int i = 0; i < 38; i++)
	{
		decode += hexToBin[in[i]];
	}
}

void solve()
{
	int mode, cnt;
	bool end = false;
	while (decode.length() >= 4 && (mode = getMode(decode)))
	{
		switch (mode)
		{
		case NUM:
			cnt = getCount(decode, NUM);
			countBit += cnt;
			getNum(decode, cnt);
			break;
		case ALPHA:
			cnt = getCount(decode, ALPHA);
			countBit += cnt;
			getAlpha(decode, cnt);
			break;
		case CHAR:
			cnt = getCount(decode, CHAR);
			countBit += cnt;
			getChar(decode, cnt);
			break;
		case KANJI:
			cnt = getCount(decode, KANJI);
			countBit += cnt;
			getKanji(decode, cnt);
			break;
		case END:
			end = true;
			break;
		}
		if (end)
			break;
	}
}

void output()
{
	cout << countBit << " " << answer << "\n";
}
