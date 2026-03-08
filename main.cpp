#include <iostream>
#include <vector>

class JointSeartSet {
private:
    std::vector<int> root_node_and_depth;
public:
    JointSeartSet(const int n) : root_node_and_depth(n, -1) {}
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