#include <fstream>
#include <iostream>
#include <filesystem>

class Two {
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

        auto crossings_right = [&](int orig, int amount) {
            int k0 = (100 - orig) % 100;

            if (k0 == 0) {
                k0 = 100;
            }

            if (amount < k0) { return 0; }

            return 1 + (amount - k0) / 100;
        };

        auto crossings_left = [&](int orig, int amount) {
            int k0 = orig % 100;
            
            if (k0 == 0) { 
                k0 = 100;
            }

            if (amount < k0) { return 0; }

            return 1 + (amount - k0) / 100;
        };

        while (std::getline(file, line)) {
            int orig = dial;
            char direction = line[0];
            int amount = std::stoi(line.substr(1));

            if (direction == 'R') {
                password += crossings_right(orig, amount);
                dial = (orig + amount) % 100;

                if (dial < 0) {
                    dial += 100;
                }
            } else if (direction == 'L') {
                password += crossings_left(orig, amount);
                dial = (orig - amount) % 100;

                if (dial < 0) {
                    dial += 100;
                }
            } else {
                std::cout << "Invalid direction: " << direction << "\n";
            }
        }

        return password;
    }
};