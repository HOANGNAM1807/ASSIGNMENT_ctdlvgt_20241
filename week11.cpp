#include <iostream>
#include <string>
using namespace std;

// Khai báo cấu trúc dữ liệu cho khối gỗ
struct Go {
    string loai;
    string kichThuoc;
    string tuoi;
};

// Hàm in nội dung của stack
void inStack(Go stack[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        cout << stack[i].loai << ", " << stack[i].kichThuoc << ", " << stack[i].tuoi << endl;
    }
}

int main() {
    const int MAX_SIZE = 100; // Kích thước tối đa của stack
    Go khoGo[MAX_SIZE];       // Mảng làm stack
    int top = -1;             // Chỉ số đỉnh stack (-1 nghĩa là stack rỗng)

    // Thêm các khối gỗ ban đầu vào kho
    khoGo[++top] = {"gu", "10cm", "10 nam"};
    khoGo[++top] = {"lim", "20cm", "20 nam"};
    khoGo[++top] = {"sen", "30cm", "10 nam"};
    khoGo[++top] = {"soi", "15cm", "35 nam"};

    cout << "Danh sach go ban dau:\n";
    inStack(khoGo, top + 1);

    // Tạo một mảng tạm để lưu các khối gỗ
    Go tempStack[MAX_SIZE];
    int tempTop = -1;

    // Chuyển các khối gỗ sang mảng tạm
    while (top >= 0) {
        tempStack[++tempTop] = khoGo[top--];
    }

    // Thêm khối gỗ mới "oc cho" vào đáy
    khoGo[++top] = {"oc cho", "10cm", "5 nam"};

    // Chuyển lại các khối gỗ từ mảng tạm về mảng chính
    while (tempTop >= 0) {
        khoGo[++top] = tempStack[tempTop--];
    }

    // In danh sách kho gỗ mới
    cout << "\nDanh sach go khi them: \n";
    inStack(khoGo, top + 1);

    return 0;
}
