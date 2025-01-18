#include <iostream>
using namespace std;

// Kích thước tối đa của cây (giả sử cây có tối đa 100 nút)
const int MAX_NODES = 100;

// Cấu trúc để lưu một nút của cây nhị phân
struct Node {
    int data; // Giá trị của nút
    Node* left; // Con trái
    Node* right; // Con phải

    // Hàm khởi tạo nút
    Node(int data) {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

// Hàm đệ quy tính đường kính và đường đi của cây nhị phân
int calculateDiameter(Node* root, int& diameter, int path[], int& pathLength, int tempPath[], int& tempPathLength) {
    // Trường hợp cơ bản: nếu cây rỗng
    if (root == nullptr) {
        tempPathLength = 0; // Đường đi tạm thời không có nút nào
        return 0;
    }

    // Mảng lưu đường đi tạm thời cho cây con trái và phải
    int leftPath[MAX_NODES], rightPath[MAX_NODES];
    int leftPathLength = 0, rightPathLength = 0;

    // Tính chiều cao cây con trái và cây con phải
    int leftHeight = calculateDiameter(root->left, diameter, path, pathLength, leftPath, leftPathLength);
    int rightHeight = calculateDiameter(root->right, diameter, path, pathLength, rightPath, rightPathLength);

    // Tính đường kính qua nút hiện tại
    int maxDiameter = leftHeight + rightHeight + 1;

    // Nếu đường kính qua nút hiện tại lớn hơn đường kính hiện tại, cập nhật đường kính và đường đi
    if (maxDiameter > diameter) {
        diameter = maxDiameter;
        pathLength = 0; // Đặt lại độ dài của đường đi chính

        // Thêm các nút từ cây con trái vào đường đi
        for (int i = 0; i < leftPathLength; i++) {
            path[pathLength++] = leftPath[i];
        }

        // Thêm nút hiện tại vào đường đi
        path[pathLength++] = root->data;

        // Thêm các nút từ cây con phải vào đường đi (theo thứ tự ngược)
        for (int i = rightPathLength - 1; i >= 0; i--) {
            path[pathLength++] = rightPath[i];
        }
    }

    // Cập nhật đường đi tạm thời để trả về cây cha
    tempPathLength = 0;
    if (leftHeight >= rightHeight) {
        // Chọn cây con trái nếu chiều cao bằng hoặc lớn hơn
        for (int i = 0; i < leftPathLength; i++) {
            tempPath[tempPathLength++] = leftPath[i];
        }
    } else {
        // Chọn cây con phải nếu chiều cao lớn hơn
        for (int i = 0; i < rightPathLength; i++) {
            tempPath[tempPathLength++] = rightPath[i];
        }
    }
    tempPath[tempPathLength++] = root->data; // Thêm nút hiện tại vào đường đi tạm thời

    // Trả về chiều cao cây tại nút hiện tại
    return max(leftHeight, rightHeight) + 1;
}

// Hàm gọi chính để tính đường kính của cây
int getDiameter(Node* root, int path[], int& pathLength) {
    int diameter = 0; // Đường kính ban đầu là 0
    int tempPath[MAX_NODES], tempPathLength = 0;
    calculateDiameter(root, diameter, path, pathLength, tempPath, tempPathLength);
    return diameter;
}

int main() {
    // Tạo cây thứ nhất
    Node* root1 = new Node(1);
    root1->right = new Node(2);
    root1->right->left = new Node(3);
    root1->right->right = new Node(4);
    root1->right->left->left = new Node(5);
    root1->right->left->right = new Node(6);
    root1->right->right->right = new Node(7);

    int path1[MAX_NODES], pathLength1 = 0;
    int diameter1 = getDiameter(root1, path1, pathLength1);

    cout << "Duong kinh cua cay thu nhat la: " << diameter1 << endl;
    cout << "Duong di: ";
    for (int i = 0; i < pathLength1; i++) {
        cout << path1[i] << (i == pathLength1 - 1 ? "\n" : " -> ");
    }

    // Tạo cây thứ hai
    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->left = new Node(4);
    root2->left->right = new Node(5);
    root2->right->left = new Node(6);
    root2->right->right = new Node(7);
    root2->left->left->left = new Node(8);
    root2->right->right->right = new Node(9);

    int path2[MAX_NODES], pathLength2 = 0;
    int diameter2 = getDiameter(root2, path2, pathLength2);

    cout << "Duong kinh cua cay thu hai la: " << diameter2 << endl;
    cout << "Duong di: ";
    for (int i = 0; i < pathLength2; i++) {
        cout << path2[i] << (i == pathLength2 - 1 ? "\n" : " -> ");
    }

    return 0;
}
