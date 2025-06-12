#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

struct Node {
    int val;
    unique_ptr<Node> left, right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class ExprTree {
    vector<string> tokens;
    size_t pos = 0;

    int evalOp(int op, int a, int b, string& err) const {
        switch (op) {
        case -1: return a + b;
        case -2: return a - b;
        case -3: return a * b;
        case -4: return b ? a / b : (err = "Div by 0", 0);
        case -5: return b ? a % b : (err = "Mod by 0", 0);
        case -6: return !a && b <= 0 ? (err = "0^-n", 0) : pow(a, b);
        default: err = "Bad op"; return 0;
        }
    }

    unique_ptr<Node> build(string& err) {
        if (pos >= tokens.size()) return (err = "Unexpected end"), nullptr;

        int v = stoi(tokens[pos++]);
        if (v < 0 && v >= -6) {
            auto n = make_unique<Node>(v);
            n->left = build(err);
            n->right = build(err);
            return n->left && n->right ? move(n) : nullptr;
        }
        return (v >= 0 && v <= 9) ? make_unique<Node>(v) : (err = "Bad val"), nullptr;
    }

    int optimize(unique_ptr<Node>& n, string& err) {
        if (!n) return (err = "Empty"), 0;
        if (!n->left && !n->right) return n->val;

        int a = optimize(n->left, err), b = optimize(n->right, err);
        if (err.empty() && (a == 0 || b == 0)) {
            int res = evalOp(n->val, a, b, err);
            n = make_unique<Node>(res);
            return res;
        }
        return evalOp(n->val, a, b, err);
    }

public:
    bool parse(const string& expr, string& err) {
        istringstream iss(expr);
        string token;
        while (iss >> token) {
            bool valid = true;
            for (size_t i = 0; i < token.size(); ++i)
                if ((i == 0 && token[i] == '-' && token.size() == 1) ||
                    (i > 0 && !isdigit(token[i]))) valid = false;
            if (!valid) return (err = "Bad token"), false;
            tokens.push_back(token);
        }
        return !tokens.empty() || (err = "No tokens"), !tokens.empty();
    }

    unique_ptr<Node> buildTree(string& err) {
        pos = 0;
        return build(err);
    }

    int optimizeTree(unique_ptr<Node>& root, string& err) {
        return optimize(root, err);
    }

    void print(const Node* n) const {
        if (!n) return;
        if (n->val < 0) cout << "+-*/%^"[-n->val - 1] << " ";
        else cout << n->val << " ";
        print(n->left.get());
        print(n->right.get());
    }
};

int main(int argc, char** argv) {
    if (argc != 2) return cerr << "Usage: " << argv[0] << " <file>\n", 1;

    ifstream f(argv[1]);
    string expr, err;
    getline(f, expr);

    ExprTree tree;
    if (!tree.parse(expr, err)) return cerr << "Parse: " << err << "\n", 2;

    auto root = tree.buildTree(err);
    if (!root) return cerr << "Build: " << err << "\n", 3;

    if (tree.optimizeTree(root, err) && !err.empty())
        return cerr << "Optimize: " << err << "\n", 4;

    cout << "Root: " << root.get() << "\nPrefix: ";
    tree.print(root.get());
    cout << "\n";
}