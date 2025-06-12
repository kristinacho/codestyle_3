/*
 * ��������� ��� ���������� � �������������� ������ ��������������� ���������
 * � ���������� ����� � ����������� ������������ ����������� � �������� ������������
 */

#include "expression_tree.h"

#include <iostream>
#include <fstream>
#include <memory>

using namespace std;

/**
 * @brief ����� ����� � ���������
 * @param argc ���������� ����������
 * @param argv ������ ����������
 * @return ��� ���������� (0 - �����, ����� ������)
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "�������������: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "������ �������� �����: " << filename << endl;
        return 2;
    }

    string expression = "";
    getline(file, expression);
    file.close();

    if (expression.empty()) {
        cerr << "���� ���� ��� �� �������� ���������" << endl;
        return 3;
    }

    ExpressionTree tree = nullptr;
    string error = "";
    unique_ptr<TreeNode> root = tree.buildFromPrefix(expression, error);

    if (!root) {
        cerr << "������ ���������� ������: " << error << endl;
        return 4;
    }

    if (tree.optimizeZeroSubtrees(root, error) != 0) {
        cerr << "������ ����������� ������: " << error << endl;
        return 5;
    }

    cout << "��������� �� ������ ������: " << root.get() << endl;
    cout << "���������� �����: ";
    tree.printPrefix(root.get());
    cout << endl;

    return 0;
}