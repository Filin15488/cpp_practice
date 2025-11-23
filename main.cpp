#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

// ===================== СТРУКТУРЫ =====================

// Для текстовых файлов удобно хранить string
struct StadiumText {
    string name;       // название
    string address;    // адрес
    int capacity;      // вместимость
    string sports;     // виды спорта (через запятую)
};

// Для бинарных файлов нужны фиксированные поля
struct StadiumBin {
    char name[64];
    char address[128];
    int capacity;
    char sports[128];
};

// ===================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ВВОДА =====================

void flushLine() {
    if (cin.peek() == '\n')
        cin.ignore();
}


StadiumText inputStadiumText() {
    StadiumText s;
    cout << "Название: ";
    flushLine();
    getline(cin, s.name);

    cout << "Адрес: ";
    getline(cin, s.address);

    cout << "Вместимость: ";
    cin >> s.capacity;

    cout << "Виды спорта: ";
    flushLine();
    getline(cin, s.sports);

    return s;
}

StadiumBin toBin(const StadiumText& t) {
    StadiumBin b{};
    strncpy(b.name, t.name.c_str(), sizeof(b.name) - 1);
    strncpy(b.address, t.address.c_str(), sizeof(b.address) - 1);
    b.capacity = t.capacity;
    strncpy(b.sports, t.sports.c_str(), sizeof(b.sports) - 1);
    return b;
}

StadiumText toText(const StadiumBin& b) {
    StadiumText t;
    t.name = b.name;
    t.address = b.address;
    t.capacity = b.capacity;
    t.sports = b.sports;
    return t;
}

void printStadium(const StadiumText& s, int idx) {
    cout << idx << ") "
         << "Название: " << s.name
         << " | Адрес: " << s.address
         << " | Вместимость: " << s.capacity
         << " | Виды спорта: " << s.sports << "\n";
}

// =====================================================
// 1) ТЕКСТ + FILE* (файловый указатель / stdio)
// =====================================================

const char* TEXT_C_FILE = "stadiums_c.txt";

void createTextFile_C(const vector<StadiumText>& arr) {
    FILE* f = fopen(TEXT_C_FILE, "w");
    for (auto& s : arr) {
        // пишем по строке на поле, плюс разделитель
        fprintf(f, "%s\n%s\n%d\n%s\n---\n",
                s.name.c_str(), s.address.c_str(), s.capacity, s.sports.c_str());
    }
    fclose(f);
}

vector<StadiumText> readTextFile_C() {
    vector<StadiumText> arr;
    FILE* f = fopen(TEXT_C_FILE, "r");
    if (!f) return arr;

    char buf[256];
    while (true) {
        StadiumText s;
        if (!fgets(buf, sizeof(buf), f)) break;
        buf[strcspn(buf, "\n")] = 0;
        s.name = buf;

        if (!fgets(buf, sizeof(buf), f)) break;
        buf[strcspn(buf, "\n")] = 0;
        s.address = buf;

        if (!fgets(buf, sizeof(buf), f)) break;
        s.capacity = atoi(buf);

        if (!fgets(buf, sizeof(buf), f)) break;
        buf[strcspn(buf, "\n")] = 0;
        s.sports = buf;

        fgets(buf, sizeof(buf), f); // читаем "---"
        arr.push_back(s);
    }
    fclose(f);
    return arr;
}

void writeTextFile_C(const vector<StadiumText>& arr) {
    createTextFile_C(arr); // перезапись тем же форматом
}

void deleteByName_TextC(const string& target) {
    auto arr = readTextFile_C();
    vector<StadiumText> out;
    for (auto& s : arr)
        if (s.name != target) out.push_back(s);
    writeTextFile_C(out);
}

void addK_TextC(int K) {
    auto arr = readTextFile_C();
    for (int i = 0; i < K; ++i) {
        cout << "\nДобавление записи #" << (i + 1) << "\n";
        arr.push_back(inputStadiumText());
    }
    writeTextFile_C(arr);
}

void showTextFile_C() {
    auto arr = readTextFile_C();
    cout << "\n--- Содержимое " << TEXT_C_FILE << " ---\n";
    if (arr.empty()) {
        cout << "(файл пуст)\n";
        return;
    }
    int idx = 1;
    for (auto& s : arr) printStadium(s, idx++);
}

// =====================================================
// 2) БИНАРЬ + FILE* (stdio)
// =====================================================

const char* BIN_C_FILE = "stadiums_c.bin";

void createBinFile_C(const vector<StadiumText>& arr) {
    FILE* f = fopen(BIN_C_FILE, "wb");
    for (auto& s : arr) {
        StadiumBin b = toBin(s);
        fwrite(&b, sizeof(StadiumBin), 1, f);
    }
    fclose(f);
}

vector<StadiumText> readBinFile_C() {
    vector<StadiumText> arr;
    FILE* f = fopen(BIN_C_FILE, "rb");
    if (!f) return arr;

    StadiumBin b;
    while (fread(&b, sizeof(StadiumBin), 1, f) == 1) {
        arr.push_back(toText(b));
    }
    fclose(f);
    return arr;
}

void writeBinFile_C(const vector<StadiumText>& arr) {
    createBinFile_C(arr);
}

void deleteByName_BinC(const string& target) {
    auto arr = readBinFile_C();
    vector<StadiumText> out;
    for (auto& s : arr)
        if (s.name != target) out.push_back(s);
    writeBinFile_C(out);
}

void addK_BinC(int K) {
    auto arr = readBinFile_C();
    for (int i = 0; i < K; ++i) {
        cout << "\nДобавление записи #" << (i + 1) << "\n";
        arr.push_back(inputStadiumText());
    }
    writeBinFile_C(arr);
}

void showBinFile_C() {
    auto arr = readBinFile_C();
    cout << "\n--- Содержимое " << BIN_C_FILE << " ---\n";
    if (arr.empty()) {
        cout << "(файл пуст)\n";
        return;
    }
    int idx = 1;
    for (auto& s : arr) printStadium(s, idx++);
}

// =====================================================
// 3) ТЕКСТ + fstream (потоки)
// =====================================================

const char* TEXT_CPP_FILE = "stadiums_cpp.txt";

void createTextFile_CPP(const vector<StadiumText>& arr) {
    ofstream out(TEXT_CPP_FILE);
    for (auto& s : arr) {
        out << s.name << "\n"
            << s.address << "\n"
            << s.capacity << "\n"
            << s.sports << "\n---\n";
    }
}

vector<StadiumText> readTextFile_CPP() {
    vector<StadiumText> arr;
    ifstream in(TEXT_CPP_FILE);
    if (!in) return arr;

    while (true) {
        StadiumText s;
        if (!getline(in, s.name)) break;
        if (!getline(in, s.address)) break;
        if (!(in >> s.capacity)) break;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!getline(in, s.sports)) break;

        string sep;
        getline(in, sep); // "---"
        arr.push_back(s);
    }
    return arr;
}

void writeTextFile_CPP(const vector<StadiumText>& arr) {
    createTextFile_CPP(arr);
}

void deleteByName_TextCPP(const string& target) {
    auto arr = readTextFile_CPP();
    vector<StadiumText> out;
    for (auto& s : arr)
        if (s.name != target) out.push_back(s);
    writeTextFile_CPP(out);
}

void addK_TextCPP(int K) {
    auto arr = readTextFile_CPP();
    for (int i = 0; i < K; ++i) {
        cout << "\nДобавление записи #" << (i + 1) << "\n";
        arr.push_back(inputStadiumText());
    }
    writeTextFile_CPP(arr);
}

void showTextFile_CPP() {
    auto arr = readTextFile_CPP();
    cout << "\n--- Содержимое " << TEXT_CPP_FILE << " ---\n";
    if (arr.empty()) {
        cout << "(файл пуст)\n";
        return;
    }
    int idx = 1;
    for (auto& s : arr) printStadium(s, idx++);
}

// =====================================================
// 4) БИНАРЬ + fstream (потоки)
// =====================================================

const char* BIN_CPP_FILE = "stadiums_cpp.bin";

void createBinFile_CPP(const vector<StadiumText>& arr) {
    ofstream out(BIN_CPP_FILE, ios::binary);
    for (auto& s : arr) {
        StadiumBin b = toBin(s);
        out.write((char*)&b, sizeof(b));
    }
}

vector<StadiumText> readBinFile_CPP() {
    vector<StadiumText> arr;
    ifstream in(BIN_CPP_FILE, ios::binary);
    if (!in) return arr;

    StadiumBin b;
    while (in.read((char*)&b, sizeof(b))) {
        arr.push_back(toText(b));
    }
    return arr;
}

void writeBinFile_CPP(const vector<StadiumText>& arr) {
    createBinFile_CPP(arr);
}

void deleteByName_BinCPP(const string& target) {
    auto arr = readBinFile_CPP();
    vector<StadiumText> out;
    for (auto& s : arr)
        if (s.name != target) out.push_back(s);
    writeBinFile_CPP(out);
}

void addK_BinCPP(int K) {
    auto arr = readBinFile_CPP();
    for (int i = 0; i < K; ++i) {
        cout << "\nДобавление записи #" << (i + 1) << "\n";
        arr.push_back(inputStadiumText());
    }
    writeBinFile_CPP(arr);
}

void showBinFile_CPP() {
    auto arr = readBinFile_CPP();
    cout << "\n--- Содержимое " << BIN_CPP_FILE << " ---\n";
    if (arr.empty()) {
        cout << "(файл пуст)\n";
        return;
    }
    int idx = 1;
    for (auto& s : arr) printStadium(s, idx++);
}

// =====================================================
// ОБЩЕЕ МЕНЮ
// =====================================================

int main() {
    setlocale(LC_ALL, "ru_RU.utf8");


    cout << "Выберите режим работы:\n"
         << "1) Текстовый файл + FILE*\n"
         << "2) Бинарный файл + FILE*\n"
         << "3) Текстовый файл + fstream\n"
         << "4) Бинарный файл + fstream\n"
         << "Ваш выбор: ";

    int mode;
    cin >> mode;

    while (true) {
        cout << "\nМеню:\n"
             << "1. Создать файл и записать данные\n"
             << "2. Вывести файл на экран\n"
             << "3. Удалить запись по названию\n"
             << "4. Добавить K записей в конец\n"
             << "5. Вывести измененный файл\n"
             << "0. Выход\n"
             << "Выбор: ";

        int cmd;
        cin >> cmd;
        if (cmd == 0) break;

        if (cmd == 1) {
            int n;
            cout << "Сколько записей создать? n = ";
            cin >> n;
            vector<StadiumText> arr;
            arr.reserve(n);
            for (int i = 0; i < n; ++i) {
                cout << "\nВвод записи #" << (i + 1) << "\n";
                arr.push_back(inputStadiumText());
            }

            if (mode == 1) createTextFile_C(arr);
            if (mode == 2) createBinFile_C(arr);
            if (mode == 3) createTextFile_CPP(arr);
            if (mode == 4) createBinFile_CPP(arr);
        }

        else if (cmd == 2 || cmd == 5) {
            if (mode == 1) showTextFile_C();
            if (mode == 2) showBinFile_C();
            if (mode == 3) showTextFile_CPP();
            if (mode == 4) showBinFile_CPP();
        }

        else if (cmd == 3) {
            cout << "Введите название стадиона для удаления: ";
            string target;
            flushLine();
            getline(cin, target);

            if (mode == 1) deleteByName_TextC(target);
            if (mode == 2) deleteByName_BinC(target);
            if (mode == 3) deleteByName_TextCPP(target);
            if (mode == 4) deleteByName_BinCPP(target);
        }

        else if (cmd == 4) {
            int K;
            cout << "Сколько записей добавить? K = ";
            cin >> K;

            if (mode == 1) addK_TextC(K);
            if (mode == 2) addK_BinC(K);
            if (mode == 3) addK_TextCPP(K);
            if (mode == 4) addK_BinCPP(K);
        }

        else {
            cout << "Неизвестная команда.\n";
        }
    }

    return 0;
}
