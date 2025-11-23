#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// 1) Количество элементов, равных 0 (с учётом погрешности)
int countZeros(const vector<double>& a, double eps = 1e-9) {
    int count = 0;
    for (double x : a) {
        if (fabs(x) < eps) count++;
    }
    return count;
}


// 2) Сумма элементов после минимального элемента
double sumAfterMin(const vector<double>& a) {
    if (a.empty()) return 0.0;


    // индекс минимального элемента
    int minIndex = 0;
    for (int i =1; i< (int)a.size(); i++) {
        if (a[i] < a[minIndex]) minIndex = i;
    }

    double sum = 0.0;
    for (int i =minIndex; i<(int)a.size(); i++) {
        sum += a[i];
    }
    return sum;
}

// 3) Сортировка по возрастанию модулей
void sortByAbs(vector<double>& a) {
    sort(a.begin(), a.end(), [](double x, double y) {
        return fabs(x) < fabs(y);
    });
}

// Вспомогательная функция вывода массива
void printArray(const vector<double>& a) {
    for (double x: a) cout << x << " ";
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    cout << fixed << setprecision(2);

    int n;
    cout << "Введите n: ";
    cin >> n;

    vector<double> arr(n);
    cout << "Введите " << n << " вещественных элементов:\n";
    for (int i = 0; i < n; i++) cin >> arr[i];

    // 1) количество нулей
    int zeros = countZeros(arr);

    // 2) сумма после минимального
    double sumMin = sumAfterMin(arr);

    // 3) сортировка по модулям
    sortByAbs(arr);

    cout << "\nРезультаты:\n";
    cout << "Количество элементов, равных 0: " << zeros << "\n";
    cout << "Сумма элементов после минимального: " << sumMin << "\n";
    cout << "Массив после сортировки по возрастанию модулей:\n";
    printArray(arr);


    return 0;
}