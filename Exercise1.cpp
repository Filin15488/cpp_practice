#include <iostream>
#include <string>

using namespace std;

// Функция с умалчиваемыми параметрами
void printStudent(const string& surname = "Иванов",
                  int course = 1,
                  const string& group = "A1")
{
    cout << "Фамилия: " << surname
         << ", курс: " << course
         << ", группа: " << group << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");

    cout << "1) Все параметры заданы явно:\n";
    printStudent("Петров", 2, "B3");

    cout << "\n2) Все параметры опущены (по умолчанию):\n";
    printStudent();

    cout << "\n3) Часть параметров задана явно, часть опущена:\n";
    printStudent("Сидоров");               // course и group берутся по умолчанию
    printStudent("Кузнецов", 3);    // group берётся по умолчанию

    return 0;
}