#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include <sstream>
#include "BTree/BPlusTree.h"

int main() {
    BPlusTree<int, int, 4> tree;

    // Example
    // tree.insert(10, 100);
    // tree.insert(20, 200);
    // tree.insert(5, 50);
    // tree.insert(15, 150);  // Causes leaf split
    // tree.insert(25, 250);  // Causes internal split if enough

    // tree.display();

    // Map input string to function
    std::unordered_map<std::string, std::function<void()>> commands = {
        {"display", [&]() {
            tree.display();
        }},
        {"insert", [&]() {
            int key;
            int value;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cin.ignore();
            std::cout << "Enter value: ";
            std::cin >> value;
            std::cin.ignore();
            tree.insert(key, value);
        }},
        {"search", [&]() {
            int key;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cin.ignore();
            std::cout << "Found value: " << tree.search(key);
        }}
    };

    std::string command;

    while (true) {
        std::cout << "Enter a command (display, insert, search, exit):" << std::endl;
        std::cout << "> ";
        std::getline(std::cin, command);

        if (commands.find(command) != commands.end()) 
        {
            commands[command]();
        } 
        else if(command == "exit")
        {
            break;
        }
        else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}