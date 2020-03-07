//#include<iostream>
//#include<cstdio>
//#include<cstdlib>
//#include<vector>
//#include<stack>
//#include<queue>
//#include<deque>
//#include<algorithm>
//#include<cmath>
//#include<climits>
//#include<set>
//#include<map>
//#include<string>
//#include<cstring>
//#include<functional>
//using namespace std;
//
//void inputAndInit();
//void init();
//void solve();
//void output();
//void solveAndOutput();
//
//long long segTree_init(vector<long long>& arr, vector<long long>& tree, int node, int start, int end);
//void segTree_update(vector<long long>& tree, int node, int start, int end, int changeIndex, double diff);
//long long segTree_mul(vector<long long>& tree, int node, int start, int end, int left, int right);
//
//#define MODULA (long long)1000000007
//
//long long N, M, K, answer;
//
//vector<long long> input;
//vector<long long> segTree;
//
//int main()
//{
//	inputAndInit();
//	solveAndOutput();
//	//system("pause");
//	return 0;
//}
//
//long long segTree_mul(vector<long long>& tree, int node, int start, int end, int left, int right)
//{
//	if (left > end || right < start)
//		return 1;
//	if (left <= start && end <= right)
//		return tree[node];
//	int mid = (start + end) / 2;
//	return (segTree_mul(tree, node * 2 + 1, start, mid, left, right) * segTree_mul(tree, node * 2 + 2, mid + 1, end, left, right)) % MODULA;
//}
//
//void segTree_update(vector<long long>& tree, int node, int start, int end, int changeIndex, double diff)
//{
//	if (changeIndex < start || changeIndex > end)
//		return;
//
//	tree[node] = (long long)round(diff * tree[node]) % MODULA;
//
//	if (start != end)
//	{
//		int mid = (start + end) / 2;
//		segTree_update(tree, node * 2 + 1, start, mid, changeIndex, diff);
//		segTree_update(tree, node * 2 + 2, mid + 1, end, changeIndex, diff);
//	}
//}
//
//long long segTree_init(vector<long long>& arr, vector<long long>& tree, int node, int start, int end)
//{
//	if (start == end)
//		return tree[node] = arr[start];
//
//	int mid = (start + end) / 2;
//
//	return tree[node] = (segTree_init(arr, tree, node * 2 + 1, start, mid) * segTree_init(arr, tree, node * 2 + 2, mid + 1, end)) % MODULA;
//}
//
//void inputAndInit()
//{
//	int in;
//	scanf("%lld %lld %lld", &N, &M, &K);
//	//cin >> N >> M >> K;
//	answer = 1;
//	input.assign(N, 0);
//	segTree.assign(N * 4, 0);
//	for (int i = 0; i < N; i++)
//	{
//		scanf("%d", &in);
//		//cin >> in;
//		input[i] = in;
//	}
//}
//
//void solveAndOutput()
//{
//	int tag, a, b;
//	segTree_init(input, segTree, 0, 0, N - 1);
//	for (int i = 0; i < M + K; i++)
//	{
//		scanf("%d %d %d", &tag, &a, &b);
//		//cin >> tag >> a >> b;
//		if (tag == 1) {
//			if (input[a - 1])
//			{
//				segTree_update(segTree, 0, 0, N - 1, a - 1, (double)b / input[a - 1]);
//				input[a - 1] = b;
//			}
//			else
//			{
//				input[a - 1] = b;
//				segTree_init(input, segTree, 0, 0, N - 1);
//			}
//			/*for (int k = 0; k < N; k++)
//				cout << input[k] << " ";
//			cout << "\n";
//			for (int k = 0; k < 4 * N; k++)
//				cout << segTree[k] << " ";
//			cout << "\n";*/
//		}
//		else
//		{
//			answer = segTree_mul(segTree, 0, 0, N - 1, a - 1, b - 1);
//			printf("%lld\n", answer);
//		}
//	}	
//}

#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 1000000007
#define MAX_N 1000000
typedef long long ll;
using namespace std;
ll n, m, k, t, x, y, z;
ll seg[4 * MAX_N];
ll update(ll pos, ll val, ll node, ll x, ll y) {
	if (y < pos || pos < x)
		return seg[node];
	if (x == y)
		return seg[node] = val;
	ll mid = (x + y) >> 1;
	return seg[node] = (update(pos, val, node * 2, x, mid) * update(pos, val, node * 2 + 1, mid + 1, y)) % MOD;
}
ll query(ll lo, ll hi, ll node, ll x, ll y) {
	if (y < lo || hi < x)
		return 1;
	if (lo <= x && y <= hi)
		return seg[node];
	ll mid = (x + y) >> 1;
	return (query(lo, hi, node * 2, x, mid) * query(lo, hi, node * 2 + 1, mid + 1, y)) % MOD;
}
int main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &t);
		update(i, t, 1, 1, n);
	}
	for (ll i = 0; i < m + k; i++) {
		scanf("%lld%lld%lld", &x, &y, &z);
		if (x == 1)
			update(y, z, 1, 1, n);
		else
			printf("%lld\n", query(y, z, 1, 1, n));
	}
	return 0;
}
