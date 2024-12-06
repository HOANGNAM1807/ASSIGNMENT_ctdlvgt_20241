#include <iostream>
using namespace std;

// Định nghĩa cấu trúc Node cho cây biểu thức
struct Node {
    char data;         // Giá trị của node (toán tử hoặc toán hạng)
    Node* left;        
    Node* right;       

    Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

// Kiểm tra xem một ký tự có phải toán tử không
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Hàm dựng cây biểu thức từ biểu thức hậu tố
Node* createExpressionTree(char postfix[], int n) {
    Node* stack[100]; 
    int top = -1;     

    for (int i = 0; i < n; i++) {
        // Tạo node mới
        Node* newNode = new Node(postfix[i]);

        // Nếu là toán hạng, đưa vào stack
        if (!isOperator(postfix[i])) {
            stack[++top] = newNode;
        } else {
            // Nếu là toán tử, tạo node với con trái/phải từ stack
            newNode->right = stack[top--];  
            newNode->left = stack[top--];   
            stack[++top] = newNode;         
        }
    }

    
    return stack[top];
}

// Duyệt cây theo tiền tố
void preOrderTraversal(Node* root) {
    if (root) {
        cout << root->data << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

// Duyệt cây theo trung tố
void inOrderTraversal(Node* root) {
    if (root) {
        inOrderTraversal(root->left);
        cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

// Duyệt cây theo hậu tố
void postOrderTraversal(Node* root) {
    if (root) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        cout << root->data << " ";
    }
}

int main() {
    // Biểu thức hậu tố
    char postfix[] = {'3', '4', '+', '5', '*', '6', '-'};
    int n = sizeof(postfix) / sizeof(postfix[0]);

    // Dựng cây biểu thức
    Node* root = createExpressionTree(postfix, n);

    // In kết quả duyệt cây theo 3 cách
    cout << "Pre-order: ";
    preOrderTraversal(root);
    cout << endl;

    cout << "In-order: ";
    inOrderTraversal(root);
    cout << endl;

    cout << "Post-order: ";
    postOrderTraversal(root);
    cout << endl;

    return 0;
}
