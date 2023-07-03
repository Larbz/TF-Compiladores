#include <iostream>
#include <fstream>
#include <vector>

const int MEMORY_SIZE = 30000;

void interpretBrainfuck(const std::string& code) {
    std::vector<char> memory(MEMORY_SIZE, 0);
    int pointer = 0;
    std::vector<int> loopStack;

    for (int i = 0; i < code.length(); ++i) {
        switch (code[i]) {
            case '>':
                ++pointer;
                break;
            case '<':
                --pointer;
                break;
            case '+':
                ++memory[pointer];
                break;
            case '-':
                --memory[pointer];
                break;
            case '.':
                std::cout << memory[pointer];
                break;
            case ',':
                std::cin >> memory[pointer];
                break;
            case '[':
                if (memory[pointer] == 0) {
                    int loopDepth = 1;
                    while (loopDepth > 0) {
                        ++i;
                        if (code[i] == '[')
                            ++loopDepth;
                        else if (code[i] == ']')
                            --loopDepth;
                    }
                } else {
                    loopStack.push_back(i);
                }
                break;
            case ']':
                if (memory[pointer] != 0) {
                    i = loopStack.back() - 1;
                } else {
                    loopStack.pop_back();
                }
                break;
            default:
                break;
        }
    }
}

int main() {
    std::ifstream file("code.bf");
    if (file.is_open()) {
        std::string code((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
        file.close();

        interpretBrainfuck(code);
    } else {
        std::cout << "Error al abrir el archivo." << std::endl;
    }

    return 0;
}

