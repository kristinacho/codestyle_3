#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int n; // ���������� ������
    vector<vector<int>> adjMatrix; // ������� ���������
    vector<bool> visited; // ������ ��� ������������ ���������� ������
    vector<bool> onStack; // ������ ��� ������������ ������ � ������� ���� (��� ����������� ������)
    stack<int> topologicalOrder; // ���� ��� �������� ������� ����������

    bool dfs(int v) {
        visited[v] = true;
        onStack[v] = true;

        for (int j = 0; j < n; ++j) {
            if (adjMatrix[v][j] != 0) { // ���� ���� ���� �� v � j
                if (!visited[j]) {
                    if (dfs(j)) return true; // ����������� �����
                }
                else if (onStack[j]) {
                    return true; // ��������� ����
                }
            }
        }

        onStack[v] = false;
        topologicalOrder.push(v); // ��������� ������� � ���� ����� ���������� ���������
        return false;
    }

public:
    Graph(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file");
        }

        file >> n;
        adjMatrix.resize(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                file >> adjMatrix[i][j];
            }
        }

        visited.resize(n, false);
        onStack.resize(n, false);
    }

    void topologicalSort() {
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                if (dfs(i)) {
                    cout << "No solution" << endl; // ���� ������
                    return;
                }
            }
        }

        // ������� ������� ����������
        while (!topologicalOrder.empty()) {
            cout << topologicalOrder.top() + 1 << " "; // +1 ��� �������� � 1-����������
            topologicalOrder.pop();
        }
        cout << endl;
    }
};

int main() {
    string filename = "FileName.txt"; // ������� ��� ������ �����

    try {
        Graph graph(filename);
        graph.topologicalSort();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
