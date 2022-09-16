#include <iostream>
#include <string>

class View {
    public:
        View();
        void print(std::string, bool);
        void printHeader();
        void row();
        std::string menu();
        std::string input(std::string);
        std::string inputLine(std::string);
        void clearPrompt();
    private:
        std::string clearCmdStm;
};

View::View() {
    #ifdef __unix
        clearCmdStm = "clear";
    #else
        clearCmdStm = "cls";
    #endif
}

void View::clearPrompt() {
    system(clearCmdStm.c_str());
}

void View::print(std::string msg, bool breakLine = true) {
    std::cout << msg;
    if (breakLine) {
        std::cout << std::endl;
    }
}

void View::row() {
    print("+--------------------------------------------------------------------------+");
}

void View::printHeader() {
    row();
    print("           Welcome to CCMax, a Caesar Cipher Engine        v.1.0.0");
    row();
}

std::string View::inputLine(std::string msg = "") {
    std::string text;
    print(msg, false);
    std::getline(std::cin, text);
    return text;
}

std::string View::menu() {
    print("1 - Cipher\n2 - Decipher\nAny - Exit");
    row();
    return inputLine();
}
