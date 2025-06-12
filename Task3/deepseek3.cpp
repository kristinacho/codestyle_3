#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
    vector<vector<int>> adj;
    int n = 0;

    bool dfs(int v, vector<bool>& vis, vector<bool>& rec, stack<int>& st) {
        vis[v] = rec[v] = true;
        for (int j = n - 1; j >= 0; --j) {
            if (adj[v][j]) {
                if (!vis[j] && !dfs(j, vis, rec, st)) return false;
                else if (rec[j]) return false;
            }
        }
        rec[v] = false;
        st.push(v);
        return true;
    }

public:
    bool load(const string& filename) {
        ifstream f(filename);
        if (!f) return false;
        f >> n;
        adj.resize(n, vector<int>(n));
        for (auto& row : adj)
            for (auto& x : row)
                if (!(f >> x)) return false;
        return true;
    }

    bool sort(vector<int>& res) {
        vector<bool> vis(n), rec(n);
        stack<int> st;
        for (int i = n - 1; i >= 0; --i)
            if (!vis[i] && !dfs(i, vis, rec, st))
                return false;
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    Graph g;
    if (!g.load(argv[1])) {
        cerr << "Error loading graph\n";
        return 1;
    }

    vector<int> res;
    if (!g.sort(res)) {
        cout << "No solution\n";
        return 0;
    }

    cout << "Topological order: ";
    for (int v : res) cout << v << " ";
    cout << "\n";
}