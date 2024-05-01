#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <string>

using namespace std;

class Vertex {
public:
    char key;
    unordered_map<char, int> edges;
    Vertex* prev;
    int distance;

    Vertex(char key, const unordered_map<char, int>& edges) : key(key), edges(edges), prev(nullptr), distance(numeric_limits<int>::max()) {}
};

class Graph {
public:
    unordered_map<char, Vertex*> V;
    unordered_map<char, unordered_map<char, int>> dict;

    Graph(const unordered_map<char, unordered_map<char, int>>& graph_dict) {
        for (const auto& pair : graph_dict) {
            V[pair.first] = new Vertex(pair.first, pair.second);
        }
        dict = graph_dict;
    }

    ~Graph() {
        for (auto& pair : V) {
            delete pair.second;
        }
    }

    void relax(Vertex* u, Vertex* v, int weight) {
        if (v->distance > u->distance + weight) {
            v->distance = u->distance + weight;
            v->prev = u;
        }
    }

    char extractMin(const unordered_map<char, Vertex*>& vertexes) {
        char min_key = '\0';
        int min_distance = numeric_limits<int>::max();

        for (const auto& pair : vertexes) {
            if (pair.second->distance < min_distance) {
                min_distance = pair.second->distance;
                min_key = pair.first;
            }
        }
        return min_key;
    }

    void dijkstra(char source) {
        V[source]->distance = 0;
        unordered_map<char, Vertex*> Q = V;

        vector<char> shortestPath;
        while (!Q.empty()) {
            char u = extractMin(Q);
            shortestPath.push_back(u);
            for (const auto& v : dict[u]) {
                relax(V[u], V[v.first], v.second);
            }
            Q.erase(u);
        }

        for (char key : shortestPath) {
            cout << key << " ";
        }
        cout << endl;
    }
};

int main() {
    unordered_map<char, unordered_map<char, int>> graph = {
        {'S', {{'T', 10}, {'Y', 5}}},
        {'T', {{'Y', 2}, {'X', 1}}},
        {'X', {{'Z', 4}}},
        {'Y', {{'T', 3}, {'X', 9}, {'Z', 2}}},
        {'Z', {{'S', 7}, {'X', 6}}}
    };

    Graph testGraph(graph);
    cout<<"Shortest Path Using Dijkstra"<< endl;
    testGraph.dijkstra('S');

    return 0;
}


// OUTPUT 

// Shortest Path Using Dijkstra
// S Y Z T X 

// References : https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
