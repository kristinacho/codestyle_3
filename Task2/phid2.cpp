#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <sstream>
#include <cmath>

// ���� ������
struct Node {
    int code; // -1..-6 ��� ��������, 0..9 ��� �����
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int c) : code(c), left(nullptr), right(nullptr) {}
};

// ������� ��� ���������� �������� ��������
int applyOp(int opCode, int leftVal, int rightVal) {
    switch (opCode) {
    case -1: return leftVal + rightVal;            // +
    case -2: return leftVal - rightVal;            // -
    case -3: return leftVal * rightVal;            // *
    case -4:
        if (rightVal == 0) throw std::runtime_error("Division by zero");
        return leftVal / rightVal;                  // /
    case -5:
        if (rightVal == 0) throw std::runtime_error("Modulo by zero");
        return leftVal % rightVal;                  // %
    case -6:
        if (rightVal < 0) throw std::runtime_error("Negative exponent");
        return static_cast<int>(std::pow(leftVal, rightVal)); // ^
    default:
        throw std::runtime_error("Unknown operation");
    }
}

// ������ ���������� ��������� �� ������, ������ ������
std::shared_ptr<Node> buildTree(std::istringstream& iss) {
    std::string token;
    if (!(iss >> token)) {
        throw std::runtime_error("Unexpected end of expression");
    }

    // ���������, �������� �� ����� ��������� ��� ������
    if (token == "+") return std::make_shared<Node>(-1);
    if (token == "-") return std::make_shared<Node>(-2);
    if (token == "*") return std::make_shared<Node>(-3);
    if (token == "/") return std::make_shared<Node>(-4);
    if (token == "%") return std::make_shared<Node>(-5);
    if (token == "^") return std::make_shared<Node>(-6);

    // ���� ����� (0..9)
    if (token.size() == 1 && token[0] >= '0' && token[0] <= '9') {
        return std::make_shared<Node>(token[0] - '0');
    }

    throw std::runtime_error("Invalid token: " + token);
}

// ���������� ������ ������, ��������, ��� �������� ����� ��� ��������
std::shared_ptr<Node> parseExpression(std::istringstream& iss) {
    auto node = buildTree(iss);
    if (node->code < 0) { // ��������
        node->left = parseExpression(iss);
        node->right = parseExpression(iss);
    }
    return node;
}

// ���������� ��������� � ����������� ������
// ���������� �������� ���������
int evaluateAndSimplify(std::shared_ptr<Node>& node) {
    if (!node) return 0;

    // ���� ���� (�����)
    if (node->code >= 0) {
        return node->code;
    }

    // ����� ��������
    int leftVal = evaluateAndSimplify(node->left);
    int rightVal = evaluateAndSimplify(node->right);

    // ���� ����� ��� ������ ��������� ����� 0, �������� ��������� ���������
    if (leftVal == 0) {
        node = std::make_shared<Node>(rightVal);
        return rightVal;
    }
    if (rightVal == 0) {
        node = std::make_shared<Node>(leftVal);
        return leftVal;
    }

    int val = applyOp(node->code, leftVal, rightVal);
    return val;
}

// ��� ������ ������ (����������)
void printTree(const std::shared_ptr<Node>& node, int depth = 0) {
    if (!node) return;
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    if (node->code >= 0) {
        std::cout << node->code << "\n";
    }
    else {
        std::cout << node->code << "\n";
        printTree(node->left, depth + 1);
        printTree(node->right, depth + 1);
    }
}

int main() {
    std::string filename = "filename"; // ��� ����� � ����������
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "�� ������� ������� ���� " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::getline(fin, line);
    fin.close();

    std::istringstream iss(line);

    try {
        auto root = parseExpression(iss);

        // ��������� � ����������� ������
        evaluateAndSimplify(root);

        // ������� ��������� �� ������ (�����)
        std::cout << "��������� �� ������ ������: " << root.get() << std::endl;

        // ��� ����������� ����� ������� ������
        std::cout << "������ ����� ��������������:\n";
        printTree(root);

    }
    catch (const std::exception& ex) {
        std::cerr << "������: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
