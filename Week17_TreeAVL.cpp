#include <iostream>
using namespace std;

// Khai báo cấu trúc cây AVL
struct AVLNode {
    int key;                 // Giá trị của node
    int height;              // Chiều cao của node
    AVLNode* left;           // Con trái
    AVLNode* right;          // Con phải

    AVLNode(int val) : key(val), height(1), left(nullptr), right(nullptr) {}
};

// Hàm lấy chiều cao của node
int getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Hàm tính giá trị lớn hơn
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Hàm tính hệ số cân bằng
int getBalance(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Hàm xoay phải
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // Trả về root mới
}

// Hàm xoay trái
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Trả về root mới
}

// Hàm chèn node vào cây AVL
AVLNode* insertNode(AVLNode* node, int key) {
    // Bước 1: Thêm node như trong cây nhị phân tìm kiếm
    if (node == nullptr) return new AVLNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node; // Không cho phép thêm giá trị trùng

    // Bước 2: Cập nhật chiều cao của node tổ tiên
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Bước 3: Kiểm tra và cân bằng cây
    int balance = getBalance(node);

    // Trường hợp xoay phải
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Trường hợp xoay trái
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Trường hợp xoay kép trái-phải
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Trường hợp xoay kép phải-trái
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node; // Trả về node (không cần xoay)
}

// Hàm duyệt cây theo thứ tự trước (Preorder)
void preOrder(AVLNode* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Hàm duyệt cây theo thứ tự giữa (Inorder)
void inOrder(AVLNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// Hàm duyệt cây theo thứ tự sau (Postorder)
void postOrder(AVLNode* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

// Chương trình chính
int main() {
    AVLNode* root = nullptr;

    // Mảng đầu vào
    int input[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(input) / sizeof(input[0]);

    cout << "Bo sung cac phan tu vao cay AVL:\n";

    // Thêm từng phần tử vào cây AVL và in ra trạng thái cây
    for (int i = 0; i < n; i++) {
        cout << "\nThem gia tri " << input[i] << " vao cay.\n";
        root = insertNode(root, input[i]);

        // In các phép duyệt cây
        cout << "Duyet cay theo thu tu truoc (Preorder): ";
        preOrder(root);
        cout << "\nDuyet cay theo thu tu giua (Inorder): ";
        inOrder(root);
        cout << "\nDuyet cay theo thu tu sau (Postorder): ";
        postOrder(root);
        cout << "\n";
    }

    return 0;
}
