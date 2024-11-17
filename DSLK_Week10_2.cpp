#include <iostream>
#include <string>
using namespace std;

// Co su dung chat GPT

// Cau truc luu thong tin file
struct FileInfo {
    string name;       
    int size;          
    int timestamp;     // Thoi gian luu file
};

// Cau truc node trong danh sach
struct Node {
    FileInfo data;     // Thong tin file
    Node* next;        
};

// Danh sach lien ket don
Node* head = nullptr;

// Ham tao mot node moi
Node* createNode(const string& name, int size, int timestamp) {
    Node* newNode = new Node;
    newNode->data = {name, size, timestamp};
    newNode->next = nullptr;
    return newNode;
}

// Ham chen file vao danh sach, sap xep tang dan theo dung luong va thoi gian
void insertFile(const string& name, int size, int timestamp) {
    Node* newNode = createNode(name, size, timestamp);
    
    // Neu danh sach rong
    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    Node* prev = nullptr;

    // Sap xep tang dan theo dung luong va thoi gian
    while (current != nullptr && 
           (current->data.size < size || 
           (current->data.size == size && current->data.timestamp <= timestamp))) {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr) { // Chen dau danh sach
        newNode->next = head;
        head = newNode;
    } else { // Chen giua hoac cuoi danh sach
        prev->next = newNode;
        newNode->next = current;
    }
}

// Ham hien thi danh sach file
void displayFiles() {
    if (head == nullptr) {
        cout << "Danh sach rong.\n";
        return;
    }
    cout << "Danh sach file trong thu muc:\n";
    Node* current = head;
    while (current != nullptr) {
        cout << "Ten: " << current->data.name 
             << ", Dung luong: " << current->data.size << "KB"
             << ", Thoi gian luu: " << current->data.timestamp << "\n";
        current = current->next;
    }
}

// Ham xoa file co dung luong nho nhat va thoi gian luu lau nhat
void deleteSmallestOldest() {
    if (head == nullptr) {
        cout << "Danh sach rong, khong the xoa.\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    cout << "Da xoa file co dung luong nho nhat va thoi gian luu lau nhat.\n";
}

int main() {
    // Chen mot so file vao danh sach
    insertFile("file1.txt", 500, 10);
    insertFile("file2.txt", 200, 15);
    insertFile("file3.txt", 200, 5);
    insertFile("file4.txt", 800, 20);

    cout << "Danh sach file ban dau:\n";
    displayFiles();

    // Xoa file co dung luong nho nhat va thoi gian luu lau nhat
    deleteSmallestOldest();
    displayFiles();

    return 0;
}
