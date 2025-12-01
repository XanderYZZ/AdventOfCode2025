#include <fstream>
#include <iostream>

class One {
public:
    void Run() {
        std::ifstream input_file("One.txt");

        if (input_file.is_open()) {
            std::cout << "Opened!";
        } else {
            std::cout << "Failed to open file.";
        }
    }
};