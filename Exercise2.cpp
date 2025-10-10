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

    cout << "CALCULATION OF AREA AND PERIMETER OF GEOMETRIC FIGURES" << endl;
    cout << "===============================================" << endl;
    cout << "Select the type of figure:" << endl;
    cout << "1 - Parallelogram" << endl;
    cout << "2 - Circle" << endl;
    cout << "3 - Square" << endl;
    cout << "Your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            fig.type = PARALLELOGRAM;
            cout << "Enter the parallelogram parameters:" << endl;
            cout << "Base: ";
            cin >> fig.geom_fig.parallelogram.base;
            cout << "Height: ";
            cin >> fig.geom_fig.parallelogram.height;
            cout << "Side: ";
            cin >> fig.geom_fig.parallelogram.side;

            fig.area = fig.geom_fig.parallelogram.base * fig.geom_fig.parallelogram.height;
            fig.perimeter = 2 * (fig.geom_fig.parallelogram.base + fig.geom_fig.parallelogram.side);

            cout << "\nCALCULATION RESULTS:" << endl;
            cout << "Area of parallelogram: " << fixed << setprecision(2) << fig.area << endl;
            cout << "Perimeter of parallelogram: " << fixed << setprecision(2) << fig.perimeter << endl;
            break;
        }

        case 2: {
            fig.type = CIRCLE;
            cout << "\nEnter the circle parameters:" << endl;
            cout << "Radius: ";
            cin >> fig.geom_fig.radius;

            fig.area = M_PI * fig.geom_fig.radius * fig.geom_fig.radius;
            fig.perimeter = 2 * M_PI * fig.geom_fig.radius;

            cout << "\nCALCULATION RESULTS:" << endl;
            cout << "Area of a circle: " << fixed << setprecision(2) << fig.area << endl;
            cout << "Circumference: " << fixed << setprecision(2) << fig.perimeter << endl;
            break;
        }

        case 3: {
            fig.type = SQUARE;
            cout << "\nEnter the parameters of the square:" << endl;
            cout << "Side length: ";
            cin >> fig.geom_fig.side_length;

            fig.area = fig.geom_fig.side_length * fig.geom_fig.side_length;
            fig.perimeter = 4 * fig.geom_fig.side_length;

            cout << "\nCALCULATION RESULTS:" << endl;
            cout << "Area of a square: " << fixed << setprecision(2) << fig.area << endl;
            cout << "Perimeter of a square: " << fixed << setprecision(2) << fig.perimeter << endl;
            break;
        }

        default:
            cout << "Error! Incorrect choice." << endl;
            return 1;
    }

    // Вывод типа фигуры
    cout << "\nFigure type: ";
    switch (fig.type) {
        case PARALLELOGRAM: cout << "Parallelogram"; break;
        case CIRCLE: cout << "Circle"; break;
        case SQUARE: cout << "Square"; break;
    }
    cout << " (code: " << fig.type << ")" << endl;
    return 0;

}