#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Edge {
public:
    int u;
    int v;
    int w;
    Edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
};

bool compare_edges(const Edge& a, const Edge& b) {
    return a.w < b.w;
}

class DisjointSet {
public:
    vector<int> root;
    vector<int> rank;

    DisjointSet(int size) {
        root.resize(size);
        rank.resize(size);
        for (int i = 0; i < size; ++i) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int find(int u) {
        if (root[u] != u) {
            root[u] = find(root[u]);
        }
        return root[u];
    }

    void union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u == root_v) {
            return;
        }
        if (rank[root_u] > rank[root_v]) {
            root[root_v] = root_u;
        } else {
            root[root_u] = root_v;
            if (rank[root_u] == rank[root_v]) {
                rank[root_v]++;
            }
        }
    }
};

vector<Edge> kruskal_algorithm(vector<Edge>& edges, int num_vertices) {
    sort(edges.begin(), edges.end(), compare_edges);
    DisjointSet ds(num_vertices);
    vector<Edge> mst;
    for (const Edge& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            mst.push_back(edge);
            ds.union_sets(edge.u, edge.v);
        }
    }
    return mst;
}

int main() {
    vector<Edge> edges = {
        Edge(0, 1, 4),
        Edge(0, 7, 8),
        Edge(1, 2, 8),
        Edge(1, 7, 11),
        Edge(2, 3, 7),
        Edge(2, 8, 2),
        Edge(2, 5, 4),
        Edge(3, 4, 9),
        Edge(3, 5, 14),
        Edge(4, 5, 10),
        Edge(5, 6, 2),
        Edge(6, 7, 1),
        Edge(6, 8, 6),
        Edge(7, 8, 7)
    };

    vector<Edge> mst = kruskal_algorithm(edges, 9);

    cout << "Given weight for corresponding edges" << endl;
    
   
    for (const Edge& edge : mst) {
        cout << "Edge " << edge.u << "-" << edge.v << "  -> " << " Weight "<< edge.w << endl;
    }
   

    return 0;
}


// OUTPUT
// Given weight for corresponding edges
// Edge 6-7  ->  Weight 1
// Edge 2-8  ->  Weight 2
// Edge 5-6  ->  Weight 2
// Edge 0-1  ->  Weight 4
// Edge 2-5  ->  Weight 4
// Edge 2-3  ->  Weight 7
// Edge 0-7  ->  Weight 8
// Edge 3-4  ->  Weight 9

// References : https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/