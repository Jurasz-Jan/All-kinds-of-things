#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int M = 10005;
const int maxn = 1e9;

int n, a[N];
pair<double, double> points[N];
double dist[N][N], ans = maxn;

void init() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> points[i].first >> points[i].second;
        for (int j = 1; j <= n; j++) {
            dist[i][j] = (i == j) ? 0 : maxn;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double x = points[i].first - points[j].first;
            double y = points[i].second - points[j].second;
            dist[i][j] = dist[j][i] = sqrt(x * x + y * y);
        }
    }
}

double calc(int x[]) {
    double sum = 0;
    for (int i = 2; i <= n; i++) {
        sum += dist[x[i - 1]][x[i]];
    }
    return sum;
}

int main() {
    init();
    for (int i = 1; i <= n; i++) {
        a[i] = i;
    }
    do {
        double cur = calc(a);
        if (cur < ans) {
            ans = cur;
            cout << "Trasa: ";
            for (int i = 1; i <= n; i++) {
                cout << "(" << points[a[i]].first << ", " << points[a[i]].second << ") ";
            }
            cout << endl << "Dystans: " << ans << endl;
        }
    } while (next_permutation(a + 1, a + n + 1));
    return 0;
}
