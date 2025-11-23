#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Решение СЛАУ методом Гаусса (с частичным выбором главного элемента)
vector<double> gaussSolve(vector<vector<double>> A, vector<double> b) {
    int n = (int)A.size();

    for (int col = 0; col < n; ++col) {
        // 1) поиск главного элемента в текущем столбце
        int pivot = col;
        for (int row = col + 1; row < n; ++row) {
            if (fabs(A[row][col]) > fabs(A[pivot][col]))
                pivot = row;
        }

        // 2) перестановка строк
        swap(A[col], A[pivot]);
        swap(b[col], b[pivot]);

        // 3) проверка на вырожденность
        if (fabs(A[col][col]) < 1e-12) {
            throw runtime_error("Система вырождена или плохо обусловлена.");
        }

        // 4) прямой ход: зануляем элементы ниже диагонали
        for (int row = col + 1; row < n; ++row) {
            double factor = A[row][col] / A[col][col];
            for (int k = col; k < n; ++k)
                A[row][k] -= factor * A[col][k];
            b[row] -= factor * b[col];
        }
    }

    // обратный ход
    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = b[i];
        for (int j = i + 1; j < n; ++j)
            sum -= A[i][j] * x[j];
        x[i] = sum / A[i][i];
    }
    return x;
}

// вычисление значения полинома
double polyValue(double t, const vector<double>& a) {
    // a[0] + a[1]*t + a[2]*t^2
    double res = 0.0;
    double p = 1.0;
    for (double coeff : a) {
        res += coeff * p;
        p *= t;
    }
    return res;
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    cout << fixed << setprecision(6);

    vector<double> t = {32, 70, 100};
    vector<double> R = {85, 92, 98};
    double tk = 38; // контрольная температура

    int m = (int)t.size();
    int n = m; // степень полинома n-1 = 2, коэффициентов m = 3

    // Составляем матрицу Вандермонда для степенного полинома
    vector<vector<double>> A(n, vector<double>(n));
    for (int i = 0; i < n; ++i) {
        double powT = 1.0;
        for (int j = 0; j < n; ++j) {
            A[i][j] = powT;
            powT *= t[i];
        }
    }

    // Решаем систему A * a = R
    vector<double> a = gaussSolve(A, R);

    cout << "Коэффициенты полинома R(t) = a0 + a1*t + a2*t^2:\n";
    for (int i = 0; i < n; ++i)
        cout << "a" << i << " = " << a[i] << "\n";

    double Rk = polyValue(tk, a);
    cout << "\nСопротивление при t_k = " << tk << " °C:\n";
    cout << "R(" << tk << ") = " << Rk << " Ом\n";

    return 0;
}