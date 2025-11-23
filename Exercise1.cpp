#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double term(double a, double b) {
    return (a + sqrt(b)) / (sqrt(a) + b);
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    double x = term(13,7) + term(15, 12) + term(32,21);
    cout << std::fixed << std::setprecision(6);
    cout << "x = " << x << std::endl;

    return 0;
}