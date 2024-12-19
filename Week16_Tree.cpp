#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct BookNode {
    string title;               // Tên mục (chapter/section/subsection)
    int pageCount;              // Số trang
    vector<BookNode*> children; // Danh sách các mục con

    BookNode(const string& t, int p) : title(t), pageCount(p) {}
};

class Book {
private:
    BookNode* root;

public:
    // Tạo sách
    Book(const string& bookTitle) {
        root = new BookNode(bookTitle, 0);
    }

    // Thêm mục con vào sách
    void addNode(const string& parentTitle, const string& title, int pageCount) {
        BookNode* parent = findNode(root, parentTitle);
        if (parent) {
            parent->children.push_back(new BookNode(title, pageCount));
        }
    }

    // Đếm số chương
    int getChapterCount() {
        return root->children.size();
    }

    // Tìm chương dài nhất
    BookNode* findLongestChapter() {
        BookNode* longest = nullptr;
        int maxPages = 0;

        for (BookNode* chapter : root->children) {
            if (chapter->pageCount > maxPages) {
                maxPages = chapter->pageCount;
                longest = chapter;
            }
        }
        return longest;
    }

    // Tìm và xóa một mục
    void deleteNode(const string& title) {
        deleteNodeRecursive(root, title);
    }

private:
    // Tìm một node theo tiêu đề
    BookNode* findNode(BookNode* node, const string& title) {
        if (node->title == title) return node;
        for (BookNode* child : node->children) {
            BookNode* result = findNode(child, title);
            if (result) return result;
        }
        return nullptr;
    }

    // Xóa node theo tiêu đề
    bool deleteNodeRecursive(BookNode* node, const string& title) {
        for (auto it = node->children.begin(); it != node->children.end(); ++it) {
            if ((*it)->title == title) {
                delete *it;  // Giải phóng bộ nhớ
                node->children.erase(it); // Xóa khỏi danh sách
                return true;
            }
            if (deleteNodeRecursive(*it, title)) return true;
        }
        return false;
    }
};
