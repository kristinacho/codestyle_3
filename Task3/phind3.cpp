#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int n; // Количество вершин
    vector<vector<int>> adjMatrix; // Матрица смежности
    vector<bool> visited; // Вектор для отслеживания посещенных вершин
    vector<bool> onStack; // Вектор для отслеживания вершин в текущем пути (для обнаружения циклов)
    stack<int> topologicalOrder; // Стек для хранения порядка сортировки

    bool dfs(int v) {
        visited[v] = true;
        onStack[v] = true;

        for (int j = 0; j < n; ++j) {
            if (adjMatrix[v][j] != 0) { // Если есть дуга из v в j
                if (!visited[j]) {
                    if (dfs(j)) return true; // Рекурсивный вызов
                }
                else if (onStack[j]) {
                    return true; // Обнаружен цикл
                }
            }
        }

        onStack[v] = false;
        topologicalOrder.push(v); // Добавляем вершину в стек после завершения обработки
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
                    cout << "No solution" << endl; // Цикл найден
                    return;
                }
            }
        }

        // Выводим порядок сортировки
        while (!topologicalOrder.empty()) {
            cout << topologicalOrder.top() + 1 << " "; // +1 для перехода к 1-индексации
            topologicalOrder.pop();
        }
        cout << endl;
    }
};

int main() {
    string filename = "FileName.txt"; // Укажите имя вашего файла

    try {
        Graph graph(filename);
        graph.topologicalSort();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
