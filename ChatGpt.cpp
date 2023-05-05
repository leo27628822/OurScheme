#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>

class SExpression {
public:
    std::string atom;
    std::vector<SExpression> children;

    SExpression() = default;

    explicit SExpression(const std::string& atom) : atom(atom) {}
};

void parseSExpression(std::istringstream& stream, SExpression& node) {
    char c;
    while (stream >> c) {
        if (c == '(') {
            SExpression child;
            parseSExpression(stream, child);
            node.children.push_back(child);
        } else if (c == ')') {
            return;
        } else if (!std::isspace(c)) {
            stream.unget();
            std::string atom;
            stream >> atom;
            node.children.push_back(SExpression(atom));
        }
    }
}

void printSExpression(const SExpression& node, int depth = 0) {
    if (!node.atom.empty()) {
        std::cout << std::string(depth * 2, ' ') << node.atom << std::endl;
    } else {
        for (const SExpression& child : node.children) {
            printSExpression(child, depth + 1);
        }
    }
}

int main() {
    std::string input;
    std::cout << "請輸入S-Expression字串：";
    std::getline(std::cin, input);

    SExpression root;
    std::istringstream stream(input);
    parseSExpression(stream, root);

    std::cout << "解析後的S-Expression如下：" << std::endl;
    printSExpression(root);

    return 0;
}