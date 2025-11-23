#include <iostream>
#include <cstdarg>
using namespace std;

// --------------------------------------------------------
// Известно количество параметров
// --------------------------------------------------------
double avgOdd_knownCount(int count, ...) {
    va_list args;
    va_start(args, count);

    long long sum = 0;
    int oddCount = 0;

    for (int i = 0; i < count; ++i) {
        int x = va_arg(args, int);
        if (x % 2 != 0) {   // нечётное
            sum += x;
            oddCount++;
        }
    }

    va_end(args);

    if (oddCount == 0) return 0.0;
    return (double)sum / oddCount;
}

// --------------------------------------------------------
// Известен признак конца списка параметров
// sentinel = 0
// --------------------------------------------------------
double avgOdd_sentinel(int first, ...) {
    if (first == 0) return 0.0; // сразу конец

    va_list args;
    va_start(args, first);

    long long sum = 0;
    int oddCount = 0;

    int x = first;
    while (x != 0) {  // 0 = конец списка
        if (x % 2 != 0) {
            sum += x;
            oddCount++;
        }
        x = va_arg(args, int);
    }

    va_end(args);

    if (oddCount == 0) return 0.0;
    return (double)sum / oddCount;
}

// --------------------------------------------------------

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== Известно количество параметров ===\n";
    cout << "avgOdd_knownCount(6, 1,2,3,4,5,6) = "
         << avgOdd_knownCount(6, 1, 2, 3, 4, 5, 6) << endl;

    cout << "avgOdd_knownCount(4, 10,12,14,16) = "
         << avgOdd_knownCount(4, 10, 12, 14, 16) << endl;

    cout << "avgOdd_knownCount(5, 7,9,2,4,11) = "
         << avgOdd_knownCount(5, 7, 9, 2, 4, 11) << endl;

    cout << "\n=== Признак конца списка (sentinel = 0) ===\n";
    cout << "avgOdd_sentinel(1,2,3,4,5,0) = "
         << avgOdd_sentinel(1, 2, 3, 4, 5, 0) << endl;

    cout << "avgOdd_sentinel(8,6,4,2,0) = "
         << avgOdd_sentinel(8, 6, 4, 2, 0) << endl;

    cout << "avgOdd_sentinel(13,0) = "
         << avgOdd_sentinel(13, 0) << endl;

    return 0;
}
