#ifndef FIVE_HPP
#define FIVE_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <thread> 
#include <chrono> 

class Five {
public:
    void Run() {
        std::ifstream input_file("inputs/Five.txt");

        if (input_file.is_open()) {
            std::cout << "Opened!\n";
            int result = ProcessFile(input_file);
            std::cout << "Resulting sum: " << result << "\n";
        } else {
            std::cout << "Failed to open file.\n";
        }
    }

private:
    [[nodiscard]]
    int ProcessFile(std::ifstream& file) {
        int sum = 0;
        std::string line;

        while (std::getline(file, line)) {
            int highest = 0;
            int second_highest = 0;

            for (int i = 0; i < line.size(); i++) {
                char c = line[i];
                int num = c - '0';
                
                // If the num is greater than the highest first num, and this is not the last digit.
                if (num > highest && i < (line.size() - 1)) {
                    highest = num;
                    second_highest = 0;
                } else {
                    second_highest = std::max(second_highest, num);
                }
            }

            int to_add = (highest * 10) + second_highest;
            sum += to_add;

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        return sum;
    }
};

#endif