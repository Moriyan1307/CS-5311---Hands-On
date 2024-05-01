#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <unordered_map>

using namespace std;

// Function to perform the Bellman-Ford algorithm
pair<vector<int>, vector<int>> bellmanFord(const vector<vector<int>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> pred(n, -1);
    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                int weight = graph[u][v];
                if (weight < INT_MAX && dist[u] < INT_MAX && dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pred[v] = u;
                }
            }
        }
    }

    return {dist, pred};
}

// Function to print the shortest path from source to destination
void printShortestPath(int source, int dest, const vector<int>& pred, const unordered_map<int, char>& vertexNames, const vector<int>& dist) {
    if (pred[dest] == -1) {
        cout << "No path from " << vertexNames.at(source) << " to " << vertexNames.at(dest) << endl;
        return;
    }

    vector<int> path;
    int curr = dest;
    while (curr != source) {
        path.push_back(curr);
        curr = pred[curr];
    }
    path.push_back(source);

    reverse(path.begin(), path.end());
    cout << "Shortest path from " << vertexNames.at(source) << " to " << vertexNames.at(dest) << ": ";
    for (int v : path) {
        cout << vertexNames.at(v) << " -> ";
    }
    cout << "end" << endl;

    cout << "Values along the path: ";
    for (int v : path) {
        cout << dist[v] << " ";
    }
    cout << endl;
}

int main() {
    // Graph representation using adjacency matrix
    vector<vector<int>> graph = {
        {0, 7, INT_MAX, 6, INT_MAX},
        {INT_MAX, 0, -3, INT_MAX, 9},
        {INT_MAX, INT_MAX, 0, -2, INT_MAX},
        {INT_MAX, 6, 5, 0, -4},
        {2, INT_MAX, 7, INT_MAX, 0}
    };

    unordered_map<int, char> vertexNames = {{0, 's'}, {1, 'y'}, {2, 'x'}, {3, 't'}, {4, 'z'}};
    int source = 0; // Vertex s
    int dest = 4; // Vertex z

    auto [dist, pred] = bellmanFord(graph, source);

    printShortestPath(source, dest, pred, vertexNames, dist);

    return 0;
}



// OUTPUT

// Shortest path from s to z: s -> y -> x -> t -> z -> end
// Values along the path: 0 7 4 2 -2 

// Reference : https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/