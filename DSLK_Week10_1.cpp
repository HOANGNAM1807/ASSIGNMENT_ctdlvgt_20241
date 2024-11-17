#include <iostream>
using namespace std;

// Cau truc node trong danh sach lien ket
struct Node {
    int data;      
    Node* next;    
};

// Danh sach lien ket don
Node* head = nullptr;

// Ham them node vao cuoi danh sach
void addNode(int value) {
    Node* newNode = new Node{value, nullptr};
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newNode;
}

// Ham hien thi danh sach
void displayList() {
    if (head == nullptr) {
        cout << "Danh sach rong.\n";
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL\n";
}

// Xoa node dau danh sach
void deleteFirst() {
    if (head == nullptr) {
        cout << "Danh sach rong, khong the xoa.\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    cout << "Da xoa node dau danh sach.\n";
}

// Xoa node cuoi danh sach
void deleteLast() {
    if (head == nullptr) {
        cout << "Danh sach rong, khong the xoa.\n";
        return;
    }
    
    Node* current = head;
    while (current->next->next != nullptr) {
        current = current->next;
    }
    delete current->next;
    current->next = nullptr;
    cout << "Da xoa node cuoi danh sach.\n";
}

// Xoa node co gia tri bat ky
void deleteNode(int value) {
    // Neu danh sach rong
    if (head == nullptr) {
        cout << "Danh sach rong, khong the xoa.\n";
        return;
    }

    // Neu node dau tien co gia tri can xoa
    if (head->data == value) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Da xoa node co gia tri " << value << ".\n";
        return;
    }

    // Tim node co gia tri can xoa
    Node* current = head;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    // Neu khong tim thay node co gia tri can xoa
    if (current->next == nullptr) {
        cout << "Khong tim thay node co gia tri " << value << " trong danh sach.\n";
        return;
    }

    // Xoa node co gia tri can xoa
    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    cout << "Da xoa node co gia tri " << value << ".\n";
}


int main() {
    // Them mot so node vao danh sach
    addNode(10);
    addNode(20);
    addNode(30);
    addNode(40);

    cout << "Danh sach ban dau:\n";
    displayList();

    // Xoa node dau danh sach
    deleteFirst();
    displayList();

    // Xoa node cuoi danh sach
    deleteLast();
    displayList();

    // Xoa node sau node co gia tri 20
    deleteNode(20);
    displayList();

    return 0;
}
