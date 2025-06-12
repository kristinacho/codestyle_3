#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum Color { WHITE, GRAY, BLACK };

bool dfs(int v, const vector<vector<int>>& adj, vector<Color>& color, vector<int>& result) {
    color[v] = GRAY;
    // ���������� ������� � ������� �������� �������
    for (int u = (int)adj.size() - 1; u >= 0; --u) {
        if (adj[v][u] != 0) {
            if (color[u] == GRAY) {
                // ������ ����
                return false;
            }
            if (color[u] == WHITE) {
                if (!dfs(u, adj, color, result)) {
                    return false;
                }
            }
        }
    }
    color[v] = BLACK;
    result.push_back(v);
    return true;
}

int main() {
    const string FileName = "FileName"; // ��� ����� � ������
    ifstream fin(FileName);
    if (!fin.is_open()) {
        cerr << "������ �������� ����� " << FileName << endl;
        return 1;
    }

    int n;
    fin >> n;
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> adj[i][j];
        }
    }
    fin.close();

    vector<Color> color(n, WHITE);
    vector<int> result;

    // ��������� DFS �� ������ � ������� �������� �������, ����� ��� ������������ �������
    // ������� � �������� �������� �������������� �������
    for (int v = n - 1; v >= 0; --v) {
        if (color[v] == WHITE) {
            if (!dfs(v, adj, color, result)) {
                cout << "No solution" << endl;
                return 0;
            }
        }
    }

    // ������ result �������� ������� � �������� ������� �������������� ����������
    reverse(result.begin(), result.end());

    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i] + 1; // +1 ��� ������ ������� ������ � 1, � �� � 0
        if (i + 1 < result.size()) cout << " ";
    }
    cout << endl;

    return 0;
}
