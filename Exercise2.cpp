#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

enum figure_type {PARALLELOGRAM, CIRCLE, SQUARE};

struct figure {
    double area, perimeter;
    enum figure_type type;
    union {
        struct {
            double base;
            double height;
            double side;
        } parallelogram;
        double radius;
        double side_length;
    } geom_fig;
} fig;

int main() {
    int choice;

    setlocale(LC_ALL, "ru_RU.utf8");

    cout << "ВЫЧИСЛЕНИЕ ПЛОЩАДИ И ПЕРИМЕТРА ГЕОМЕТРИЧЕСКИХ ФИГУР" << endl;
    cout << "===============================================" << endl;
    cout << "Выберите тип фигуры:" << endl;
    cout << "1 - Параллелограмм" << endl;
    cout << "2 - Окружность" << endl;
    cout << "3 - Квадрат" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            fig.type = PARALLELOGRAM;
            cout << "Введите параметры параллелограмма:" << endl;
            cout << "Основание: ";
            cin >> fig.geom_fig.parallelogram.base;
            cout << "Высота: ";
            cin >> fig.geom_fig.parallelogram.height;
            cout << "Боковая сторона: ";
            cin >> fig.geom_fig.parallelogram.side;

            fig.area = fig.geom_fig.parallelogram.base * fig.geom_fig.parallelogram.height;
            fig.perimeter = 2 * (fig.geom_fig.parallelogram.base + fig.geom_fig.parallelogram.side);

            cout << "\nРезультат расчётов:" << endl;
            cout << "Площадь параллелограмма" << fixed << setprecision(2) << fig.area << endl;
            cout << "Периметр параллелограмма: " << fixed << setprecision(2) << fig.perimeter << endl;
            break;
        }

        case 2: {
            fig.type = CIRCLE;
            cout << "\nВведите параметры окружности:" << endl;
            cout << "Радиус: ";
            cin >> fig.geom_fig.radius;

            fig.area = M_PI * fig.geom_fig.radius * fig.geom_fig.radius;
            fig.perimeter = 2 * M_PI * fig.geom_fig.radius;

            cout << "\nРезультаты расчётов:" << endl;
            cout << "Площадь окружности: " << fixed << setprecision(2) << fig.area << endl;
            cout << "Длина окружности: " << fixed << setprecision(2) << fig.perimeter << endl;
            break;
        }

        case 3: {
            fig.type = SQUARE;
            cout << "\nВведите параметры квадрата:" << endl;
            cout << "Длина стороны: ";
            cin >> fig.geom_fig.side_length;

            fig.area = fig.geom_fig.side_length * fig.geom_fig.side_length;
            fig.perimeter = 4 * fig.geom_fig.side_length;

            cout << "\nРезультаты расчётов:" << endl;
            cout << "Площадь квадрата: " << fixed << setprecision(2) << fig.area << endl;
            cout << "Периметр квадрата: " << fixed << setprecision(2) << fig.perimeter << endl;
            break;
        }

        default:
            cout << "Ошибка! Некорректный ввод." << endl;
            return 1;
    }

    // Вывод типа фигуры
    cout << "\nТип фигуры: ";
    switch (fig.type) {
        case PARALLELOGRAM: cout << "Параллелограмма"; break;
        case CIRCLE: cout << "Окружность"; break;
        case SQUARE: cout << "Квадрат"; break;
    }
    cout << " (код: " << fig.type << ")" << endl;
    return 0;

}