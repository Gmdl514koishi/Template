#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

class DisJointSet {
private:
    std::vector<int> root_node_and_depth;

public:
    DisJointSet(const int n) : root_node_and_depth(n, -1) {}
    int find_root(int x) {
        // find root and do path compression
        int root = x;
        while (root_node_and_depth[root] >= 0) {
            root = root_node_and_depth[root];
        }
        while (x != root) {
            const int next = root_node_and_depth[x];
            root_node_and_depth[x] = root;
            x = next;
        }
        return root;
    }

    void unite(int x, int y) {
        // unite by depth
        x = find_root(x);
        y = find_root(y);
        const unsigned int x_depth = root_node_and_depth[x];
        const unsigned int y_depth = root_node_and_depth[y];
        if (x_depth > y_depth) {
            root_node_and_depth[y] = x;
        } else if (x_depth < y_depth) {
            root_node_and_depth[x] = y;
        } else if (x != y) {
            root_node_and_depth[y] = x;
            --root_node_and_depth[x];
        }
    }

    bool is_same(int x, int y) {
        // return true if x and y are in the same set, otherwise return false
        return find_root(x) == find_root(y);
    }

    int count_connected_components() {
        // return the number of connected components
        return std::count_if(root_node_and_depth.begin(), root_node_and_depth.end(), [](const int x) {return x < 0;});
    }
};

class UndirectedMinimumSpanningTree {
private:
    struct Edge {
        unsigned int u;
        unsigned int v;
        int weight;
        bool is_directed;
    };

    struct Comparator {
        bool operator()(const Edge& a, const Edge& b) const {
            return a.weight > b.weight;
        }
    };

    struct KruskalResult {
        bool connected;
        bool is_unique;
        long long cost;
        unsigned int spaning_tree_cnt;
    };
    
    std::priority_queue<Edge, std::vector<Edge>, Comparator> selected_edges_and_weights;
    std::vector<Edge> edges_and_weights;

public:
    UndirectedMinimumSpanningTree() : selected_edges_and_weights(), edges_and_weights() { }
    void add_edge(const unsigned int u, const unsigned int v, const int w, const bool is_directed = false) {
        edges_and_weights.push_back(Edge{u, v, w, is_directed});
    }

    std::pair<bool, long long> Prim(const unsigned int n) {
        // return false if there are more than 1 spanning trees, otherwise return true and the cost of the minimum spanning tree
        std::vector<bool> is_included(n, false);
        is_included[0] = true;
        for (auto edge : edges_and_weights) {
            if (edge.u == 0 || edge.v == 0) {
                selected_edges_and_weights.push(edge);
            }
        }
        long long cost = 0;
        int include_cnt = 1;
        while (selected_edges_and_weights.empty() == false && include_cnt < n) {
            const auto edge = selected_edges_and_weights.top();
            selected_edges_and_weights.pop();
            const int u = edge.u;
            const int v = edge.v;
            const int w = edge.weight;
            if (is_included[u] == true && is_included[v] == true) {
                continue;
            }
            cost += w;
            include_cnt++;
            const unsigned int next = is_included[u] == false ? u : v;
            is_included[next] = true;
            for (auto edge : edges_and_weights) {
                if ((edge.u == next && is_included[edge.v] == false) || (edge.v == next && is_included[edge.u] == false)) {
                    selected_edges_and_weights.push(edge);
                }
            }
        }
        int not_in_disjoint = std::count(is_included.begin(), is_included.end(), false);
        if (include_cnt != n) {
            return std::make_pair(false, not_in_disjoint);
        }
        return std::make_pair(true, cost);
    }

    KruskalResult Kruskal(const unsigned int n, const bool search_unique_spanning_tree = false) {
        // return {false, false, -1, spanning_tree_cnt} if there are more than 1 spanning trees, otherwise return {true, is_unique, cost, spanning_tree_cnt}
        DisJointSet disjoint_set(n);
        for (auto edge : edges_and_weights) {
            if (edge.is_directed == true) {
                disjoint_set.unite(edge.u, edge.v);
            }
            else {
                selected_edges_and_weights.push(edge);
            }
        }
        long long cost = 0;
        bool is_unique = true;
        while (!selected_edges_and_weights.empty()) {
            const int this_edge_weight = selected_edges_and_weights.top().weight;
            if (search_unique_spanning_tree == true && is_unique == true) {
                std::vector<Edge> same_weight_edges;
                while (!selected_edges_and_weights.empty() && selected_edges_and_weights.top().weight == this_edge_weight) {
                    same_weight_edges.push_back(selected_edges_and_weights.top());
                    selected_edges_and_weights.pop();
                }
                int valid_edge_cnt = 0;
                for (const auto& edge : same_weight_edges) {
                    const auto [u, v, w, is_directed] = edge;
                    if (disjoint_set.is_same(u, v) == false) {
                        valid_edge_cnt++;
                    }
                }
                int selected_valid_edge_cnt = 0;
                while (!same_weight_edges.empty()) {
                    const auto [u, v, w, is_directsd] = same_weight_edges.back();
                    same_weight_edges.pop_back();
                    if (disjoint_set.is_same(u, v) == false) {
                        disjoint_set.unite(u, v);
                        cost += w;
                        selected_valid_edge_cnt++;
                    }
                }
                if (valid_edge_cnt > selected_valid_edge_cnt) {
                    is_unique = false;
                }
            }
            else {
                const auto [u, v, w, is_directed] = selected_edges_and_weights.top();
                selected_edges_and_weights.pop();
                if (disjoint_set.is_same(u, v) == true) {
                    continue;
                }
                disjoint_set.unite(u, v);
                cost += w;
            }
        }
        unsigned int spanning_trees_cnt = disjoint_set.count_connected_components();
        KruskalResult result;
        if (spanning_trees_cnt != 1) {
            return result = {false, false, -1, spanning_trees_cnt};
        }
        return result = {true, is_unique, cost, spanning_trees_cnt};
    }
};

void solve() {
    using namespace std;
    // code
}

void run() {
    int t = 1;
    std::cin >> t;
    while (t-- > 0) {
        solve();
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    //
    run();
}