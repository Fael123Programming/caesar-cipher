#include <string>
#include <cctype>
#include <cassert>
#include "char_type.cpp"

using std::string;

class Encoder {
    public:
        string encode(string input, int offset_value) {
            assert(offset_value >= 0);
            char temp;
            string result = "";
            for (int i = 0; i < input.size(); i++) {
                temp = input[i];
                if (islower(temp)) {
                    temp = offset(temp, offset_value, LOWERCASE_LETTER);
                } else if (isupper(temp)) {
                    temp = offset(temp, offset_value, UPPERCASE_LETTER);
                } else if (isdigit(temp)) {
                    temp = offset(temp, offset_value, DIGIT);
                }
                result += temp;
            }
            return result;
        }

        string decode(string input, int offset_value) {
            return "";
        }
        
    private:
        char offset(char ch, int offset, CharType char_type) {
            int alphabetSize = 26; //a-z and A-Z. 
            int codeFirstSymbol;
            switch (char_type) {
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

        char offset_while(char ch, int offset) {
            while (offset > 0) {
                if (ch == 'z') {
                ch = 'a';
                } else {
                    ch = ch + 1;
                }
                offset--;
            }
            return static_cast<char>(ch);
        }
};
//abcdefghijklmnopqrstuvwxyz