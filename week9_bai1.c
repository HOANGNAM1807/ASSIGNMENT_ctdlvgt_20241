#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* link;
} Node;

typedef struct List {
    Node* first;
    Node* last;
} List;

// Xóa phần tử cuối cùng trong danh sách
void list_delete_last(List* list) {
    if (list->first == NULL) {
        printf("list khong co phan tu\n");
        return;
    }
    
    if (list->first == list->last) {
        free(list->first);
        list->first = NULL;
        list->last = NULL;
    } else {
        Node* cs = list->first;
        while (cs->link != list->last) {
            cs = cs->link;
        }
        free(list->last);
        list->last = cs;
        list->last->link = NULL;
    }
}

// Xóa một phần tử cụ thể trong danh sách
void list_delete(List* list, Node* node) {
    if (list->first == NULL) {
        printf("list khong co phan tu\n");
        return;
    }
    
    if (list->first == node) {
        list->first = node->link;
        free(node);
    } else {
        Node* cs = list->first;
        while (cs->link != NULL && cs->link != node) {
            cs = cs->link;
        }
        
        if (cs->link == node) {
            cs->link = node->link;
            if (node == list->last) {
                list->last = cs;
            }
            free(node);
        }
    }
}
