#include <iostream>
#include <string>
#include <cctype>
// #define NDEBUG
#include <cassert>
#include "char_type.cpp"

class Encoder {
    public:
        Encoder(int);

        Encoder();
        
        std::string encode(std::string);

        std::string decode(std::string);

        int getOffsetValue();

        void setOffsetValue(int);
    private:
        int offsetValue;

        char offset(char, int, CharType);

        char forwardOffset(char, int, CharType);
        
        char backwardOffset(char, int, CharType);
};

Encoder::Encoder(int offsetValue) : offsetValue(offsetValue) {}

Encoder::Encoder() : offsetValue(0) {}

char Encoder::offset(char ch, int offset, CharType charType) {
    if (offset < 0) {
        return backwardOffset(ch, offset, charType);
    }
    return forwardOffset(ch, offset, charType);
}

char Encoder::backwardOffset(char ch, int offset, CharType charType) {
    int alphabetSize = 26; //a-z and A-Z. 
    int codeLastSymbol;
    switch (charType) {
        case LOWERCASE_LETTER:
            codeLastSymbol = 122; //Unicode code of 'z'.
            break;
        case UPPERCASE_LETTER:
            codeLastSymbol = 90; //Unicode code of 'Z'.
            break;
        case DIGIT:
            codeLastSymbol = 57; //Unicode code of '9'.
            alphabetSize = 10; //0-9
            break;
    }
    offset *= -1; //Turning it positive.
    return static_cast<char>(codeLastSymbol - (codeLastSymbol - ch + offset) % alphabetSize);
}

char Encoder::forwardOffset(char ch, int offset, CharType charType) {
    int alphabetSize = 26; //a-z and A-Z. 
    int codeFirstSymbol;
    switch (charType) {
        case LOWERCASE_LETTER:
            codeFirstSymbol = 97; //Unicode code of 'a'.
            break;
        case UPPERCASE_LETTER:
            codeFirstSymbol = 65; //Unicode code of 'A'.
            break;
        case DIGIT:
            codeFirstSymbol = 48; //Unicode code of '0'.
            alphabetSize = 10; //0-9
            break;
    }
    return static_cast<char>(codeFirstSymbol + (ch - codeFirstSymbol + offset) % alphabetSize);
}

std::string Encoder::encode(std::string text) {
    char temp;
    std::string result = "";
    for (int i = 0; i < text.size(); i++) {
        temp = text[i];
        if (islower(temp)) {
            temp = offset(temp, offsetValue, LOWERCASE_LETTER);
        } else if (isupper(temp)) {
            temp = offset(temp, offsetValue, UPPERCASE_LETTER);
        } else if (isdigit(temp)) {
            temp = offset(temp, offsetValue, DIGIT);
        }
        result += temp;
    }
    return result;
}

std::string Encoder::decode(std::string text) {
    char temp;
    std::string result = "";
    for (int i = 0; i < text.size(); i++) {
        temp = text[i];
        if (islower(temp)) {
            temp = offset(temp, -offsetValue, LOWERCASE_LETTER);
        } else if (isupper(temp)) {
            temp = offset(temp, -offsetValue, UPPERCASE_LETTER);
        } else if (isdigit(temp)) {
            temp = offset(temp, -offsetValue, DIGIT);
        }
        result += temp;
    }
    return result;
}

int Encoder::getOffsetValue() {
    return offsetValue;
}

void Encoder::setOffsetValue(int newOffsetValue) {
    offsetValue = newOffsetValue;
}
