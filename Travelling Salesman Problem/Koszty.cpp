#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

const int MAX_N = 100;
const double INF = INT_MAX;

double cost(int x1, int y1, int x2, int y2) {
return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void createGraph(int n, int x[], int y[], double graph[][MAX_N]) {
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
graph[i][j] = cost(x[i], y[j], x[j], y[j]);
}
}
}

double tsp(double graph[][MAX_N], int n, int start, std::vector<int>& path, std::vector<bool>& visited) {
double minCost = INF;
if (path.size() == n) {
minCost = graph[start][0];
} else {
for (int i = 0; i < n; i++) {
if (!visited[i]) {
int currCity = i;
double currCost = graph[start][currCity];
visited[currCity] = true;
path.push_back(currCity);
double tempCost = tsp(graph, n, currCity, path, visited);
if (tempCost + currCost < minCost) {
minCost = tempCost + currCost;
}
visited[currCity] = false;
path.pop_back();
}
}
}
return minCost;
}

int main() {
int n;
std::cin >> n;
int x[MAX_N], y[MAX_N];
double graph[MAX_N][MAX_N];
for (int i = 0; i < n; i++) {
std::cin >> x[i] >> y[i];
}
createGraph(n, x, y, graph);
std::vector<int> path;
std::vector<bool> visited(n, false);
visited[0] = true;
path.push_back(0);
double minCost = tsp(graph, n, 0, path, visited);
std::cout << "Minimum cost: " << minCost << std::endl;
std::cout << "Path: ";
for (int i = 0; i < path.size(); i++) {
std::cout << path[i] << " ";
}
std::cout << std::endl;
return 0;
}