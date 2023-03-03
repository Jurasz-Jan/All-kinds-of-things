#include <bits/stdc++.h>
#define MAX 101
using namespace std;
int n, X[MAX], Y[MAX];
double cost[MAX][MAX];
bool v[MAX];
double ans = 1e9;
vector<int> path;

double dist(int i, int j) {
    double x1 = X[i], x2 = X[j], y1 = Y[i], y2 = Y[j];
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

void createCostMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) cost[i][j] = 0;
            else cost[i][j] = dist(i, j);
        }
    }
}

void tsp(int u, double c) {
    if (path.size() == n) {
        ans = min(ans, c + cost[u][0]);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (!v[i]) {
            v[i] = true;
            path.push_back(i);
            tsp(i, c + cost[u][i]);
            v[i] = false;
            path.pop_back();
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        X[i] = x;
        Y[i] = y;
    }
    createCostMatrix();
    path.push_back(0);
    v[0] = true;
    tsp(0, 0);
    //cout << ans << endl;
    for (int i = 0; i < n; i++) {
        cout << X[path[i]] << " " << Y[path[i]] << endl;
    }
    return 0;
}
