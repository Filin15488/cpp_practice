#include <iostream>
#include <cmath>

using namespace std;

// нерекурсивная функция
double sum_iter() {
    double s = 0.0;
    for (int x = 3; x <= 20; x++) {
        s += (2 * log(x)) / x;
    }
    return s;
}

// рекурсивная функция
double sum_rec(int x) {
    if (x > 20) return 0.0;
    return (2 * log(x)) / x + sum_rec(x + 1);
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");

    double iterative = sum_iter();
    double recursive = sum_rec(3);   // старт рекурсии с x=3

    cout << "Нерекурсивный вариант суммы: " << iterative << endl;
    cout << "Рекурсивный вариант суммы:   " << recursive << endl;

    return 0;
}
