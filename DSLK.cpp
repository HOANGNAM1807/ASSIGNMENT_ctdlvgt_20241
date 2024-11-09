#include <iostream>

using namespace std;

// Cấu trúc Ngày
struct Ngay {
    int ngay, thang, nam;
};

// Cấu trúc SinhVien
struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;  // 0: Nữ, 1: Nam
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

// Cấu trúc Node cho danh sách liên kết
struct Node {
    SinhVien data;
    Node* link;
};

// Cấu trúc List quản lý đầu danh sách
struct List {
    Node* first;
};

// Khởi tạo danh sách
void initList(List* list) {
    list->first = NULL;
}

// Sao chép chuỗi thủ công
void copyString(char* dest, const char* src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

// So sánh chuỗi thủ công
int compareString(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// Tạo Node mới
Node* createNode(SinhVien sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = NULL;
    return newNode;
}

// Thêm sinh viên vào danh sách theo thứ tự mã
void insertSorted(List* list, SinhVien sv) {
    Node* newNode = createNode(sv);
    if (list->first == NULL || compareString(sv.maSV, list->first->data.maSV) < 0) {
        newNode->link = list->first;
        list->first = newNode;
    } else {
        Node* temp = list->first;
        while (temp->link != NULL && compareString(temp->link->data.maSV, sv.maSV) < 0) {
            temp = temp->link;
        }
        newNode->link = temp->link;
        temp->link = newNode;
    }
}

// In danh sách sinh viên
void printList(List list) {
    Node* temp = list.first;
    while (temp != NULL) {
        cout << "MaSV: " << temp->data.maSV << ", HoTen: " << temp->data.hoTen << ", Lop: " << temp->data.lop << endl;
        temp = temp->link;
    }
}

// Tìm sinh viên có cùng ngày sinh
void findSameBirthday(List list, Ngay ngaySinh) {
    Node* temp = list.first;
    int found = 0;
    while (temp != NULL) {
        if (temp->data.ngaySinh.ngay == ngaySinh.ngay &&
            temp->data.ngaySinh.thang == ngaySinh.thang &&
            temp->data.ngaySinh.nam == ngaySinh.nam) {
            cout << "MaSV: " << temp->data.maSV << ", HoTen: " << temp->data.hoTen << endl;
            found = 1;
        }
        temp = temp->link;
    }
    if (!found) {
        cout << "Không tìm thấy sinh viên cùng ngày sinh" << endl;
    }
}

// Loại bỏ sinh viên có cùng ngày sinh
void removeSameBirthday(List* list, Ngay ngaySinh) {
    Node *temp = list->first, *prev = NULL;
    while (temp != NULL) {
        if (temp->data.ngaySinh.ngay == ngaySinh.ngay &&
            temp->data.ngaySinh.thang == ngaySinh.thang &&
            temp->data.ngaySinh.nam == ngaySinh.nam) {
            if (prev == NULL) {
                list->first = temp->link;
            } else {
                prev->link = temp->link;
            }
            Node* toDelete = temp;
            temp = temp->link;
            delete toDelete;
        } else {
            prev = temp;
            temp = temp->link;
        }
    }
}

void addSinhVien(List* list) {
    SinhVien sv;

    // Nhập thông tin sinh viên mới
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;

    cout << "Nhap ho ten: ";
    cin.ignore(); // Loại bỏ ký tự '\n' còn lại từ lần nhập trước
    cin.getline(sv.hoTen, 50); // Đọc chuỗi, cho phép khoảng trắng

    cout << "Nhap gioi tinh (0: Nu, 1: Nam): ";
    cin >> sv.gioiTinh;

    cout << "Nhap ngay sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;

    cout << "Nhap dia chi: ";
    cin.ignore(); // Loại bỏ ký tự '\n'
    cin.getline(sv.diaChi, 100);

    cout << "Nhap lop: ";
    cin >> sv.lop;

    cout << "Nhap khoa: ";
    cin >> sv.khoa;

    // Thêm sinh viên mới vào danh sách đã sắp xếp
    insertSorted(list, sv);

    cout << "Da them sinh vien thanh cong!" << endl;
}

int main() {
    List list;
    initList(&list);

    // Thêm sinh viên vào danh sách
    SinhVien sv1 = {"001", "Nguyen Van Long", 1, {10, 1, 2004}, "Hanoi", "ETE9", "K67"};
    SinhVien sv2 = {"002", "Tran Thi Thuy", 0, {20, 6, 2004}, "Hai Phong", "ETE9", "K67"};
    SinhVien sv3 = {"003", "Le Van Hanh", 1, {10, 12, 2004}, "Da Nang", "ETE9", "K67"};

    insertSorted(&list, sv1);
    insertSorted(&list, sv2);
    insertSorted(&list, sv3);

    cout << "Danh sách sinh viên:" << endl;
    printList(list);

    cout << "\nNhap sinh vien moi:\n";
    addSinhVien(&list);

    // In lại danh sách sau khi thêm sinh viên mới
    cout << "\nDanh sach sau khi them sinh vien moi:\n";
    printList(list);

    // Tìm sinh viên có cùng ngày sinh
    cout << "\nTìm sinh viên có cùng ngày sinh 10/01/2004:\n";
    findSameBirthday(list, {10, 1, 2004});

    // Loại bỏ sinh viên có cùng ngày sinh
    cout << "\nLoại bỏ sinh viên có cùng ngày sinh 10/01/2004:\n";
    removeSameBirthday(&list, {10, 1, 2004});
    printList(list);

    return 0;
}
