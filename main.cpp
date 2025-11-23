#include <iostream>
using namespace std;

// узел списка
struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

// добавление в конец
void pushBack(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = newNode;
}

// вывод списка
void printList(Node* head) {
    cout << "Список: ";
    for (Node* p = head; p; p = p->next)
        cout << p->data << " ";
    cout << "\n";
}

// вставка 10 после первого отрицательного
void insertAfterFirstNegative(Node* head) {
    Node* p = head;
    while (p) {
        if (p->data < 0) {
            Node* newNode = new Node(10);
            newNode->next = p->next;
            p->next = newNode;
            return;
        }
        p = p->next;
    }
    cout << "Отрицательных элементов нет, вставка не выполнена.\n";
}

// очистка списка
void freeList(Node*& head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    Node* head = nullptr;

    int n;
    cout << "Введите количество элементов списка: ";
    cin >> n;

    cout << "Введите элементы списка:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pushBack(head, x);
    }

    cout << "\nДо вставки:\n";
    printList(head);

    insertAfterFirstNegative(head);

    cout << "После вставки:\n";
    printList(head);

    freeList(head);
    return 0;
}