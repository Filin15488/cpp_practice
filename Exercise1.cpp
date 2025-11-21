#include <iostream>
#include <iomanip>
using namespace std;

enum CORRECT {NO, YES} correct;

void check_correct(CORRECT correct, int &ball) {
    if (correct == YES) {
        ball++;
        cout << "Правильно!" << endl;
    } else {
        cout << "Неправильно" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");

    int ball = 0;
    double result;

    cout << "ТЕСТ НА ПРАВИЛЬНОСТЬ ВЫПОЛНЕНИЯ ДЕЛЕНИЯ" << endl;
    cout << "======================================" << endl;

    // Задание 1
    cout << "\nУпражнение 1: 15 / 3 = ";
    cin >> result;
    correct = (result == 5) ? YES : NO;
    check_correct(correct, ball);

    // Задание 2
    cout << "\nУпражнение 2: 24 / 6 = ";
    cin >> result;
    correct = (result == 4) ? YES : NO;
    check_correct(correct, ball);

    // Задание 3
    cout << "\nУпражнение 3: 100 / 25 = ";
    cin >> result;
    correct = (result == 4) ? YES : NO;
    check_correct(correct, ball);

    // Задание 4
    cout << "\nУпражнение 4: 81 / 9 = ";
    cin >> result;
    correct = (result == 9) ? YES : NO;
    check_correct(correct, ball);

    // Задание 5
    cout << "\nУпражнение 5: 56 / 7 = ";
    cin >> result;
    correct = (result == 8) ? YES : NO;
    check_correct(correct, ball);

    // Расчет результатов
    double percent = (ball * 100.0) / 5.0;
    int fivePointGrade;

    if (percent >= 85) fivePointGrade = 5;
    else if (percent >= 75) fivePointGrade = 4;
    else if (percent >= 60) fivePointGrade = 3;
    else fivePointGrade = 2;

    // Вывод результатов
    cout << "\n\nРЕЗУЛЬТАТЫ ТЕСТА:" << endl;
    cout << "=================" << endl;
    cout << "Правильные ответы: " << ball << " из 5" << endl;
    cout << "Процент завершения: " << fixed << setprecision(1) << percent << "%" << endl;
    cout << "Оценка по 5-балльной шкале: " << fivePointGrade << endl;

    return 0;
}