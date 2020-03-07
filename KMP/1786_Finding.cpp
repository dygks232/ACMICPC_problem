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

char S[1000001];
char P[1000001];
int pl[1000001];
int i, j;
int tmp;
int S_length;
int P_length;
char buff[10];
int idx[1000001];
int cnt;


int main() {
	scanf("%[^\n]s", S);
	scanf("%c", buff);

	S_length = 0;
	for (int i = 0; S[i]; i++) {
		S_length++;
	}
	scanf("%[^\n]s", P);
	P_length = 0;
	P_length = 0;
	for (int i = 0; P[i]; i++) {
		P_length++;
	}

	pl[0] = 0;
	j = 0;
	for (int i = 1; i < P_length; i++) {
		while (P[j] != P[i] && j > 0) {
			j = pl[j - 1];
		}
		if (P[j] == P[i]) {
			pl[i] = ++j;
		}

	}
	cnt = 0; j = 0;
	for (int i = 0; i < S_length; i++) {
		while (P[j] != S[i] && j > 0) {
			j = pl[j - 1];
		}
		if (P[j] == S[i]) {
			if (j == P_length - 1) {
				idx[cnt++] = i - P_length + 2;
				j = pl[j];
			}
			else {
				j++;
			}
		}

	}
	printf("%d\n", cnt);
	for (i = 0; i < cnt; ++i) {
		printf("%d\n", idx[i]);
	}

	return 0;
}
