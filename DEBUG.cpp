#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int value = 0;
    vector<int> next_nodes;
};

void solve() {
    using namespace std;
    // code
    int n, m;
    cin >> n >> m;
    vector<Node> nodes(n);
    vector<bool> is_root(n, true);
    vector<bool> is_end(n, true);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        nodes[u].next_nodes.push_back(v);
        is_root[v] = false;
        is_end[u] = false;
    }

    int where_root, where_end;
    for (int i = 0; i < n; ++i) {
        if (is_root[i]) {
            where_root = i;
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (is_end[i]) {
            where_end = i;
            break;
        }
    }
    nodes[where_root].value = 1;

    queue<int> vertex;
    vertex.push(where_root);
    while (!vertex.empty()) {
        int u = vertex.front();
        vertex.pop();
        for (int v : nodes[u].next_nodes) {
            vertex.push(v);
            nodes[v].value += nodes[u].value;
        }
    }

    cout << nodes[where_end].value << '\n';
}

void run() {
    int t = 1;
    cin >> t;
    while (t-- > 0) {
        solve();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //
    #ifdef LOCAL
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    if (!fin.is_open() || !fout.is_open()) {
        cerr << "files not opened\n";
        return 1;
    }
    cin.rdbuf(fin.rdbuf());
    cout.rdbuf(fout.rdbuf());
    #endif
    //
    run();
}