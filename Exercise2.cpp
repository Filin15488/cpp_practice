#include <iostream>
#include <iomanip>

using namespace std;

double area(double a) {
    return a*a;
}

void callArea() {
    double a;
    cout << "Введите длину стороны квадрата" << endl;
    cin >> a;
    cout << "Площадь квадрата при стороне " << a << " составляет: " << area(a) << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    for (int i = 0; i < 2; i++) {
        callArea();
    }
    return 0;
}