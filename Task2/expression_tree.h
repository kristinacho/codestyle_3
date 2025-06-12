/*
 * ��������� ��� ���������� � �������������� ������ ��������������� ���������
 * � ���������� ����� � ����������� ������������ ����������� � �������� ������������
 */
#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <memory>
#include <string>
#include <vector>

 /**
  * @brief ���� ������ ���������
  */
struct TreeNode {
    int value;                      ///< �������� ���� (������� ��� ��� ��������)
    std::unique_ptr<TreeNode> left; ///< ����� �������
    std::unique_ptr<TreeNode> right;///< ������ �������

    /**
     * @brief ����������� ����
     * @param val �������� ����
     */
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief ����� ��� ������ � ��������� ���������
 */
class ExpressionTree {
public:
    /**
     * @brief ������ ������ �� ����������� ���������
     * @param expression ������ � ����������
     * @param error [out] ������ ��� ��������� �� ������
     * @return ��������� �� ������ ������ ��� nullptr ��� ������
     */
    std::unique_ptr<TreeNode> buildFromPrefix(const std::string& expression, std::string& error);

    /**
     * @brief ������������ ������, ������� ���������� � �������� ������������
     * @param node ������ ������ ��� �����������
     * @param error [out] ������ ��� ��������� �� ������
     * @return ��� ������ (0 - �����, ����� ��� ������)
     */
    int optimizeZeroSubtrees(std::unique_ptr<TreeNode>& node, std::string& error);

    /**
     * @brief ������� ������ � ���������� �������
     * @param node ���� ��� ������
     */
    void printPrefix(const TreeNode* node) const;

private:
    std::vector<std::string> tokens; ///< ������ ���������
    size_t currentToken = 0;         ///< ������� �������������� �����

    /**
     * @brief ���������� ������ ������ �� �������
     * @param error [out] ������ ��� ��������� �� ������
     * @return ��������� �� ���� ��� nullptr ��� ������
     */
    std::unique_ptr<TreeNode> buildTree(std::string& error);

    /**
     * @brief ��������� �������� ��������
     * @param op ��� ��������
     * @param left ����� �������
     * @param right ������ �������
     * @param error [out] ������ ��� ��������� �� ������
     * @return ��������� ���������� ��� 0 ��� ������
     */
    int evaluateOperation(int op, int left, int right, std::string& error) const;

    /**
     * @brief ��������� ������ �� ������
     * @param str ������� ������
     * @param error [out] ������ ��� ��������� �� ������
     * @return ��� ������ (0 - �����, ����� ��� ������)
     */
    int tokenize(const std::string& str, std::string& error);
};

#endif // EXPRESSION_TREE_H