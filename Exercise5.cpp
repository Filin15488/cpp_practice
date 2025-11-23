#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// 1) Количество отрицательных элементов в строках, содержащих хотя бы один ноль
int countNegativesInZeroRows(const vector<vector<int>>& A) {
    int n = (int)A.size();
    int m = n ? (int)A[0].size() : 0;

    int count = 0;
    for (int i = 0; i < n; i++) {
        bool hasZero = false;
        for (int j = 0; j < m; j++) {
            if (A[i][j] == 0) {
                hasZero = true;
                break;
            }
        }

        if (hasZero) {
            for (int j = 0; j < m; j++) {
                if (A[i][j] < 0) count++;
            }
        }
    }
    return count;
}


// 2) Поиск всех седловых точек
/**
 * @return список пар (i, j) — индексы седловых точек
 */
vector<pair<int, int>> findSaddlePoints(const vector<vector<int>>& A) {
    int n = (int)A.size();
    int m = n ? (int)A[0].size() : 0;

    vector<int> rowMin(n);
    vector<int> colMax(m);

    // минимумы по строкам
    for (int i = 0; i < n; i++) {
        rowMin[i] = A[i][0];
        for (int j = 1; j < m; j++) {
            if (A[i][j] < rowMin[i]) rowMin[i] = A[i][j];
        }
    }

    // максимумы по столбцам
    for (int j = 0; j < m; j++) {
        colMax[j] = A[0][j];
        for (int i = 1; i < n; i++) {
            if (A[i][j] > colMax[j]) colMax[j] = A[i][j];
        }
    }

    // седловые точки: min в строке и max в столбце одновременно
    vector<pair<int,int>> saddles;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (A[i][j] == rowMin[i] && A[i][j] == colMax[j]) {
                saddles.push_back({i, j});
            }
        }
    }

    return saddles;
}

// Ввод матрицы
vector<vector<int>> readMatrix(int n, int m) {
    vector<vector<int>> A(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> A[i][j];
    return A;
}

// Вывод матрицы (необязательно, но удобно)
void printMatrix(const vector<vector<int>>& A) {
    for (auto& row : A) {
        for (int x : row) cout << setw(4) << x;
        cout << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");
    cout << fixed << setprecision(2);


    int n, m;
    cout << "Введите размеры матрицы n m: ";
    cin >> n >> m;

    cout << "Введите матрицу " << n << "x" << m << ":\n";
    vector<vector<int>> A = readMatrix(n, m);

    cout << "\nМатрица:\n";
    printMatrix(A);

    // 1)
    int negCount = countNegativesInZeroRows(A);

    // 2)
    vector<pair<int,int>> saddles = findSaddlePoints(A);

    cout << "\nРезультаты:\n";
    cout << "1) Кол-во отрицательных элементов в строках с нулём: "
         << negCount << "\n";

    cout << "2) Седловые точки (номер строки, номер столбца):\n";
    if (saddles.empty()) {
        cout << "   Седловых точек нет.\n";
    } else {
        for (auto [i, j] : saddles) {
            cout << "   (" << i + 1 << ", " << j + 1 << ")"
                 << "  значение = " << A[i][j] << "\n";
        }
    }

    return 0;
}