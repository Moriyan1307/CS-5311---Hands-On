#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

// Helper function to print the shortest paths
void printShortestPaths(const unordered_map<string, unordered_map<string, int>>& distance) {
    for (const auto& source : distance) {
        cout << "Shortest path from given node to: " << endl;
        for (const auto& dest : distance) {
            cout <<  source.first << " -> " << dest.first << ": " 
                 << distance.at(source.first).at(dest.first) << endl;
        }
        cout << endl;
    }
}

// Floyd-Warshall Algorithm function
unordered_map<string, unordered_map<string, int>> floydWarshall(const unordered_map<string, unordered_map<string, int>>& graph) {
    unordered_map<string, unordered_map<string, int>> distance;

    // Initialize distances
    for (const auto& u : graph) {
        for (const auto& v : graph) {
            if (u.first == v.first) {
                distance[u.first][v.first] = 0;
            } else {
                distance[u.first][v.first] = numeric_limits<int>::max();
            }
        }
    }

    // Set initial distances based on direct paths
    for (const auto& u : graph) {
        for (const auto& v : u.second) {
            distance[u.first][v.first] = v.second;
        }
    }

    // Compute shortest paths
    for (const auto& k : graph) {
        for (const auto& i : graph) {
            for (const auto& j : graph) {
                if (distance[i.first][k.first] != numeric_limits<int>::max() &&
                    distance[k.first][j.first] != numeric_limits<int>::max() &&
                    distance[i.first][j.first] > distance[i.first][k.first] + distance[k.first][j.first]) {
                    distance[i.first][j.first] = distance[i.first][k.first] + distance[k.first][j.first];
                }
            }
        }
    }

    return distance;
}

int main() {
    // Example graph from your problem statement
    unordered_map<string, unordered_map<string, int>> graph = {
        {"1", {{"2", 3}, {"3", 8}, {"5", -4}}},
        {"2", {{"5", 7}, {"4", 1}}},
        {"3", {{"2", 4}}},
        {"4", {{"3", -5}, {"1", 2}}},
        {"5", {{"4", 6}}}
    };

    auto all_pairs_shortest_paths = floydWarshall(graph);

    printShortestPaths(all_pairs_shortest_paths);

    return 0;
}



// OUTPUT 

// Shortest path from given node to: 
// 1 -> 1: 0
// 1 -> 2: 1
// 1 -> 3: -3
// 1 -> 4: 2
// 1 -> 5: -4

// Shortest path from given node to: 
// 2 -> 1: 3
// 2 -> 2: 0
// 2 -> 3: -4
// 2 -> 4: 1
// 2 -> 5: -1

// Shortest path from given node to: 
// 3 -> 1: 7
// 3 -> 2: 4
// 3 -> 3: 0
// 3 -> 4: 5
// 3 -> 5: 3

// Shortest path from given node to: 
// 4 -> 1: 2
// 4 -> 2: -1
// 4 -> 3: -5
// 4 -> 4: 0
// 4 -> 5: -2

// Shortest path from given node to: 
// 5 -> 1: 8
// 5 -> 2: 5
// 5 -> 3: 1
// 5 -> 4: 6
// 5 -> 5: 0

// References :  https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/