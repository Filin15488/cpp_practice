#include <iostream>
#include <vector>

using namespace std;

// Шаблонная функция поиска индекса максимального элемента
template <typename T>
int maxIndex(const vector<T>& a) {
    int idx = 0;
    for (int i = 1; i < (int)a.size(); ++i) {
        if (a[i] > a[idx]) idx = i;
    }
    return idx; // индекс с 0
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

    // Вызов одной и той же шаблонной функции для разных типов
    int idxInt = maxIndex(ai);
    int idxFloat = maxIndex(af);
    int idxDouble = maxIndex(ad);

    cout << "\n=== Результаты ===\n";
    cout << "Номер максимального элемента (int)    : " << idxInt + 1 << "\n";
    cout << "Номер максимального элемента (float)  : " << idxFloat + 1 << "\n";
    cout << "Номер максимального элемента (double) : " << idxDouble + 1 << "\n";

    return 0;
}
