#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<cmath>
#include<climits>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int nInputNumberNum, nInputAddNum, nInputSubNum, nInputMulNum, nInputDivNum;

vector<int> nVecNumber;

vector<int> nVecOperationPermutation;

int main()
{
	int nTemp, nResult;
	int nOutputMax = INT_MIN, nOutputMin = INT_MAX;
	cin >> nInputNumberNum;
	for (int i = 0; i < nInputNumberNum; i++)
	{
		cin >> nTemp;
		nVecNumber.push_back(nTemp);
	}
	cin >> nInputAddNum >> nInputSubNum >> nInputMulNum >> nInputDivNum;

	for (int i = 0; i < nInputNumberNum - 1; i++)
	{
		if (i < nInputAddNum)
			nVecOperationPermutation.push_back(0);
		else if (i < nInputAddNum + nInputSubNum)
			nVecOperationPermutation.push_back(1);
		else if (i < nInputAddNum + nInputSubNum + nInputMulNum)
			nVecOperationPermutation.push_back(2);
		else
			nVecOperationPermutation.push_back(3);
	}

	do
	{
		nResult = nVecNumber[0];
		for (int i = 0; i < nInputNumberNum - 1; i++)
		{
			switch (nVecOperationPermutation[i])
			{
			case 0: nResult += nVecNumber[i + 1]; break;
			case 1: nResult -= nVecNumber[i + 1]; break;
			case 2: nResult *= nVecNumber[i + 1]; break;
			default:
				if (nResult < 0) {
					nResult *= -1;
					nResult /= nVecNumber[i + 1];
					nResult *= -1;
				}
				else
					nResult /= nVecNumber[i + 1];
				break;
			}
		}
		nOutputMax = max(nOutputMax, nResult);
		nOutputMin = min(nOutputMin, nResult);
	} while (next_permutation(nVecOperationPermutation.begin(), nVecOperationPermutation.end()));

	cout << nOutputMax << "\n" << nOutputMin << "\n";

	return 0;
}