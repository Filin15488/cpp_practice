#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

struct Point {
    double t;
    double x;
};

// тип указателя на правую часть dx/dt = f(t, x)
using RHS = double (*)(double, double);

// ---------- Правая часть ОДУ ----------
double f(double t, double x) {
    return cos(t) + 0.5 * x * x * x;
}

// ---------- 1) Метод Эйлера ----------
vector<Point> euler_iter(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);

    double t = t0, x = x0;
    res.push_back({t, x});

    for (int i = 0; i < N; ++i) {
        x = x + dt * f(t, x);
        t = t + dt;
        res.push_back({t, x});
    }
    return res;
}

void euler_rec_impl(RHS f, int i, int N, double t, double x, double dt, vector<Point>& res) {
    if (i == N) return;
    double xNext = x + dt * f(t, x);
    double tNext = t + dt;
    res.push_back({tNext, xNext});
    euler_rec_impl(f, i + 1, N, tNext, xNext, dt, res);
}

vector<Point> euler_rec(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);
    res.push_back({t0, x0});
    euler_rec_impl(f, 0, N, t0, x0, dt, res);
    return res;
}

// ---------- 2) Модифицированный Эйлер (предиктор–корректор) ----------
vector<Point> modEuler_iter(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);

    double t = t0, x = x0;
    res.push_back({t, x});

    for (int i = 0; i < N; ++i) {
        double k1 = f(t, x);
        double xPred = x + dt * k1;               // предиктор (Эйлер)
        double k2 = f(t + dt, xPred);             // наклон в конце шага
        x = x + dt * (k1 + k2) / 2.0;             // корректор
        t = t + dt;
        res.push_back({t, x});
    }
    return res;
}

void modEuler_rec_impl(RHS f, int i, int N, double t, double x, double dt, vector<Point>& res) {
    if (i == N) return;
    double k1 = f(t, x);
    double xPred = x + dt * k1;
    double k2 = f(t + dt, xPred);
    double xNext = x + dt * (k1 + k2) / 2.0;
    double tNext = t + dt;
    res.push_back({tNext, xNext});
    modEuler_rec_impl(f, i + 1, N, tNext, xNext, dt, res);
}

vector<Point> modEuler_rec(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);
    res.push_back({t0, x0});
    modEuler_rec_impl(f, 0, N, t0, x0, dt, res);
    return res;
}

// ---------- 3) Эйлер–Коши (серединный / Heun midpoint) ----------
vector<Point> eulerCauchy_iter(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);

    double t = t0, x = x0;
    res.push_back({t, x});

    for (int i = 0; i < N; ++i) {
        double k1 = f(t, x);
        double xMid = x + dt/2.0 * k1;            // значение в середине шага
        double kMid = f(t + dt/2.0, xMid);
        x = x + dt * kMid;
        t = t + dt;
        res.push_back({t, x});
    }
    return res;
}

void eulerCauchy_rec_impl(RHS f, int i, int N, double t, double x, double dt, vector<Point>& res) {
    if (i == N) return;
    double k1 = f(t, x);
    double xMid = x + dt/2.0 * k1;
    double kMid = f(t + dt/2.0, xMid);
    double xNext = x + dt * kMid;
    double tNext = t + dt;
    res.push_back({tNext, xNext});
    eulerCauchy_rec_impl(f, i + 1, N, tNext, xNext, dt, res);
}

vector<Point> eulerCauchy_rec(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);
    res.push_back({t0, x0});
    eulerCauchy_rec_impl(f, 0, N, t0, x0, dt, res);
    return res;
}

// ---------- 4) Рунге–Кутта 4-го порядка ----------
vector<Point> rk4_iter(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);

    double t = t0, x = x0;
    res.push_back({t, x});

    for (int i = 0; i < N; ++i) {
        double k1 = f(t, x);
        double k2 = f(t + dt/2.0, x + dt/2.0 * k1);
        double k3 = f(t + dt/2.0, x + dt/2.0 * k2);
        double k4 = f(t + dt,     x + dt * k3);

        x = x + dt * (k1 + 2*k2 + 2*k3 + k4) / 6.0;
        t = t + dt;
        res.push_back({t, x});
    }
    return res;
}

void rk4_rec_impl(RHS f, int i, int N, double t, double x, double dt, vector<Point>& res) {
    if (i == N) return;

    double k1 = f(t, x);
    double k2 = f(t + dt/2.0, x + dt/2.0 * k1);
    double k3 = f(t + dt/2.0, x + dt/2.0 * k2);
    double k4 = f(t + dt,     x + dt * k3);

    double xNext = x + dt * (k1 + 2*k2 + 2*k3 + k4) / 6.0;
    double tNext = t + dt;
    res.push_back({tNext, xNext});
    rk4_rec_impl(f, i + 1, N, tNext, xNext, dt, res);
}

vector<Point> rk4_rec(RHS f, double t0, double x0, double tk, double dt) {
    int N = (int)round((tk - t0) / dt);
    vector<Point> res;
    res.reserve(N + 1);
    res.push_back({t0, x0});
    rk4_rec_impl(f, 0, N, t0, x0, dt, res);
    return res;
}

// ---------- Вспомогательный вывод таблицы ----------
void printTable(const string& title, const vector<Point>& v) {
    cout << "\n" << title << "\n";
    cout << " i    t_i       x_i\n";
    for (int i = 0; i < (int)v.size(); ++i) {
        cout << setw(2) << i << "  "
             << setw(6) << v[i].t << "   "
             << setw(10) << v[i].x << "\n";
    }
}

// ---------- MAIN ----------
int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    cout << fixed << setprecision(6);

    double t0 = 0.0, tk = 2.0, x0 = -1.0;
    double dt0 = 0.1;

    vector<double> dts = { dt0/2.0, dt0, dt0*2.0 };

    cout << "ОДУ: x' = cos(t) + 0.5*x^3,  t in [0,2],  x(0)=-1\n";

    // Для базового dt выводим таблицы (итерационные версии)
    {
        auto v1 = euler_iter(f, t0, x0, tk, dt0);
        auto v2 = modEuler_iter(f, t0, x0, tk, dt0);
        auto v3 = eulerCauchy_iter(f, t0, x0, tk, dt0);
        auto v4 = rk4_iter(f, t0, x0, tk, dt0);

        printTable("Метод Эйлера (итерац.), dt=0.1", v1);
        printTable("Модифицированный Эйлер (итерац.), dt=0.1", v2);
        printTable("Эйлер–Коши (итерац.), dt=0.1", v3);
        printTable("Рунге–Кутта 4 (итерац.), dt=0.1", v4);
    }

    // Сравнение точности по разным dt (финальные значения)
    cout << "\nСравнение конечного x(tk) при разных dt:\n";
    cout << "dt      Euler      ModEuler   Euler-Cauchy   RK4\n";

    for (double dt : dts) {
        auto e  = euler_iter(f, t0, x0, tk, dt);
        auto me = modEuler_iter(f, t0, x0, tk, dt);
        auto ec = eulerCauchy_iter(f, t0, x0, tk, dt);
        auto rk = rk4_iter(f, t0, x0, tk, dt);

        cout << setw(5) << dt << "  "
             << setw(10) << e.back().x << "  "
             << setw(10) << me.back().x << "  "
             << setw(14) << ec.back().x << "  "
             << setw(10) << rk.back().x << "\n";
    }

    // Пример: проверить, что рекурсивные дают то же, что и итерационные (dt=0.1)
    {
        auto e_i = euler_iter(f, t0, x0, tk, dt0);
        auto e_r = euler_rec (f, t0, x0, tk, dt0);
        cout << "\nПроверка (dt=0.1): Euler итерац. = " << e_i.back().x
             << ", Euler рекурс. = " << e_r.back().x << "\n";
    }

    return 0;
}
