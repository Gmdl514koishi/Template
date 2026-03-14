#include <fstream>
#include <iostream>
using namespace std;

void solve() {
    using namespace std;
    // code
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