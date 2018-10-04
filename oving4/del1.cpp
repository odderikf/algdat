#include <iostream>
#include <unistd.h>

#include "NumberDoubleLinkedList.hpp"

int main() {
    while (true) {
	try{
        std::string i1, sign, i2;
        std::cin >> i1;
        NumberDoubleLinkedList l(i1);
	std::cin >> sign;
	std::cin >> i2;
        NumberDoubleLinkedList m(i2);
	std::cout << std::endl;

        if (sign == "+")
            std::cout << l + m << std::endl;
        else if (sign == "-")
            std::cout << l - m << std::endl;
        else if(i1 == "exit")
            break;
        else
            std::cout << "command not recognized: " << sign << std::endl;
	}catch (std::invalid_argument &e) {
	    std::cout << e.what() << std::endl;
	}
    }
    return EXIT_SUCCESS;
}
