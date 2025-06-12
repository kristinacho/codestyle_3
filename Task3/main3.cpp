/**
 * @file main.cpp
 * @brief Топологическая сортировка графа с использованием DFS
 */

#include "graph.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    Graph graph = nullptr;
    string filename = argv[1];
    string error = "";

    if (!graph.loadFromFile(filename, error)) {
        cerr << "Error: " << error << endl;
        return 1;
    }

    vector<int> sortedVertices;
    if (!graph.topologicalSort(sortedVertices, error)) {
        cout << "No solution" << endl;
        return 0;
    }

    cout << "Topological order: ";
    for (int v : sortedVertices) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}