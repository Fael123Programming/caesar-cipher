#ifndef VIEW_H
#define VIEW_H

#include <string>
class View {
    public:
        void print(std::string msg);
        void printHeader();
        void row();
        std::string menu();
        void clear_prompt() {
            system("clear");
        }
};

#endif
