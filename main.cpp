#include <iostream>
#include "converter.h"

int main() {
    const int Q = 6;
    const int P = 3;

    std::string numQ;
    std::cout << "Введите целое число в системе Q=6: ";
    std::cin >> numQ;

    try {
        std::string numP = convertQtoP(numQ, Q, P);
        std::cout << "Число в системе P=3: " << numP << "\n";
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }

    return 0;
}