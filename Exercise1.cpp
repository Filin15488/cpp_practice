#include <iostream>
#include <vector>

using namespace std;

// Перегрузка для int
int maxIndex(const vector<int>& a) {
    int idx = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i] > a[idx]) idx = i;
    }
    return idx; // индекс с 0
}

// Перегрузка для float
int maxIndex(const vector<float>& a) {
    int idx = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i] > a[idx]) idx = i;
    }
    return idx;
}

// Перегрузка для double
int maxIndex(const vector<double>& a) {
    int idx = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i] > a[idx]) idx = i;
    }
    return idx;
}
int main() {
    setlocale(LC_ALL, "ru_RU.utf8");

    int n;
    cout << "Введите размер массивов n: ";
    cin >> n;

    // ----- int массив -----
    vector<int> ai(n);
    cout << "\nВведите " << n << " целых элементов:\n";
    for (int i = 0; i < n; ++i) cin >> ai[i];

    // ----- float массив -----
    vector<float> af(n);
    cout << "\nВведите " << n << " вещественных (float) элементов:\n";
    for (int i = 0; i < n; ++i) cin >> af[i];

    // ----- double массив -----
    vector<double> ad(n);
    cout << "\nВведите " << n << " вещественных (double) элементов:\n";
    for (int i = 0; i < n; ++i) cin >> ad[i];

    // Поиск индекса максимума
    int idxInt = maxIndex(ai);
    int idxFloat = maxIndex(af);
    int idxDouble = maxIndex(ad);

    cout << "\n=== Результаты ===\n";
    cout << "Номер максимального элемента (int)    : " << idxInt + 1 << "\n";
    cout << "Номер максимального элемента (float)  : " << idxFloat + 1 << "\n";
    cout << "Номер максимального элемента (double) : " << idxDouble + 1 << "\n";

    return 0;
}