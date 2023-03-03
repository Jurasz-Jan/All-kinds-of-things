#include <iostream>

using namespace std;

// there are four nodes in example graph (graph is 1-based)
const int MAX = 1000000;

int dist[20][20];
int memo[20][1<<20];
int n;

int fun(int i, int mask)
{
if (mask == ((1 << i) | ((1 << n) - 1)))
return dist[0][i];
if (memo[i][mask] != 0)
return memo[i][mask];
int res = MAX;

for (int j = 1; j < n; j++)
	if ((mask & (1 << j)) && j != i)
		res = min(res, fun(j, mask & (~(1 << i))) + dist[j][i]);
return memo[i][mask] = res;
}

int main()
{
cin >> n;
for (int i = 0; i < n; i++)
for (int j = 0; j < n; j++)
cin >> dist[i][j];
int ans = MAX;
for (int i = 1; i < n; i++)
ans = min(ans, fun(i, (1 << n) - 1) + dist[i][0]);
cout << ans << endl;
return 0;
}