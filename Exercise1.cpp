#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

enum CORRECT {NO, YES} correct;

void check_correct(CORRECT correct, int &ball) {
    if (correct == YES) {
        ball++;
        cout << "Correct!" << endl;
    } else {
        cout << "Incorrect" << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int ball = 0;
    double result;

    cout << "TEST FOR CORRECT DIVISION PERFORMANCE" << endl;
    cout << "======================================" << endl;

    // Задание 1
    cout << "\nExercise 1: 15 / 3 = ";
    cin >> result;
    correct = (result == 5) ? YES : NO;
    check_correct(correct, ball);

    // Задание 2
    cout << "\nExercise 2: 24 / 6 = ";
    cin >> result;
    correct = (result == 4) ? YES : NO;
    check_correct(correct, ball);

    // Задание 3
    cout << "\nExercise 3: 100 / 25 = ";
    cin >> result;
    correct = (result == 4) ? YES : NO;
    check_correct(correct, ball);

    // Задание 4
    cout << "\nExercise 4: 81 / 9 = ";
    cin >> result;
    correct = (result == 9) ? YES : NO;
    check_correct(correct, ball);

    // Задание 5
    cout << "\nExercise 5: 56 / 7 = ";
    cin >> result;
    correct = (result == 8) ? YES : NO;
    check_correct(correct, ball);

    // Расчет результатов
    double percent = (ball * 100.0) / 5.0;
    int fivePointGrade;

    if (percent >= 85) fivePointGrade = 5;
    else if (percent >= 70) fivePointGrade = 4;
    else if (percent >= 50) fivePointGrade = 3;
    else fivePointGrade = 2;

    // Вывод результатов
    cout << "\n\nTEST RESULTS:" << endl;
    cout << "=================" << endl;
    cout << "Correct answers: " << ball << " out of 5" << endl;
    cout << "Percentage complete: " << fixed << setprecision(1) << percent << "%" << endl;
    cout << "Rating on a 5-point scale: " << fivePointGrade << endl;

    return 0;
}