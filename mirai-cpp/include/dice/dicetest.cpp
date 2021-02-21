#include <iostream>
#include <string>
#include "dice.h"

int main()
{
    std::string cmd;
    while (std::cin >> cmd)
    {
        std::cout << rndm(cmd) << std::endl;
    }
    return 0;
}