#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

using namespace std;

const double R = 8.32;

// Решение СЛАУ методом Гаусса
vector<double> gaussSolve(vector<vector<double>> A, vector<double> b) {
    int n = (int)A.size();

    for (int col = 0; col < n; ++col) {
        // partial pivoting
        int pivot = col;
        for (int row = col + 1; row < n; ++row)
            if (fabs(A[row][col]) > fabs(A[pivot][col]))
                pivot = row;

        swap(A[col], A[pivot]);
        swap(b[col], b[pivot]);

        if (fabs(A[col][col]) < 1e-12)
            throw runtime_error("СЛАУ вырождена.");

        for (int row = col + 1; row < n; ++row) {
            double factor = A[row][col] / A[col][col];
            for (int k = col; k < n; ++k)
                A[row][k] -= factor * A[col][k];
            b[row] -= factor * b[col];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        double s = b[i];
        for (int j = i + 1; j < n; ++j)
            s -= A[i][j] * x[j];
        x[i] = s / A[i][i];
    }
    return x;
}

// Метод выбранных точек
pair<double,double> methodChosenPoints(const vector<double>& x,
                                       const vector<double>& y) {
    int i = 0;
    int j = (int)x.size() - 1; // первая и последняя точки

    double a1 = (y[j] - y[i]) / (x[j] - x[i]);
    double a0 = y[i] - a1 * x[i];
    return {a0, a1};
}

// Метод средних
pair<double,double> methodMeans(const vector<double>& x,
                                const vector<double>& y) {
    int m = (int)x.size();
    int k = 2;         // два параметра => две группы
    int M = m / k;     // размер первой группы

    // группа 1: 0..M-1, группа 2: M..m-1
    vector<int> g1, g2;
    for (int i = 0; i < M; ++i) g1.push_back(i);
    for (int i = M; i < m; ++i) g2.push_back(i);

    auto buildEq = [&](const vector<int>& g) {
        double ng = (double)g.size();
        double sx = 0, sy = 0;
        for (int idx : g) {
            sx += x[idx];
            sy += y[idx];
        }
        return pair<vector<double>, double>({ng, sx}, sy);
    };

    auto eq1 = buildEq(g1);
    auto eq2 = buildEq(g2);

    vector<vector<double>> A = { eq1.first, eq2.first };
    vector<double> b = { eq1.second, eq2.second };

    vector<double> a = gaussSolve(A, b);
    return {a[0], a[1]};
}

// МНК (линейная регрессия)
pair<double,double> methodLeastSquares(const vector<double>& x,
                                       const vector<double>& y) {
    int m = (int)x.size();
    double sx = 0, sy = 0, sxx = 0, sxy = 0;

    for (int i = 0; i < m; ++i) {
        sx += x[i];
        sy += y[i];
        sxx += x[i] * x[i];
        sxy += x[i] * y[i];
    }

    vector<vector<double>> A = {
        { (double)m, sx },
        { sx, sxx }
    };
    vector<double> b = { sy, sxy };

    vector<double> a = gaussSolve(A, b);
    return {a[0], a[1]};
}

// расчет K по (a0,a1)
vector<double> calcK(const vector<double>& x, double a0, double a1) {
    vector<double> Kcalc(x.size());
    for (size_t i = 0; i < x.size(); ++i)
        Kcalc[i] = exp(a0 + a1 * x[i]);
    return Kcalc;
}

// погрешность δ
double calcError(const vector<double>& Kexp,
                 const vector<double>& Kcalc) {
    int N = (int)Kexp.size();
    double Kmax = *max_element(Kexp.begin(), Kexp.end());
    double Kmin = *min_element(Kexp.begin(), Kexp.end());
    double denom = N * fabs(Kmax - Kmin);

    double sum = 0;
    for (int i = 0; i < N; ++i)
        sum += fabs(Kcalc[i] - Kexp[i]);

    return sum / denom * 100.0;
}

int main() {
    cout << fixed << setprecision(6);

    // экспериментальные данные
    vector<double> T = {277.5, 282, 285, 290, 292, 295, 297.5};
    vector<double> Kexp = {1238, 1239, 1239.5, 1240, 1239.8, 1240.5, 1241};

    int m = (int)T.size();
    vector<double> x(m), y(m);

    for (int i = 0; i < m; ++i) {
        x[i] = 1.0 / T[i];
        y[i] = log(Kexp[i]);
    }

    // 3 метода
    auto [a0_vt, a1_vt] = methodChosenPoints(x, y);
    auto [a0_sr, a1_sr] = methodMeans(x, y);
    auto [a0_ls, a1_ls] = methodLeastSquares(x, y);

    // параметры k0 и E
    auto printParams = [&](string title, double a0, double a1) {
        double k0 = exp(a0);
        double E = -a1 * R;
        cout << title << ":\n";
        cout << "  a0 = " << a0 << ", a1 = " << a1 << "\n";
        cout << "  k0 = " << k0 << ", E = " << E << " кДж/моль\n\n";
    };

    printParams("Метод выбранных точек", a0_vt, a1_vt);
    printParams("Метод средних", a0_sr, a1_sr);
    printParams("Метод МНК", a0_ls, a1_ls);

    // расчетные значения
    auto K_vt = calcK(x, a0_vt, a1_vt);
    auto K_sr = calcK(x, a0_sr, a1_sr);
    auto K_ls = calcK(x, a0_ls, a1_ls);

    // ошибки
    double d_vt = calcError(Kexp, K_vt);
    double d_sr = calcError(Kexp, K_sr);
    double d_ls = calcError(Kexp, K_ls);

    // таблица
    cout << "Таблица результатов:\n";
    cout << "i   T       Kexp     K_vt     K_sr     K_lsq\n";
    for (int i = 0; i < m; ++i) {
        cout << setw(2) << i+1 << " "
             << setw(7) << T[i] << " "
             << setw(8) << Kexp[i] << " "
             << setw(8) << K_vt[i] << " "
             << setw(8) << K_sr[i] << " "
             << setw(8) << K_ls[i] << "\n";
    }

    cout << "\nПогрешности δ (%):\n";
    cout << "  выбранных точек = " << d_vt << "%\n";
    cout << "  средних         = " << d_sr << "%\n";
    cout << "  МНК             = " << d_ls << "%\n";

    return 0;
}
