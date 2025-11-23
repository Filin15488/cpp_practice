#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// f(x) = 3x - 4lnx - 5
double f(double x) {
    return 3.0 * x - 4.0 * log(x) - 5.0;
}

// производная f'(x) = 3 - 4/x
double df(double x) {
    return 3.0 - 4.0 / x;
}

/*
  Метод Ньютона.
  f и df передаются как указатели на функции.
*/
double newtonMethod(double (*func)(double),
                    double (*dfunc)(double),
                    double a, double b,
                    double eps = 1e-6,
                    int maxIter = 100)
{
    // начальная точка — середина отрезка
    double x = (a + b) / 2.0;

    for (int iter = 0; iter < maxIter; ++iter) {
        double fx = func(x);
        double dfx = dfunc(x);

        // защита от деления на 0
        if (fabs(dfx) < 1e-12) {
            cerr << "Производная близка к нулю, метод остановлен.\n";
            break;
        }

        double xNext = x - fx / dfx;

        // условие остановки
        if (fabs(xNext - x) < eps) {
            return xNext;
        }

        x = xNext;
    }

    return x; // если дошли до maxIter
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    cout << fixed << setprecision(6);

    double a = 2.0, b = 4.0;

    double root = newtonMethod(f, df, a, b, 1e-6);

    cout << "Корень уравнения 3x - 4lnx - 5 = 0 на [" << a << "; " << b << "]\n";
    cout << "x ≈ " << root << endl;
    cout << "Проверка f(x) ≈ " << f(root) << endl;

    return 0;
}
