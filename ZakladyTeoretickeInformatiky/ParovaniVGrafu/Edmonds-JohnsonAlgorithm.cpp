// Edmonds' Blossom algorithm (maximum matching in general undirected graphs)
// Complexity: O(n^3). 0-indexed vertices.
// Build: g++ -O2 -std=c++17 blossom.cpp && ./a.out
// #include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

using namespace std;

struct Blossom {
  int n;  
// number of vertices in the graph

vector<vector<int>> g;        
// adjacency list representation of the graph
// g[v] = list of neighbors of vertex v

vector<int> mate;             
// mate[v] = the vertex matched with v in the current matching
// if mate[v] == -1 → v is free (unmatched)

vector<int> parent;           
// parent[v] = parent of v in the BFS alternating tree
// used to reconstruct paths during augmenting path search

vector<int> base;             
// base[v] = the "blossom base" of the set containing v
// if v is not in a blossom, base[v] = v
// if v is inside a contracted blossom, base[v] = representative (root) of that blossom

vector<int> type;             
// label of each vertex during BFS:
//   0 = unseen (not yet discovered in BFS tree)
//   1 = outer (at even distance from the root, connected by unmatched edge)
//   2 = inner (at odd distance from the root, connected by matched edge)

vector<int> q;                
// the BFS queue (implemented as a simple array for speed)
// vertices waiting to be processed

int qh; 
// "queue head" index → position of the next element to dequeue (pop)

int qt; 
// "queue tail" index → position where the next new element will be enqueued (push)

vector<int> inQueue;  
// inQueue[v] = 1 if vertex v is currently in the BFS queue, else 0
// prevents the same vertex from being enqueued multiple times

vector<int> inPath;   
// temporary helper array (often used for finding LCA of blossoms)
// marks vertices visited while walking up parent/mate chains
// used to detect odd cycles and reconstruct blossoms


    explicit Blossom(int n): n(n), g(n), mate(n,-1) {}

    void add_edge(int u, int v) {
        if (u == v) return;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // Lowest common ancestor in alternating tree
    int lca(int a, int b) {
        vector<int> used(n, 0);
        while (true) {
            a = base[a];
            used[a] = 1;
            if (mate[a] == -1) break;
            a = parent[mate[a]];
        }
        while (true) {
            b = base[b];
            if (used[b]) return b;
            if (mate[b] == -1) break;
            b = parent[mate[b]];
        }
        return -1; // never happens
    }

    // Contract blossom with base c; update parent/base and queue
    void markPath(int v, int c, int x) {
        // marks path v->c and v's mate -> ... as inner/outer appropriately,
        // and sets parent pointers toward x.
        while (base[v] != c) {
            int u = mate[v];
            int w = parent[u];
            if (base[w] != c) parent[w] = u;
            if (type[u] == 2) { type[u] = 1; push(u); }
            if (type[w] == 2) { type[w] = 1; push(w); }
            base[v] = base[u] = c;
            v = w;
        }
    }

    void blossomContract(int a, int b) {
        int c = lca(a, b);
        // shrink both arms a->c and b->c
        markPath(a, c, b);
        markPath(b, c, a);
        for (int v = 0; v < n; ++v) {
            if (type[v] == 1 && base[v] == c) continue;
            if (type[v] == 2 && base[v] == c) continue;
        }
    }

    void reset_search_structs(int root) {
        parent.assign(n, -1);
        type.assign(n, 0);
        base.resize(n);
        iota(base.begin(), base.end(), 0);
        inQueue.assign(n, 0);
        q.assign(n, 0); qh = qt = 0;

        type[root] = 1; // outer
        push(root);
    }

    void push(int v) {
        if (!inQueue[v]) {
            inQueue[v] = 1;
            q[qt++] = v;
        }
    }

    // Try to find augmenting path from given root; if found, augment and return true
    bool bfs_augment(int root) {
        reset_search_structs(root);

        while (qh < qt) {
            int v = q[qh++];

            for (int u : g[v]) {
                // if base/u the same as v, ignore (self-loop in contracted sense)
                if (base[v] == base[u] || mate[v] == u) continue;

                if (type[u] == 2) {
                    // u is inner: just ignore
                    continue;
                }
                if (type[u] == 1) {
                    // outer->outer : blossom!
                    blossomContract(v, u);
                    continue;
                }
                // u is unseen
                parent[u] = v;
                if (mate[u] == -1) {
                    // Found augmenting path: flip along v...root and u...root
                    int a = u, b = v;
                    while (b != -1) {
                        int nb = mate[b];
                        mate[b] = a;
                        mate[a] = b;
                        a = nb;
                        if (a == -1) break;
                        b = parent[a];
                    }
                    return true;
                } else 
                {
                    // u is matched; grow tree by adding its mate as outer
                    int m = mate[u];
                    type[u] = 2;        // inner
                    type[m] = 1;        // outer
                    parent[m] = u;
                    push(m);
                }
            }
        }
        return false;
    }

    int maximum_matching() {
        bool progress = true;
        while (progress) {
            progress = false;
            for (int v = 0; v < n; ++v) if (mate[v] == -1) {
                if (bfs_augment(v)) { progress = true; }
            }
        }
        int sz = 0;
        for (int v = 0; v < n; ++v) if (mate[v] != -1 && v < mate[v]) ++sz;
        return sz;
    }
};

// ----- demo -----
int main() {
    // Example with an odd cycle where blossom contraction is required.
    // Graph: triangle (0,1,2) plus tails making an augmenting path through it.
    int n = 7;
    Blossom M(n);
    auto E = [&](int a,int b){ M.add_edge(a,b); };

    E(0,1); E(1,2); E(2,0);   // triangle (blossom)
    E(0,3);                    // tail left
    E(2,4); E(4,5);            // tail right chain
    E(5,6);

    // Start with some matching (could be empty; algorithm works regardless)
    // Here we don't preset matching; algorithm will find a maximum one.

    int sz = M.maximum_matching();
    cout << "Maximum matching size: " << sz << "\n";
    cout << "mate: ";
    for (int v = 0; v < n; ++v) {
    if (M.mate[v] != -1 && v < M.mate[v]) {
        cout << v << " - " << M.mate[v] << "\n";
    }
}

    return 0;
}
