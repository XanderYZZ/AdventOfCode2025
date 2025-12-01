#include <fstream>
#include <iostream>
#include <filesystem>

class One {
public:
    void Run() {
        std::ifstream input_file("inputs/One.txt");

        if (input_file.is_open()) {
            std::cout << "Opened!\n";
            int result = ProcessFile(input_file);
            std::cout << "Resulting password: " << result << "\n";
        } else {
            std::cout << "Failed to open file.\n";
        }
    }

private:
    [[nodiscard]]
    int ProcessFile(std::ifstream& file) {
        int password = 0;
        int dial = 50;
        std::string line;

        while (std::getline(file, line)) {
            char direction = line[0];
            int amount = std::stoi(line.substr(1));

            switch(direction) {
                case 'R':
                    dial = (dial + amount) % 100;
                    break;
                case 'L':
                    dial = (dial - amount) % 100;
                    break;
                default:
                    std::cout << "Invalid direction: " << direction << "\n";
                    break;
            }

            if (dial != 0) { continue; }

            password += 1;
        }

        return password;
    }
};