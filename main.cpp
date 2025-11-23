#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;


// --------- ФУНКЦИЯ 1: обработка char[] ---------
void processCharArray(char s[], int &digits, int &others) {
    int n = strlen(s);
    // Подсчёт
    for (int i =0; i < n; i++) {
        if (isdigit(s[i])) digits++;
        else others++;
    }
    // Создаём временную строку
    char *temp = new char[n + 1];
    int idx = 0;
    // сначала цифры
    for (int i = 0; i < n; i++) {
        if (isdigit(s[i])) temp[idx++] = s[i];
    }
    // потом остальные
    for (int i = 0; i < n; i++) {
        if (!isdigit(s[i])) temp[idx++] = s[i];
    }
    temp[idx] = '\0';
    // копируем обратно
    strcpy(s, temp);
    delete[] temp;
}

// --------- ФУНКЦИЯ 2: обработка char* ---------
void processCharPointer(char *s, int &digits, int &others) {
    int n = strlen(s);
    digits = others = 0;
    for (int i = 0; i < n; i++) {
        if (isdigit(s[i])) digits++;
        else others++;
    }
    char *temp = new char[n + 1];
    int idx = 0;

    for (int i = 0; i < n; i++) {
        if (isdigit(s[i])) temp[idx++] = s[i];
    }
    for (int i = 0; i < n; i++) {
        if (!isdigit(s[i])) temp[idx++] = s[i];
    }
    temp[idx] = '\0';
    strcpy(s, temp);
    delete[] temp;

}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");

    char s1[256];

    cout << "Введите строку: ";
    cin.getline(s1, 256);

    // Копия для второй функции
    char s2[256];
    strcpy(s2, s1);

    int d1, o1;
    int d2, o2;

    // ----- обработка char[] -----
    processCharArray(s1, d1, o1);

    // ----- обработка char* -----
    processCharPointer(s2, d2, o2);

    cout << "\n=== РЕЗУЛЬТАТЫ ===\n";
    cout << "\nРезультат (char[]): " << s1;
    cout << "\nЦифр: " << d1 << ", остальных: " << o1;

    cout << "\n\nРезультат (char*): " << s2;
    cout << "\nЦифр: " << d2 << ", остальных: " << o2 << endl;


    return 0;
}