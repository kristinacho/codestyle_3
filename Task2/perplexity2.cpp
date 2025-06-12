#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

// Узел дерева
struct TreeNode {
    int value; // Хранит операнд или код операции
    shared_ptr<TreeNode> left; // Левое поддерево
    shared_ptr<TreeNode> right; // Правое поддерево

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева из префиксного выражения
shared_ptr<TreeNode> buildTree(vector<int>& tokens, int& index) {
    if (index >= tokens.size()) return nullptr;

    int token = tokens[index++];
    auto node = make_shared<TreeNode>(token);

    if (token < -6) { // Если это операция
        node->left = buildTree(tokens, index);
        node->right = buildTree(tokens, index);
    }

    return node;
}

// Функция для вычисления значения поддерева
int evaluate(shared_ptr<TreeNode> node) {
    if (!node) return 0;

    // Если это лист (операнд)
    if (node->value >= 0 && node->value <= 9) {
        return node->value;
    }

    // Рекурсивно вычисляем значения поддеревьев
    int leftValue = evaluate(node->left);
    int rightValue = evaluate(node->right);

    // Если одно из поддеревьев равно нулю, возвращаем значение другого
    if (leftValue == 0) return rightValue;
    if (rightValue == 0) return leftValue;

    // Выполняем соответствующую операцию
    switch (node->value) {
    case -1: return leftValue + rightValue; // сложение
    case -2: return leftValue - rightValue; // вычитание
    case -3: return leftValue * rightValue; // умножение
    case -4: return leftValue / rightValue; // деление
    case -5: return leftValue % rightValue; // остаток от деления
    case -6: return pow(leftValue, rightValue); // возведение в степень
    default: return 0;
    }
}

// Функция для вывода дерева (для отладки)
void printTree(shared_ptr<TreeNode> node, int level = 0) {
    if (!node) return;

    printTree(node->right, level + 1);
    cout << string(level * 4, ' ') << node->value << endl;
    printTree(node->left, level + 1);
}

// Функция для чтения выражения из файла и преобразования его в токены
vector<int> readExpressionFromFile(const string& filename) {
    ifstream file(filename);
    vector<int> tokens;
    string line;

    if (file.is_open()) {
        getline(file, line);
        istringstream iss(line);
        string token;

        while (iss >> token) {
            if (isdigit(token[0])) {
                tokens.push_back(stoi(token));
            }
            else {
                switch (token[0]) {
                case '+': tokens.push_back(-1); break;
                case '-': tokens.push_back(-2); break;
                case '*': tokens.push_back(-3); break;
                case '/': tokens.push_back(-4); break;
                case '%': tokens.push_back(-5); break;
                case '^': tokens.push_back(-6); break;
                }
            }
        }
    }

    return tokens;
}

int main() {
    string filename = "filename.txt"; // Укажите имя вашего файла
    vector<int> tokens = readExpressionFromFile(filename);

    int index = 0;
    shared_ptr<TreeNode> root = buildTree(tokens, index);

    cout << "Дерево выражения:" << endl;
    printTree(root);

    int result = evaluate(root);

    cout << "Результат вычисления: " << result << endl;

    return 0;
}
