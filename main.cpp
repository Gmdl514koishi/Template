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
    using tuple = std::tuple<unsigned int, unsigned int, int, bool>;
private:
    struct Comparator {
        bool operator()(const tuple& a, const tuple& b) const {
            return std::get<2>(a) > std::get<2>(b);
        }
    };
    std::priority_queue<tuple, std::vector<tuple>, Comparator> selected_edges_and_weights;
    std::vector<tuple> edges_and_weights;
public:
    UndirectedMinimumSpanningTree() : selected_edges_and_weights(), edges_and_weights() { }
    void add_edge(const unsigned int u, const unsigned int v, const int w, const bool is_directed = false) {
        edges_and_weights.push_back(std::make_tuple(u, v, w, is_directed));
    }
    std::pair<bool, long long> Prim(const unsigned int n) {
        // return false if there are more than 1 spanning trees, otherwise return true and the cost of the minimum spanning tree
        std::vector<bool> is_included(n, false);
        is_included[0] = true;
        for (auto edge : edges_and_weights) {
            if (std::get<0>(edge) == 0 || std::get<1>(edge) == 0) {
                selected_edges_and_weights.push(edge);
            }
        }
        long long cost = 0;
        int include_cnt = 1;
        while (selected_edges_and_weights.empty() == false && include_cnt < n) {
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
            const unsigned int next = is_included[u] == false ? u : v;
            is_included[next] = true;
            for (auto edge : edges_and_weights) {
                if ((std::get<0>(edge) == next && is_included[std::get<1>(edge)] == false) || (std::get<1>(edge) == next && is_included[std::get<0>(edge)] == false)) {
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
    std::pair<bool, long long> Kruskal(const unsigned int n) {
        // return false if there are more than 1 spanning trees, otherwise return true and the cost of the minimum spanning tree
        DisJointSet disjoint_set(n);
        for (auto edge : edges_and_weights) {
            if (std::get<3>(edge) == true) {
                disjoint_set.unite(std::get<0>(edge), std::get<1>(edge));
            }
            else {
                selected_edges_and_weights.push(edge);
            }
        }
        long long cost = 0;
        while (!selected_edges_and_weights.empty()) {
            const auto edge = selected_edges_and_weights.top();
            selected_edges_and_weights.pop();
            const auto [u, v, w, _] = edge;
            if (disjoint_set.is_same(u, v) == true) {
                continue;
            }
            disjoint_set.unite(u, v);
            cost += w;
        }
        int spanning_trees_cnt = disjoint_set.count_connected_components();
        if (spanning_trees_cnt != 1) {
            return std::make_pair(false, spanning_trees_cnt);
        }
        return std::make_pair(true, cost);
    }
    int number_of_undirected_minimum_spanning_trees(const unsigned int n) {
        // return the number of undirected minimum spanning trees in a graph
        DisJointSet disjoint_set(n);
        std::sort(edges_and_weights.begin(), edges_and_weights.end(), [](const tuple& a, const tuple& b) {
            return std::get<2>(a) < std::get<2>(b);
        });
        size_t index = 0;
        for (; index < edges_and_weights.size(); index++) {
            if (disjoint_set.count_connected_components() == 2) {
                break;
            }
            const tuple& edge = edges_and_weights[index];
            const unsigned int u = std::get<0>(edge);
            const unsigned int v = std::get<1>(edge);
            disjoint_set.unite(u, v);
        }
        while (index < edges_and_weights.size() && disjoint_set.is_same(std::get<0>(edges_and_weights[index]), std::get<1>(edges_and_weights[index])) == true) {
            index++;
        }
        int weight = std::get<2>(edges_and_weights[index]);
        int cnt = 0;
        while (index < edges_and_weights.size() && std::get<2>(edges_and_weights[index]) == weight) {
            const tuple& edge = edges_and_weights[index];
            const unsigned int u = std::get<0>(edge);
            const unsigned int v = std::get<1>(edge);
            if (disjoint_set.is_same(u, v) == false) {
                cnt++;
            }
            index++;
        }
        return cnt;
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