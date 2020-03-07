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
using namespace std;

void inputAndInit();
void init();
void solve();
void output();

int T, G, L;
unsigned int AB, answer;

void calcPrime();
void factorization(int ar[]);
int calcG();

vector<int> prime;
map<int, int> divisor[2];
int number[2];

int main()
{
	calcPrime();
	cin >> T;
	while (T--)
	{
		inputAndInit();
		solve();
		output();
	}
	return 0;
}

int calcG()
{
	int ret = 1;
	map<int, int>::iterator it, found;
	for (it = divisor[0].begin(); it != divisor[0].end(); it++)
	{
		found = divisor[1].find(it->first);
		if (found != divisor[1].end())
		{
			ret *= pow((it->first), min(it->second, found->second));
		}
	}
	return ret;
}

void factorization(int ar[])
{
	int size = prime.size();
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < size; i++)
		{
			if (ar[k] % prime[i] == 0)
			{
				if (divisor[k].find(prime[i]) != divisor[k].end())
				{
					divisor[k][prime[i]]++;
				}
				else
				{
					divisor[k][prime[i]] = 1;
				}
				ar[k] /= prime[i];
				i--;
			}
		}
		if (ar[k] > prime[size - 1])
			divisor[k][ar[k]] = 1;
	}
}

void calcPrime()
{
	int range = sqrt(45000) + 1;
	bool isPrime = true;
	int size = prime.size();
	for (int i = 2; i <= range; i++)
	{
		isPrime = true;
		for (int j = 0; j < size; j++)
		{
			if (i % prime[j] == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime)
		{
			prime.push_back(i);
			size++;
		}
	}
}

void inputAndInit()
{
	cin >> number[0] >> number[1];
	AB = number[0] * number[1];
	divisor[0].clear();
	divisor[1].clear();
}

void solve()
{
	factorization(number);
	G = calcG();
	answer = AB / G;
}

void output()
{
	cout << answer << "\n";
}
