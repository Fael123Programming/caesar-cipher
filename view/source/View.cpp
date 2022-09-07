#include "../headers/View.h"
#include <iostream>

using namespace std;

void View::print(std::string msg) {
    cout << msg << endl;
}

void View::row() {
    cout << "+--------------------------------------------------------------------------+\n";
}

void View::printHeader() {
    row();
    print("           Welcome to VMax, a Caesar Cipher engine        v.1.0.0");
    row();
}

string View::menu() {
    cout << "1 - Cipher\n"
        << "2 - Decipher\n"
        << "Any - Exit\n";
    row();
    string answer;
    cout << "-> ";
    cin >> answer;
    return answer;
}