/*
 * Программа для построения и преобразования дерева арифметического выражения
 * в префиксной форме с последующей оптимизацией поддеревьев с нулевыми результатами
 */

#include "expression_tree.h"

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

/**
 * @brief Точка входа в программу
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @return Код завершения (0 - успех, иначе ошибка)
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Использование: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return 2;
    }

    string expression = "";
    getline(file, expression);
    file.close();

    if (expression.empty()) {
        cerr << "Файл пуст или не содержит выражения" << endl;
        return 3;
    }

    ExpressionTree tree = nullptr;
    string error = "";
    unique_ptr<TreeNode> root = tree.buildFromPrefix(expression, error);

    if (!root) {
        cerr << "Ошибка построения дерева: " << error << endl;
        return 4;
    }

    if (tree.optimizeZeroSubtrees(root, error) != 0) {
        cerr << "Ошибка оптимизации дерева: " << error << endl;
        return 5;
    }

    cout << "Указатель на корень дерева: " << root.get() << endl;
    cout << "Префиксный обход: ";
    tree.printPrefix(root.get());
    cout << endl;

    return 0;
}