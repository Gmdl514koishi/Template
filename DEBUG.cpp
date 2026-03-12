#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <limits>
#include <fstream>
using namespace std;

struct Edge {
    int u;
    int v;
};

struct Node {
    bool is_change;
    int op_sum;
    int condition;
    int fa_node;
    int gr_fa_node;
};

void solve() {
    int n;
    cin >> n;
    vector<Edge> edges(n-1);
    for (auto& edge : edges) {
        int u, v;
        --u;
        --v;
        cin >> u >> v;
        edge = {u, v};
    }

    cin.ignore();
    vector<string> strs(2);
    for (auto& str : strs) {
        string temp;
        getline(cin, temp);
        temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());
        str = temp;
    }

    vector<Node> nodes(n);
    Node node = {strs[0][0] == strs[1][0], (strs[0][0] == strs[1][0] ? 0 : 1), 0, 0};
    nodes[0] = node;
    queue<int> selected_vertexs;
    selected_vertexs.push(0);
    while (!selected_vertexs.empty()) {
        const int vertex = selected_vertexs.front();
        selected_vertexs.pop();
        for (auto& edge : edges) {
            const int u = edge.u;
            const int v = edge.v;
            if (u == vertex) {
                ++nodes[nodes[u].fa_node].condition;
                selected_vertexs.push(v);
                nodes[v] = {strs[0][v] == strs[1][v], (strs[0][v] == strs[1][v] ? 0 : 1), 0, u, nodes[u].fa_node};
            }
            else if (v == vertex) {
                ++nodes[nodes[v].fa_node].condition;
                selected_vertexs.push(u);
                nodes[u] = {strs[0][v] == strs[1][v], (strs[0][v] == strs[1][v] ? 0 : 1), 0, v, nodes[v].fa_node};
            }
        }
    }

    queue<int> vertex_list;
    for (int i = 0; i < n; ++i) {
        if (nodes[i].condition == 0) {
            vertex_list.push(i);
        }
    }
    long long result = 0;
    set<int> should_change_vertex;
    while (!vertex_list.empty()) {
        const int vertex = vertex_list.front();
        vertex_list.pop();
        auto& node = nodes[vertex];
        if (node.fa_node == node.gr_fa_node) {
            result += node.op_sum;
            continue;
        }
        auto& gr_fa_node = nodes[node.gr_fa_node];
        --gr_fa_node.condition;
        gr_fa_node.op_sum += node.op_sum;
        if (node.is_change != gr_fa_node.is_change) {
            ++gr_fa_node.op_sum;
            should_change_vertex.insert(vertex);
        }
        if (gr_fa_node.condition == 0) {
            vertex_list.push(node.gr_fa_node);
        }
    }

    cout << result << '\n';
    bool not_space = true;
    for (auto& vertex : should_change_vertex) {
        if (not_space) {
            cout << vertex;
            not_space = false;
        }
        else {
            cout << ' ' << vertex;
        }
    }
}

void run() {
    int t = 1;
    // cin >> t;
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
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");
    if (!fin.is_open() || !fout.is_open()) {
        std::cerr << "files not opened\n";
        return 1;
    }
    std::cin.rdbuf(fin.rdbuf());
    std::cout.rdbuf(fout.rdbuf());
#endif
    //
    run();
}