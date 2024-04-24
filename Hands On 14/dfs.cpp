#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Vertex {
public:
    char label;
    int state;
    int start_time;
    int finish_time;
    Vertex* previous;
    Vertex(char l) : label(l), state(0), start_time(0), finish_time(0), previous(nullptr) {}
};

class Graph {
public:
    unordered_map<Vertex*, vector<Vertex*>> adj;
    int time;

    Graph(int vertices) : time(0) {}

    void add_edge(Vertex* start, Vertex* end) {
        if (adj.find(start) == adj.end()) {
            adj[start] = vector<Vertex*>{end};
        } else {
            adj[start].push_back(end);
        }
    }

    void add_vertex(Vertex* vertex) {
        adj[vertex] = vector<Vertex*>{};
    }

    void depth_first_search() {
        for (auto& pair : adj) {
            Vertex* v = pair.first;
            v->state = 0;
            v->previous = nullptr;
        }
        time = 0;
        for (auto& pair : adj) {
            Vertex* v = pair.first;
            if (v->state == 0) {
                depth_first_search_visit(v);
            }
        }
    }

    void depth_first_search_visit(Vertex* vertex) {
        time++;
        vertex->start_time = time;
        vertex->state = 1;
        for (Vertex* v : adj[vertex]) {
            if (v->state == 0) {
                v->previous = vertex;
                depth_first_search_visit(v);
            }
        }
        vertex->state = 2;
        time++;
        vertex->finish_time = time;
    }

  
};

int main() {
    Graph graph(6);

    Vertex u('u'), v('v'), w('w'), x('x'), y('y'), z('z');

    graph.add_edge(&u, &v);
    graph.add_edge(&u, &x);
    graph.add_edge(&x, &v);
    graph.add_edge(&v, &y);
    graph.add_edge(&y, &x);
    graph.add_edge(&w, &y);
    graph.add_edge(&w, &z);
    graph.add_edge(&z, &z);

    graph.depth_first_search();
    cout << "DFS Graph:" << endl;
    for (auto& pair : graph.adj) {
        Vertex* v = pair.first;
        cout << v->label << " -> " << v->start_time << "/" << v->finish_time << " , ";
    }
    cout << endl;

   

    return 0;
}



// OUTPUT
// DFS Graph:
// z -> 1/2 , x -> 3/8 , w -> 9/10 , u -> 11/12 , v -> 4/7 , y -> 5/6 , 

// References : https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/