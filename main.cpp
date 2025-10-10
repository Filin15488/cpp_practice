#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstring>
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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int N = 2;
    NOTE notes[N];
    NOTE buffer;

    cout << "Enter information about " << N << " people:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "People " << i + 1 << ":" << endl;
        cout << "SecondName: ";
        cin >> notes[i].surname;
        cout << "Name: ";
        cin >> notes[i].name;
        cout << "Phone number: ";
        cin >> notes[i].phone;
        cout << "Date of birth (day, month, year, separated by spaces): ";
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
    cout << "\nSorted list by first three digits of phone number:\n";
    cout << setw(15) << "SecondName" << setw(10) << "Name"
         << setw(15) << "Phone" << setw(15) << "Birthdate" << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(15) << notes[i].surname << setw(10) << notes[i].name
             << setw(15) << notes[i].phone << setw(10)
             << notes[i].birthDate[0] << "." << notes[i].birthDate[1] << "." << notes[i].birthDate[2] << endl;
    }

    // Поиск по фамилии
    char searchSurname[20];
    cout << "\nEnter your lastname to search: ";
    cin >> searchSurname;

    bool found = false;
    cout << "\nSearch results:\n";
    for (int i = 0; i < N; i++) {
        if (strcmp(notes[i].surname, searchSurname) == 0) {
            cout << "Find: " << notes[i].surname << " " << notes[i].name
                 << ", phone.: " << notes[i].phone
                 << ", birthdate: " << notes[i].birthDate[0] << "."
                 << notes[i].birthDate[1] << "." << notes[i].birthDate[2] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "A man with the last name '" << searchSurname << "' not found." << endl;
    }

    return 0;
}