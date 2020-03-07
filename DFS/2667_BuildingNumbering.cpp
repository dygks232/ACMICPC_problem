#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<cstdio>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<climits>

using namespace std;

void input();
void output();
void solveDFS();
void dfs(int nCurIndex);
void solveBFS();
void bfs(int nCurIndex);
void addQ(int nCurIndex);

int nInputLen, nSize, nOutputClusterNum;

vector<int> nVecInputMap;
vector<int> nVecHomeIndex;
vector<pair<int, bool>> nbVecClusteringVisit;
vector<int> nVecClusterSize;

int main()
{
	input();
	solveBFS();
	output();
	return 0;
}

void input()
{
	int nTemp;
	cin >> nInputLen;
	nSize = nInputLen * nInputLen;
	getchar();
	for (int i = 0; i < nSize; i++)
	{
		nTemp = getchar() - '0';
		nVecInputMap.push_back(nTemp);
		if (nTemp) {
			nVecHomeIndex.push_back(i);
			nbVecClusteringVisit.push_back(make_pair(0, false));
		}
		else {
			nbVecClusteringVisit.push_back(make_pair(-1, false));
		}
		if (i % nInputLen == nInputLen - 1)
			getchar();
	}
}

void output()
{
	cout << nOutputClusterNum << "\n";
	for (int i = 0; i < nOutputClusterNum; i++)
	{
		cout << nVecClusterSize[i] << "\n";
	}
}

void solveDFS()
{
	int nHomeNum;
	nHomeNum = nVecHomeIndex.size();
	nOutputClusterNum = 0;

	for (int i = 0; i < nHomeNum; i++)
	{
		if (nbVecClusteringVisit[nVecHomeIndex[i]].first == 0) {
			nOutputClusterNum++;
			dfs(nVecHomeIndex[i]);
		}
	}

	nVecClusterSize.assign(nOutputClusterNum, 0);
	for (int i = 0; i < nSize; i++)
	{
		if (nbVecClusteringVisit[i].first > 0)
			nVecClusterSize[nbVecClusteringVisit[i].first - 1]++;
	}
	sort(nVecClusterSize.begin(), nVecClusterSize.begin() + nOutputClusterNum);
}

void dfs(int nCurIndex)
{
	int nCurRow, nCurCol, nNextRow, nNextCol, nNextIndex;
	nCurRow = nCurIndex / nInputLen;
	nCurCol = nCurIndex % nInputLen;
	int nDirRow[4] = { -1,0,1,0 };
	int nDirCol[4] = { 0,-1,0,1 };

	nbVecClusteringVisit[nCurIndex] = make_pair(nOutputClusterNum, true);

	//for (int i = 0; i < nSize; i++)
	//{
	//	if (nbVecClusteringVisit[i].first > 0) {
	//		printf("%2d ", nbVecClusteringVisit[i].first);
	//	}
	//	else if (nbVecClusteringVisit[i].first == 0) cout << "00 ";
	//	else cout << nbVecClusteringVisit[i].first << " ";

	//	if (i % nInputLen == nInputLen - 1)
	//		cout << "\n";
	//}
	//cout << endl;


	for (int i = 0; i < 4; i++)
	{
		nNextRow = nCurRow + nDirRow[i];
		nNextCol = nCurCol + nDirCol[i];
		if (nNextRow < 0 || nNextCol < 0 || nNextRow >= nInputLen || nNextCol >= nInputLen)
			continue;
		nNextIndex = nNextRow * nInputLen + nNextCol;

		if (nbVecClusteringVisit[nNextIndex].second == false && nbVecClusteringVisit[nNextIndex].first == 0)
			dfs(nNextIndex);
	}
}


////////////////

queue<int> quTest;


void addQ(int nCurIndex)
{
	int nCurRow, nCurCol, nNextIndex, nNextRow, nNextCol;
	int nDirRow[4] = { -1,0,1,0 };
	int nDirCol[4] = { 0,-1,0,1 };

	quTest.push(nCurIndex);
	nbVecClusteringVisit[nCurIndex] = make_pair(nOutputClusterNum, true);


	/*for (int i = 0; i < nSize; i++)
	{
		if (nbVecClusteringVisit[i].first > 0) {
			printf("%2d ", nbVecClusteringVisit[i].first);
		}
		else if (nbVecClusteringVisit[i].first == 0) cout << "00 ";
		else cout << nbVecClusteringVisit[i].first << " ";

		if (i % nInputLen == nInputLen - 1)
			cout << "\n";
	}
	cout << endl;*/

	while (!quTest.empty())
	{
		nCurIndex = quTest.front();
		nCurRow = nCurIndex / nInputLen;
		nCurCol = nCurIndex % nInputLen;

		quTest.pop();

		for (int i = 0; i < 4; i++)
		{
			nNextRow = nCurRow + nDirRow[i];
			nNextCol = nCurCol + nDirCol[i];

			if (nNextRow < 0 || nNextCol < 0 || nNextRow >= nInputLen || nNextCol >= nInputLen)
				continue;
			nNextIndex = nNextRow * nInputLen + nNextCol;
			
			if (nbVecClusteringVisit[nNextIndex].second == false && nbVecClusteringVisit[nNextIndex].first == 0) {
				addQ(nNextIndex);
			}
		}
	}
}

void solveBFS()
{
	int nHomeNum;
	nHomeNum = nVecHomeIndex.size();
	nOutputClusterNum = 0;

	
	for (int i = 0; i < nSize; i++)
	{
		if (nbVecClusteringVisit[i].first == 0 && nbVecClusteringVisit[i].second == false) {
			nOutputClusterNum++;
			addQ(i);
		}
	}

	nVecClusterSize.assign(nOutputClusterNum, 0);
	for (int i = 0; i < nSize; i++)
	{
		if (nbVecClusteringVisit[i].first > 0)
			nVecClusterSize[nbVecClusteringVisit[i].first - 1]++;
	}
	sort(nVecClusterSize.begin(), nVecClusterSize.begin() + nOutputClusterNum);
}

void bfs(int nCurIndex)
{
}
