#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <cstdlib>
#include "BTree/BPlusTree.h"

// void quit() {
//     std::cout << "Terminating Program\n";
//     // break;
// }

int main() {
    std::cout << "HERE";
    BPlusTree<int, int, 4> tree;

    // Create the command map
    std::unordered_map<std::string, std::function<void()>> commands = {
        {"display", [&]() {
            tree.display();
        }},
        {"insert", [&]() {
            int key;
            int value;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cin.ignore(); // discard newline
            std::cout << "Enter value: ";
            std::cin >> value;
            tree.insert(key, value);
        }},
        {"search", [&]() {
            int key;
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cout << "Found value: " << tree.search(key);
        }}
        // {"quit", quit}
    };

    std::string input;

    std::cout << "Enter a command (display, insert, search):\n";
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (commands.find(input) != commands.end()) {
            commands[input](); // Call the corresponding function
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}