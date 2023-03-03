#include <bits/stdc++.h>
using namespace std;

const int N = 105;
const int maxn = 1e9;
//pojawiały się pewne problemy z algorytmem zachłannym. Wymaga to przetestowania. Testy zostaną zrobione w edycji programu.
//niestety,  te algorytmy należy porównać formatowo, porównać złożoności i czas wykonania.
//Obecna wersja jest przesłana, by nie utracić punktów potrzebnych do zaliczenia przedmiotu, jeśli oczywiście takie rozwiązanie jest akceptowalne.
//Edycje i dodatki zostaną wprowadzone-obecne pliki jest formą "przejściową"
int n;
pair<int, int> points[N];
vector<int> path, visited(N);
double ans = maxn;

double dist(pair<int, int> a, pair<int, int> b) {
    int x = a.first - b.first;
    int y = a.second - b.second;
    return sqrt(x * x + y * y);
}

void visit(int cur) {
    visited[cur] = 1;
    path.push_back(cur);
    int next = -1;
    double min_dist = maxn;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            double d = dist(points[cur], points[i]);
            if (d < min_dist) {
                min_dist = d;
                next = i;
            }
        }
    }
    if (next == -1) {
        return;
    }
    visit(next);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    visit(1);
    double sum = 0;
    for (int i = 1; i < n; i++) {
        sum += dist(points[path[i]], points[path[i + 1]]);
    }
    sum += dist(points[path[n]], points[path[0]]);
    sum += dist(points[path[0]], points[path[n]]);
    cout << "Trasa: ";
    for (int i = 0; i < n; i++) {
        cout << "(" << points[path[i]].first << ", " << points[path[i]].second << ") ";
    }
    cout << "(" << points[path[0]].first << ", " << points[path[0]].second << ")" << endl;
    //cout << "Dystans: " << sum << endl;
	//problem zamkniętycc
    return 0;
}
