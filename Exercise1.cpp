#include <iostream>
#include <cmath>

using namespace std;

// ===== Рекурсивная версия =====
// степенной ряд
// a_n = 4^(n-1)
long long term_rec(int n) {
    if (n == 1) return 1;          // базовый случай: a1 = 1
    return 4 * term_rec(n - 1);    // рекурсия
}

// ===== Нерекурсивная версия =====
long long term_iter(int n) {
    long long a = 1;               // a1 = 1
    for (int i = 2; i <= n; i++) {
        a *= 4;
    }
    return a;
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    int n;
    cout << "Введите номер n-го члена ряда: ";
    cin >> n;

    cout << "\nРекурсивный вариант: a_" << n << " = " << term_rec(n) << endl;
    cout << "Нерекурсивный вариант: a_" << n << " = " << term_iter(n) << endl;

    return 0;
}