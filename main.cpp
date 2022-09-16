#include <cctype>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include "view/View.cpp"
#include "encoder/encoder.cpp"

int main() {
    View view;
    Encoder encoder;
    std::string text;
    std::string answer;
    int offset;
    do {
        view.printHeader();
        answer = view.menu();
        view.clearPrompt();
        if (answer == "1") {
            text = view.inputLine("Enter text: ");
            view.clearPrompt();
            try {
                offset = std::stoi(
                    view.inputLine("Enter offset value: ")
                );
                view.clearPrompt();
                encoder.setOffsetValue(offset);
                view.print("Encoded with offset = " + std::to_string(encoder.getOffsetValue()));
                view.print(encoder.encode(text));
            } catch(std::invalid_argument) {
                view.clearPrompt();
                view.print("invalid offset");
            }
        } else if (answer == "2") {
            text = view.inputLine("Enter encoded text: ");
            view.clearPrompt();
            try {
                offset = std::stoi(
                    view.inputLine("Enter the offset value used to encode: ")
                );
                view.clearPrompt();
                encoder.setOffsetValue(offset);
                view.print("Decoded with offset = " + std::to_string(encoder.getOffsetValue()));
                view.print(encoder.decode(text));
            } catch(std::invalid_argument) {
                view.clearPrompt();
                view.print("invalid offset");
            }
        }
    } while (answer == "1" || answer == "2");
    return 0;
}
