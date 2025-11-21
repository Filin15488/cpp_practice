#include <iostream>
#include <iomanip>
#include <cstring>
#include <locale>
using namespace std;

struct NOTE {
    char surname[20];
    char name[20];
    char phone[15];
    int birthDate[3];
};

// Функция для получения первых трех цифр номера телефона
int getFirstThreeDigits(const char* phone) {
    int count = 0;
    int result = 0;
    for (int i = 0; phone[i] != '\0' && count < 3; i++) {
        if (isdigit(phone[i])) {
            result = result * 10 + (phone[i] - '0');
            count++;
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");

    const int N = 6;
    NOTE notes[N];
    NOTE buffer;

    cout << "Введите информацию о " << N << " людях:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "Человек " << i + 1 << ":" << endl;
        cout << "Фамилия: ";
        cin >> notes[i].surname;
        cout << "Имя: ";
        cin >> notes[i].name;
        cout << "Номер телефона: ";
        cin >> notes[i].phone;
        cout << "Дата рождения (день, месяц, год, разделённые пробелом): ";
        cin >> notes[i].birthDate[0] >> notes[i].birthDate[1] >> notes[i].birthDate[2];
        cout << endl;
    }

    // Сортировка по первым трем цифрам номера телефона (пузырьковая сортировка)
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            int digits1 = getFirstThreeDigits(notes[j].phone);
            int digits2 = getFirstThreeDigits(notes[j + 1].phone);
            if (digits1 > digits2) {
                buffer = notes[j];
                notes[j] = notes[j + 1];
                notes[j + 1] = buffer;
            }
        }
    }

    // Вывод отсортированного массива
    cout << "\nСписок, отсортированный по первым трём цифрам номеров телефонов:\n";
    cout << left; // выравнивание по левому краю

    cout << "\t" << "Фамилия"
         << "\t" << "\t" << "Имя"
         << "\t" << "\t" << "Номер телефона"
         << "\t" << "\t" << "Дата рождения" << endl;

    for (int i = 0; i < N; i++) {
        char birthStr[12];
        snprintf(birthStr, sizeof(birthStr), "%02d.%02d.%04d",
                 notes[i].birthDate[0], notes[i].birthDate[1], notes[i].birthDate[2]);

        cout << "\t" << notes[i].surname
             << "\t" << "\t" << notes[i].name
             << "\t" << "\t" << notes[i].phone
             << "\t" << "\t" << birthStr << endl;
    }

    // Поиск по фамилии
    char searchSurname[20];
    cout << "\nВведите фамилию для поиска: ";
    cin >> searchSurname;

    bool found = false;
    cout << "\nРезультат поиска:\n";
    for (int i = 0; i < N; i++) {
        if (strcmp(notes[i].surname, searchSurname) == 0) {
            cout << "Найден: " << notes[i].surname << " " << notes[i].name
                 << ", телефон: " << notes[i].phone
                 << ", дата рождения: " << notes[i].birthDate[0] << "."
                 << notes[i].birthDate[1] << "." << notes[i].birthDate[2] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Человек с фамилией '" << searchSurname << "' не найден." << endl;
    }

    return 0;
}