#include <iostream>
#include <string>

int main() {
    std::string line;
    std::cout << "Reading from stdin:" << std::endl;
    
    while (std::getline(std::cin, line)) {
        std::cout << "Read: " << line << std::endl;
    }
    
    std::cout << "End of input" << std::endl;
    return 0;
} 