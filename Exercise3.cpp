#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void hexagonAreaAndPrismVolume(double a, double h, double &area, double *volume) {
    area = (3.0 * sqrt(3.0) / 2.0) * a * a;
    if (volume != nullptr) {
        *volume = area * h;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    cout << fixed << setprecision(6);
    double a, h;
    double area, volume;

    cout << "Введите сторону правильного шестиугольника a: ";
    cin >> a;

    cout << "Введите высоту призмы h: ";
    cin >> h;

    hexagonAreaAndPrismVolume(a, h, area, &volume);

    cout << "\nРезультаты:\n";
    cout << "Площадь шестиугольника S = " << area << endl;
    cout << "Объем призмы V = " << volume << endl;

    return 0;
}