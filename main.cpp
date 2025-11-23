#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct TankRecord {
    int tankCode;            // шифр ёмкости
    string tankName;         // наименование ёмкости
    double maxVolume;        // максимальный объём (м^3 или л — как решишь)

    int productCode;         // шифр продукта
    string productName;      // наименование продукта
    double density;          // плотность продукта (кг/м^3)
    double mass;             // масса в ёмкости (кг)

    // вычисляемые поля (не храним, а считаем по месту)
    double currentVolume() const {
        return (density != 0.0) ? (mass / density) : 0.0;
    }
    double fillPercent() const {
        return (maxVolume != 0.0) ? (currentVolume() / maxVolume * 100.0) : 0.0;
    }
};


void inputRecords(vector<TankRecord>& recs, int n) {
    recs.resize(n);
    for (int i = 0; i < n; ++i) {
        cout << "\n=== Запись #" << i + 1 << " ===\n";
        cout << "Шифр ёмкости: ";
        cin >> recs[i].tankCode;

        cout << "Наименование ёмкости: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, recs[i].tankName);

        cout << "Максимальный объём ёмкости: ";
        cin >> recs[i].maxVolume;

        cout << "Шифр продукта: ";
        cin >> recs[i].productCode;

        cout << "Наименование продукта: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, recs[i].productName);

        cout << "Плотность продукта: ";
        cin >> recs[i].density;

        cout << "Масса продукта в ёмкости: ";
        cin >> recs[i].mass;
    }
}

void printRecords(const vector<TankRecord>& recs) {
    cout << "\n------ Список ёмкостей ------\n";
    cout << left
         << setw(8)  << "TankID"
         << setw(18) << "TankName"
         << setw(12) << "MaxVol"
         << setw(8)  << "ProdID"
         << setw(18) << "ProdName"
         << setw(10) << "Density"
         << setw(10) << "Mass"
         << setw(12) << "CurVol"
         << setw(10) << "Fill(%)"
         << "\n";

    for (const auto& r : recs) {
        cout << left
             << setw(8)  << r.tankCode
             << setw(18) << r.tankName.substr(0,17)
             << setw(12) << r.maxVolume
             << setw(8)  << r.productCode
             << setw(18) << r.productName.substr(0,17)
             << setw(10) << r.density
             << setw(10) << r.mass
             << setw(12) << r.currentVolume()
             << setw(10) << r.fillPercent()
             << "\n";
    }
}

// Сумма масс
double sumMass(const vector<TankRecord>& recs) {
    double s = 0.0;
    for (auto& r : recs) s += r.mass;
    return s;
}

// Средняя масса
double avgMass(const vector<TankRecord>& recs) {
    if (recs.empty()) return 0.0;
    return sumMass(recs) / recs.size();
}

// Минимальная масса (возвращаем значение)
double minMass(const vector<TankRecord>& recs) {
    if (recs.empty()) return 0.0;
    double mn = recs[0].mass;
    for (auto& r : recs) mn = min(mn, r.mass);
    return mn;
}

// Максимальная масса
double maxMass(const vector<TankRecord>& recs) {
    if (recs.empty()) return 0.0;
    double mx = recs[0].mass;
    for (auto& r : recs) mx = max(mx, r.mass);
    return mx;
}

// Суммарный текущий объём
double sumCurrentVolume(const vector<TankRecord>& recs) {
    double s = 0.0;
    for (auto& r : recs) s += r.currentVolume();
    return s;
}

// Средний текущий объём
double avgCurrentVolume(const vector<TankRecord>& recs) {
    if (recs.empty()) return 0.0;
    return sumCurrentVolume(recs) / recs.size();
}

// Минимальный % заполнения
double minFillPercent(const vector<TankRecord>& recs) {
    if (recs.empty()) return 0.0;
    double mn = recs[0].fillPercent();
    for (auto& r : recs) mn = min(mn, r.fillPercent());
    return mn;
}

// Максимальный % заполнения
double maxFillPercent(const vector<TankRecord>& recs) {
    if (recs.empty()) return 0.0;
    double mx = recs[0].fillPercent();
    for (auto& r : recs) mx = max(mx, r.fillPercent());
    return mx;
}

// Средний % заполнения
double avgFillPercent(const vector<TankRecord>& recs) {
    if (recs.empty()) return 0.0;
    double s = 0.0;
    for (auto& r : recs) s += r.fillPercent();
    return s / recs.size();
}


int main() {
    cout << fixed << setprecision(3);

    int n;
    cout << "Введите количество ёмкостей: ";
    cin >> n;

    vector<TankRecord> recs;
    inputRecords(recs, n);

    printRecords(recs);

    cout << "\n------ Расчёт показателей ------\n";

    cout << "Масса (кг):\n";
    cout << "  sum  = " << sumMass(recs) << "\n";
    cout << "  avg  = " << avgMass(recs) << "\n";
    cout << "  min  = " << minMass(recs) << "\n";
    cout << "  max  = " << maxMass(recs) << "\n";

    cout << "Текущий объём (в тех же единицах, что и maxVolume):\n";
    cout << "  sum  = " << sumCurrentVolume(recs) << "\n";
    cout << "  avg  = " << avgCurrentVolume(recs) << "\n";

    cout << "Процент заполнения (%):\n";
    cout << "  avg  = " << avgFillPercent(recs) << "\n";
    cout << "  min  = " << minFillPercent(recs) << "\n";
    cout << "  max  = " << maxFillPercent(recs) << "\n";

    return 0;
}