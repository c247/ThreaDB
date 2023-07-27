#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "bplustree.h"

int main() {
    BPlusTree bPlusTree;

    std::cout << "Commands:" << std::endl;
    std::cout << "  i <key> <value>: Insert a key-value pair into the B+ tree." << std::endl;
    std::cout << "  s <key1> <key2> ...: Search for multiple keys in the B+ tree." << std::endl;
    std::cout << "  q: Quit the program." << std::endl;

    while (true) {
        std::string line;
        std::cout << "> ";
        std::getline(std::cin, line);
        std::stringstream ss(line);

        std::string action;
        ss >> action;

        if (action == "i") {
            int key, value;
            ss >> key >> value;
            bPlusTree.insert(key, value);
        } else if (action == "s") {
            std::vector<int> keys;
            int key;
            while (ss >> key) {
                keys.push_back(key);
            }

            for (int key : keys) {
                int value = bPlusTree.search(key);
                std::cout << "Key: " << key << ", Value: " << value << std::endl;
            }
        } else if (action == "q") {
            break;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }

    return 0;
}
