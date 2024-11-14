#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

// Định nghĩa cấu trúc của một Node trong danh sách liên kết đơn
struct WordNode {
    string word;        
    WordNode* next;      
};

// Hàm thêm từ vào cuối danh sách liên kết
void ThemTuCuoi(WordNode*& head, const string& word) {
    WordNode* newNode = new WordNode;   
    newNode->word = word;               
    newNode->next = nullptr;            

    if (head == nullptr) {              // Nếu danh sách rỗng, Node mới là Node đầu tiên
        head = newNode;
    } else {
        WordNode* temp = head;          // Duyệt đến cuối danh sách
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;           // Thêm Node mới vào cuối
    }
    
}

// Hàm tìm từ xuất hiện nhiều nhất trong danh sách
string TuCoNhieuNhat(WordNode* head) {
    unordered_map<string, int> wordCount;    // Đếm số lần xuất hiện của mỗi từ
    WordNode* temp = head;
    
    while (temp != nullptr) {
        wordCount[temp->word]++;             
        temp = temp->next;
    }
    
    string NhieuNhat;
    int maxCount = 0;
    
    // Tìm từ có số lần xuất hiện lớn nhất
    for (const auto& cap : wordCount) {
        if (cap.second > maxCount) {
            maxCount = cap.second;
            NhieuNhat = cap.first;
        }
    }
    
    return NhieuNhat;
}

// Hàm loại bỏ từ láy (các từ giống nhau liên tiếp)
void BoTuLay(WordNode*& head) {
    WordNode* current = head;
    
    while (current != nullptr && current->next != nullptr) {
        if (current->word == current->next->word) {  // Nếu phát hiện từ láy
            WordNode* redundantNode = current->next; // Node cần xóa
            current->next = redundantNode->next;     // Bỏ qua Node bị xóa
            delete redundantNode;                    
        } else {
            current = current->next;
        }
    }
}

// Hàm đếm số từ vựng duy nhất trong danh sách
int demSoTuVung(WordNode* head) {
    unordered_map<string, bool> tuDuyNhat;   // Sử dụng map để đếm các từ duy nhất
    WordNode* temp = head;
    
    while (temp != nullptr) {
        tuDuyNhat[temp->word] = true;        
        temp = temp->next;
    }
    
    return tuDuyNhat.size();                 
}

// Hàm để tách câu thành các từ, rồi thêm vào danh sách liên kết
void xuLyCau(WordNode*& head, const string& cau) {
    stringstream ss(cau);                    // Tách chuỗi dựa trên khoảng trắng
    string word;
    
    while (ss >> word) {
        ThemTuCuoi(head, word);      // Thêm từng từ vào danh sách liên kết
    }
}

int main() {
    string cau;
    cout << "Nhập câu: ";
    getline(cin, cau);                       
    WordNode* head = nullptr;               

    // Xử lý câu để lưu các từ vào danh sách liên kết
    xuLyCau(head, cau);
    
    // Tìm từ xuất hiện nhiều nhất
    string NhieuNhat = TuCoNhieuNhat(head);
    cout << "Từ xuất hiện nhiều nhất: " << NhieuNhat << endl;
    
    // Loại bỏ từ láy
    BoTuLay(head);

    // Đếm số từ vựng duy nhất
    int soTuDuyNhat = demSoTuVung(head);
    cout << "Số lượng từ vựng duy nhất: " << soTuDuyNhat << endl;
    
    return 0;
}
