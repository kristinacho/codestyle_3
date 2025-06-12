/*
 * Программа для построения и преобразования дерева арифметического выражения
 * в префиксной форме с последующей оптимизацией поддеревьев с нулевыми результатами
 */
#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <memory>
#include <string>
#include <vector>

 /**
  * @brief Узел дерева выражения
  */
struct TreeNode {
    int value;                      ///< Значение узла (операнд или код операции)
    std::unique_ptr<TreeNode> left; ///< Левый потомок
    std::unique_ptr<TreeNode> right;///< Правый потомок

    /**
     * @brief Конструктор узла
     * @param val Значение узла
     */
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief Класс для работы с деревьями выражений
 */
class ExpressionTree {
public:
    /**
     * @brief Строит дерево из префиксного выражения
     * @param expression Строка с выражением
     * @param error [out] Строка для сообщения об ошибке
     * @return Указатель на корень дерева или nullptr при ошибке
     */
    std::unique_ptr<TreeNode> buildFromPrefix(const std::string& expression, std::string& error);

    /**
     * @brief Оптимизирует дерево, заменяя поддеревья с нулевыми результатами
     * @param node Корень дерева для оптимизации
     * @param error [out] Строка для сообщения об ошибке
     * @return Код ошибки (0 - успех, иначе код ошибки)
     */
    int optimizeZeroSubtrees(std::unique_ptr<TreeNode>& node, std::string& error);

    /**
     * @brief Выводит дерево в префиксном порядке
     * @param node Узел для вывода
     */
    void printPrefix(const TreeNode* node) const;

private:
    std::vector<std::string> tokens; ///< Токены выражения
    size_t currentToken = 0;         ///< Текущий обрабатываемый токен

    /**
     * @brief Рекурсивно строит дерево из токенов
     * @param error [out] Строка для сообщения об ошибке
     * @return Указатель на узел или nullptr при ошибке
     */
    std::unique_ptr<TreeNode> buildTree(std::string& error);

    /**
     * @brief Вычисляет значение операции
     * @param op Код операции
     * @param left Левый операнд
     * @param right Правый операнд
     * @param error [out] Строка для сообщения об ошибке
     * @return Результат вычисления или 0 при ошибке
     */
    int evaluateOperation(int op, int left, int right, std::string& error) const;

    /**
     * @brief Разбивает строку на токены
     * @param str Входная строка
     * @param error [out] Строка для сообщения об ошибке
     * @return Код ошибки (0 - успех, иначе код ошибки)
     */
    int tokenize(const std::string& str, std::string& error);
};

#endif // EXPRESSION_TREE_H