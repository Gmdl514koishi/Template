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
        return find_root(x) == find_root(y);
    }
};

class UndirectedMinimumSpanningTree {
private:
    struct Comparator {
        bool operator()(const std::tuple<unsigned int, unsigned int, int>& a, const std::tuple<unsigned int, unsigned int, int>& b) const {
            return std::get<2>(a) > std::get<2>(b);
        }
    };
    std::priority_queue<std::tuple<unsigned int, unsigned int, int>, std::vector<std::tuple<unsigned int, unsigned int, int>>, Comparator> selected_edges_and_weights;
    std::vector<std::tuple<unsigned int, unsigned int, int>> edges_and_weights;
public:
    UndirectedMinimumSpanningTree() : selected_edges_and_weights(), edges_and_weights() { }
    void add_edge(const int u, const int v, const int w = 1) {
        edges_and_weights.push_back(std::make_tuple(u, v, w));
    }
    int Prim(const unsigned int n) {
        std::vector<bool> is_included(n, false);
        is_included[0] = true;
        for (auto edge : edges_and_weights) {
            if (std::get<0>(edge) == 0 || std::get<1>(edge) == 0) {
                selected_edges_and_weights.push(edge);
            }
        }
        int cost = 0;
        int include_cnt = 1;
        while (selected_edges_and_weights.empty() == false && include_cnt != n) {
            const auto edge = selected_edges_and_weights.top();
            selected_edges_and_weights.pop();
            const int u = std::get<0>(edge);
            const int v = std::get<1>(edge);
            const int w = std::get<2>(edge);
            if (is_included[u] == true && is_included[v] == true) {
                continue;
            }
            cost += w;
            include_cnt++;
            const int next = is_included[u] == false ? u : v;
            is_included[next] = true;
            for (auto edge : edges_and_weights) {
                if ((std::get<0>(edge) == next && is_included[std::get<1>(edge)] == false) || (std::get<1>(edge) == next && is_included[std::get<0>(edge)] == false)) {
                    selected_edges_and_weights.push(edge);
                }
            }
        }
        if (include_cnt != n) {
            return -1;
        }
        return cost;
    }
};

void solve() {
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