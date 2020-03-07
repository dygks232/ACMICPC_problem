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

int main()
{
	int T, R;
	char c;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &R);
		getchar();
		while (1)
		{
			scanf("%c", &c);
			if (c == '\0' || c == '\n' || c == '\r') break;
			if (c != '\\' && c != '%')
			{
				for (int i = 0; i < R; i++)
					printf("%c", c);
			}
			else if(c == '\\')
				for (int i = 0; i < R; i++)
					printf("\\", c);
			else
				for (int i = 0; i < R; i++)
					printf("%%", c);
		}
		printf("\n");
	}
	return 0;
}