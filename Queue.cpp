#include <iostream>
#include <string>
using namespace std;

// Struct de bieu dien mot gio hang (node)
struct Cart {
    string customerName; // Ten khach hang
    float totalPrice;    // Tong gia tri gio hang
    Cart* next;          // Con tro toi gio hang tiep theo
};

// Class bieu dien hang doi (queue)
class Queue {
private:
    Cart* front; // Diem dau cua hang doi
    Cart* rear;  // Diem cuoi cua hang doi

public:
    Queue() : front(nullptr), rear(nullptr) {}

    // Ham kiem tra hang doi co rong khong
    bool isEmpty() {
        return front == nullptr;
    }

    // Ham them mot gio hang vao hang doi
    void enqueue(string name, float price) {
        Cart* newCart = new Cart{name, price, nullptr};
        if (rear == nullptr) {
            front = rear = newCart;
        } else {
            rear->next = newCart;
            rear = newCart;
        }
    }

    // Ham xu ly thanh toan (dequeue)
    void dequeue() {
        if (isEmpty()) {
            cout << "Hang doi trong, khong the thanh toan.\n";
            return;
        }

        Cart* temp = front;
        cout << "Khach hang " << temp->customerName << " da thanh toan: " << temp->totalPrice << " VND\n";

        // Loai bo khach hang khoi hang doi
        front = front->next;
        if (front == nullptr) rear = nullptr;

        delete temp;
    }

    // Ham hien thi danh sach hang doi
    void displayQueue() {
        if (isEmpty()) {
            cout << "Hang doi trong.\n";
            return;
        }

        Cart* temp = front;
        cout << "Danh sach hang doi:\n";
        while (temp != nullptr) {
            cout << "Khach hang: " << temp->customerName 
                 << ", Tong tien: " << temp->totalPrice << " VND\n";
            temp = temp->next;
        }
    }

    // Destructor de giai phong bo nho
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

// Ham main
int main() {
    Queue q;

    // Them khach hang vao hang doi
    q.enqueue("Khach hang 1", 100000.0);
    q.enqueue("Khach hang 2", 50000.0);
    q.enqueue("Khach hang 3", 200000.0);

    // Hien thi hang doi
    q.displayQueue();

    // Xu ly thanh toan tung khach hang
    cout << "\n--- Xu ly thanh toan ---\n";
    while (!q.isEmpty()) {
        q.dequeue();
    }

    return 0;
}
