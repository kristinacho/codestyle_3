/*
 * Программа для построения и преобразования дерева арифметического выражения
 * в префиксной форме с последующей оптимизацией поддеревьев с нулевыми результатами
 */

#include "expression_tree.h"
#include <sstream>
#include <cmath>
#include <cctype>

using namespace std;

/**
 * @brief Разбивает строку на токены с проверками
 */
int ExpressionTree::tokenize(const string& str, string& error) {
    if (str.empty()) {
        error = "Пустая входная строка";
        return 1;
    }

    istringstream iss(str);
    tokens.clear();
    string token;

    while (iss >> token) {
        bool is_valid = true;
        for (size_t i = 0; i < token.size(); ++i) {
            if (i == 0 && token[i] == '-') {
                if (token.size() == 1) {
                    is_valid = false;
                }
                continue;
            }
            if (!isdigit(token[i])) {
                is_valid = false;
                break;
            }
        }

        if (!is_valid) {
            error = "Некорректный токен: " + token;
            return 2;
        }

        tokens.push_back(token);
    }

    if (tokens.empty()) {
        error = "Не найдено корректных токенов";
        return 3;
    }

    currentToken = 0;
    return 0;
}

/**
 * @brief Рекурсивно строит дерево с проверками
 */
unique_ptr<TreeNode> ExpressionTree::buildTree(string& error) {
    if (currentToken >= tokens.size()) {
        error = "Неожиданный конец выражения";
        return nullptr;
    }

    string token = tokens[currentToken++];
    int value = 0;

    try {
        value = stoi(token);
    }
    catch (...) {
        error = "Невозможно преобразовать токен в число: " + token;
        return nullptr;
    }

    if (token[0] == '-' && token.size() > 1) {
        if (value < -6 || value > -1) {
            error = "Недопустимый код операции: " + token;
            return nullptr;
        }

        auto node = make_unique<TreeNode>(value);
        node->left = buildTree(error);
        if (!node->left) return nullptr;

        node->right = buildTree(error);
        if (!node->right) {
            error = "Недостаточно операндов для операции " + token;
            return nullptr;
        }

        return node;
    }
    else {
        if (value < 0 || value > 9) {
            error = "Операнд вне диапазона 0-9: " + token;
            return nullptr;
        }
        return make_unique<TreeNode>(value);
    }
}

/**
 * @brief Создает дерево выражения с проверками
 */
unique_ptr<TreeNode> ExpressionTree::buildFromPrefix(const string& expression, string& error) {
    int tokenizeResult = tokenize(expression, error);
    if (tokenizeResult != 0) {
        return nullptr;
    }

    currentToken = 0;
    return buildTree(error);
}

/**
 * @brief Вычисляет операцию с проверками
 */
int ExpressionTree::evaluateOperation(int op, int left, int right, string& error) const {
    switch (op) {
    case -1: return left + right;
    case -2: return left - right;
    case -3: return left * right;
    case -4:
        if (right == 0) {
            error = "Деление на ноль";
            return 0;
        }
        return left / right;
    case -5:
        if (right == 0) {
            error = "Остаток от деления на ноль";
            return 0;
        }
        return left % right;
    case -6:
        if (left == 0 && right <= 0) {
            error = "Ноль в отрицательной степени";
            return 0;
        }
        return (int)pow(left, right);
    default:
        error = "Неизвестная операция: " + to_string(op);
        return 0;
    }
}

/**
 * @brief Оптимизирует дерево с проверками
 */
int ExpressionTree::optimizeZeroSubtrees(unique_ptr<TreeNode>& node, string& error) {
    if (!node) {
        error = "Пустой узел при оптимизации";
        return 1;
    }

    if (!node->left && !node->right) {
        if (node->value < 0 || node->value > 9) {
            error = "Некорректное значение операнда: " + to_string(node->value);
            return 2;
        }
        return node->value;
    }

    if (!node->left || !node->right) {
        error = "Неполное выражение для операции " + to_string(node->value);
        return 3;
    }

    int leftVal = optimizeZeroSubtrees(node->left, error);
    if (!error.empty()) return 0;

    int rightVal = optimizeZeroSubtrees(node->right, error);
    if (!error.empty()) return 0;

    if (leftVal == 0 || rightVal == 0) {
        int result = evaluateOperation(node->value, leftVal, rightVal, error);
        if (!error.empty()) return 0;

        node = make_unique<TreeNode>(result);
        return result;
    }

    return evaluateOperation(node->value, leftVal, rightVal, error);
}

/**
 * @brief Выводит дерево в префиксном порядке
 */
void ExpressionTree::printPrefix(const TreeNode* node) const {
    if (!node) return;

    if (node->value < 0) {
        switch (node->value) {
        case -1: cout << "+ "; break;
        case -2: cout << "- "; break;
        case -3: cout << "* "; break;
        case -4: cout << "/ "; break;
        case -5: cout << "% "; break;
        case -6: cout << "^ "; break;
        }
    }
    else {
        cout << node->value << " ";
    }

    printPrefix(node->left.get());
    printPrefix(node->right.get());
}