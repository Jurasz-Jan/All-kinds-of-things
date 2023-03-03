#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
//heurystyka- opisane to zostanie w PDF.
using namespace std;

struct Point {
    int x;
    int y;
};

double distance(Point &p1, Point &p2) {
    int x = p1.x - p2.x;
    int y = p1.y - p2.y;
    return sqrt(x * x + y * y);
}

double calc_route_distance(vector<Point> &points, vector<int> &route) {
    double distance = 0;
    for (int i = 1; i < route.size(); i++) {
        distance += ::distance(points[route[i]], points[route[i - 1]]);
    }
    distance += ::distance(points[route[route.size() - 1]], points[route[0]]);
    return distance;
}

vector<int> random_start(int n) {
    vector<int> route(n);
    for (int i = 0; i < n; i++) {
        route[i] = i;
    }
    shuffle(route.begin(), route.end(), default_random_engine());
    return route;
}

vector<int> grasp(vector<Point> &points, int max_iters) {
    int n = points.size();
    vector<int> best_route = random_start(n);
    double best_distance = calc_route_distance(points, best_route);
    for (int i = 0; i < max_iters; i++) {
        vector<int> candidate_route = random_start(n);
        for (int j = 0; j < n * log(n); j++) {
            int pos1 = rand() % n;
            int pos2 = rand() % n;
            swap(candidate_route[pos1], candidate_route[pos2]);
            double candidate_distance = calc_route_distance(points, candidate_route);
            if (candidate_distance < best_distance) {
                best_route = candidate_route;
                best_distance = candidate_distance;
            }
        }
    }
    return best_route;
}

int main() {
    int n;
    cout << "Wprowadź liczbę punktów: ";
    cin >> n;
    vector<Point> points(n);
    cout << "Wprowadź koordynaty" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Punkt " << i + 1 << ": ";
        cin >> points[i].x >> points[i].y;
    }
    int max_iters;
    cout << "Wprowadź maksymalną liczbę iteracji: ";
    cin >> max_iters;
    vector<int> route = grasp(points, max_iters);//(to nie jest problem zamkniętego cyklu hamiltona)
    cout << "Najkrótsza ścieżka : " << endl;
    for (int i = 0; i < n; i++) {
        cout << "Punkt " << i + 1 << ": (" << points[route[i]].x << ", " << points[route[i]].y << ")" << endl;
	}
}