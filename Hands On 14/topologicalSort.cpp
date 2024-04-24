#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdexcept>

using namespace std;

class TopologicalGraph {
public:
    unordered_map<string, vector<string>> graph;
    unordered_set<string> vertices;

    void add_edge(const string& u, const string& v) {
        graph[u].push_back(v);
        vertices.insert(u);
        vertices.insert(v);
    }

    vector<string> topological_sort() {
        unordered_map<string, int> in_degree;
        for (const string& u : vertices) {
            in_degree[u] = 0;
        }
        for (const auto& pair : graph) {
            const string& u = pair.first;
            for (const string& v : pair.second) {
                in_degree[v]++;
            }
        }

        queue<string> q;
        for (const string& u : vertices) {
            if (in_degree[u] == 0) {
                q.push(u);
            }
        }

        vector<string> topological_order;
        while (!q.empty()) {
            string u = q.front();
            q.pop();
            topological_order.push_back(u);
            for (const string& v : graph[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    q.push(v);
                }
            }
        }

        for (const auto& pair : in_degree) {
            if (pair.second != 0) {
                throw invalid_argument("Graph contains a cycle");
            }
        }

        return topological_order;
    }
};

int main() {
    TopologicalGraph g;
    g.add_edge("pants", "belt");
    g.add_edge("socks", "belt");
    g.add_edge("shirt", "tie");
    g.add_edge("undershorts", "shoes");
    g.add_edge("undershorts", "pants");
    g.add_edge("tie", "undershorts");
    g.add_edge("belt", "jacket");
    g.add_edge("jacket", "shoes");

    cout << "Topological Ordering:" << endl;
    vector<string> result = g.topological_sort();
    for (const string& vertex : result) {
        cout << vertex << " , ";
    }
    cout << endl;

    return 0;
}

// OUTPUT:
// Topological Ordering:
// shirt , socks , tie , undershorts , pants , belt , jacket , shoes , 

// References : https://www.geeksforgeeks.org/cpp-program-for-topological-sorting/
