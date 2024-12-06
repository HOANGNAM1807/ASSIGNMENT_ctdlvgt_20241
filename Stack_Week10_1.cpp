#include <iostream>
#include <string>

using namespace std;

// Định nghĩa cấu trúc cho một loại gỗ
struct Wood {
    string type;   
    int size;      
    int age;       
    Wood* next;    
};


struct Stack {
    Wood* top;    // Con trỏ đến loại gỗ trên cùng của stack
};

// Khởi tạo kho rỗng
void initStack(Stack& stack) {
    stack.top = nullptr;  
}

// Kiểm tra kho có rỗng không
bool isEmpty(const Stack& stack) {
    return stack.top == nullptr;
}

// Thêm loại gỗ vào kho
void pushStack(Stack& stack, const string& type, int size, int age) {
    Wood* newWood = new Wood;
    newWood->type = type;
    newWood->size = size;
    newWood->age = age;
    newWood->next = stack.top;
    stack.top = newWood;
}

// Hàm tìm và xóa thanh gỗ có tuổi bằng tuổi nhập vào
void removeWoodByAge(Stack& stack, int age) {
    if (isEmpty(stack)) {
        cout << "Kho go rong, khong co go de xoa!" << endl;
        return;
    }

    Wood* current = stack.top;
    Wood* previous = nullptr;

    // Duyệt qua danh sách liên kết và tìm gỗ có tuổi đúng yêu cầu
    while (current != nullptr) {
        if (current->age == age) {
            if (previous == nullptr) {
                stack.top = current->next;  // Xóa thanh gỗ đầu tiên
            } else {
                previous->next = current->next; 
            }
            delete current;  // Giải phóng bộ nhớ của thanh gỗ
            cout << "Thanh go co tuoi " << age << " da bi xoa khoi kho!" << endl;
            return;
        }
        previous = current;
        current = current->next;
    }

    cout << "Khong tim thay go co tuoi " << age << " trong kho!" << endl;
}

// Hiển thị tất cả các loại gỗ trong kho
void displayStack(const Stack& stack) {
    if (isEmpty(stack)) {
        cout << "Kho go rong!" << endl;
        return;
    }

    cout << "Danh sach go trong kho: " << endl;
    Wood* current = stack.top;
    while (current != nullptr) {
        cout << "Loai go: " << current->type << ", Kich thuoc: " << current->size
             << ", Tuoi: " << current->age << endl;
        current = current->next;
    }
}

int main() {
    Stack kho;
    initStack(kho);  
    
    // Thêm một số loại gỗ vào kho
    pushStack(kho, "Go Lim", 5, 10);
    pushStack(kho, "Go Xoan", 3, 7);
    pushStack(kho, "Go Trac", 8, 10);
    pushStack(kho, "Go Keo", 6, 7);
    pushStack(kho, "Go Bang Lang", 9, 12);
    pushStack(kho, "Go Mit", 7, 7); 

    // Hiển thị danh sách các thanh gỗ
    cout << "Kho go truoc khi lay go: " << endl;
    displayStack(kho);

    // Nhập tuổi gỗ cần lấy ra
    int ageToRemove;
    cout << "\nNhap tuoi go can lay ra kho: ";
    cin >> ageToRemove;

    // Thực hiện lấy gỗ có tuổi bằng tuổi nhập vào
    removeWoodByAge(kho, ageToRemove);

    // Hiển thị danh sách gỗ trong kho sau khi lấy
    cout << "\nKho go sau khi lay go co tuoi " << ageToRemove << " ra kho: " << endl;
    displayStack(kho);

    // Giải phóng bộ nhớ của tất cả các thanh gỗ còn lại
    Wood* current = kho.top;
    while (current != nullptr) {
        Wood* temp = current;
        current = current->next;
        delete temp;  // Giải phóng bộ nhớ của thanh gỗ
    }

    return 0;
}
