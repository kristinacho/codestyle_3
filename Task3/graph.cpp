#include "graph.h"
#include <fstream>
#include <algorithm>

using namespace std;

bool Graph::loadFromFile(const string& filename, string& error) {
    ifstream file(filename);
    if (!file.is_open()) {
        error = "Cannot open file: " + filename;
        return false;
    }

    file >> vertexCount;
    if (vertexCount <= 0) {
        error = "Invalid vertex count: " + to_string(vertexCount);
        return false;
    }

    adjacencyMatrix.resize(vertexCount, vector<int>(vertexCount));
    for (int i = 0; i < vertexCount; ++i) {
        for (int j = 0; j < vertexCount; ++j) {
            if (!(file >> adjacencyMatrix[i][j])) {
                error = "Invalid matrix data in file";
                return false;
            }
        }
    }

    return true;
}

bool Graph::topologicalSort(vector<int>& result, string& error) const {
    vector<bool> visited(vertexCount, false);
    vector<bool> recursionStack(vertexCount, false);
    stack<int> stack;

    // ќбрабатываем вершины в пор€дке убывани€ номеров
    for (int i = vertexCount - 1; i >= 0; --i) {
        if (!visited[i]) {
            if (!dfsTopologicalSort(i, visited, stack, recursionStack, error)) {
                return false;
            }
        }
    }

    result.clear();
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }

    return true;
}

bool Graph::dfsTopologicalSort(int vertex, vector<bool>& visited,
    stack<int>& stack, vector<bool>& recursionStack,
    string& error) const {
    visited[vertex] = true;
    recursionStack[vertex] = true;

    // ѕровер€ем всех соседей (в пор€дке убывани€ номеров вершин)
    for (int j = vertexCount - 1; j >= 0; --j) {
        if (adjacencyMatrix[vertex][j] != 0) { // ≈сть ребро vertex -> j
            if (!visited[j]) {
                if (!dfsTopologicalSort(j, visited, stack, recursionStack, error)) {
                    return false;
                }
            }
            else if (recursionStack[j]) {
                error = "Graph contains at least one cycle";
                return false;
            }
        }
    }

    recursionStack[vertex] = false;
    stack.push(vertex);
    return true;
}