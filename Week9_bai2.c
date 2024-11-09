#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int he_so;    // Hệ số của hạng tử
    int bac;      // Bậc của hạng tử
    struct Node* tiep; // Con trỏ tới hạng tử tiếp theo
} Node;

typedef struct DaThuc {
    Node* dau;
} DaThuc;

// Khởi tạo một đa thức rỗng
DaThuc* taoDaThuc() {
    DaThuc* da_thuc = (DaThuc*)malloc(sizeof(DaThuc));
    da_thuc->dau = NULL;
    return da_thuc;
}

// Tạo một node mới cho hạng tử
Node* taoNode(int he_so, int bac) {
    Node* node_moi = (Node*)malloc(sizeof(Node));
    node_moi->he_so = he_so;
    node_moi->bac = bac;
    node_moi->tiep = NULL;
    return node_moi;
}

// Thêm một hạng tử vào đa thức (theo thứ tự giảm dần của bậc)
void themHangTu(DaThuc* da_thuc, int he_so, int bac) {
    if (he_so == 0) return; // Bỏ qua nếu hệ số là 0
    
    Node* node_moi = taoNode(he_so, bac);
    if (da_thuc->dau == NULL || da_thuc->dau->bac < bac) {
        node_moi->tiep = da_thuc->dau;
        da_thuc->dau = node_moi;
    } else {
        Node* tam = da_thuc->dau;
        while (tam->tiep != NULL && tam->tiep->bac > bac) {
            tam = tam->tiep;
        }
        if (tam->tiep != NULL && tam->tiep->bac == bac) {
            tam->tiep->he_so += he_so;
            free(node_moi);
            if (tam->tiep->he_so == 0) {
                Node* can_xoa = tam->tiep;
                tam->tiep = tam->tiep->tiep;
                free(can_xoa);
            }
        } else {
            node_moi->tiep = tam->tiep;
            tam->tiep = node_moi;
        }
    }
}

// Nhập đa thức
void nhapDaThuc(DaThuc* da_thuc) {
    int so_hang_tu, he_so, bac;
    printf("Nhap so luong hang tu: ");
    scanf("%d", &so_hang_tu);
    for (int i = 0; i < so_hang_tu; i++) {
        printf("Nhap he so va bac: ");
        scanf("%d %d", &he_so, &bac);
        themHangTu(da_thuc, he_so, bac);
    }
}

// In đa thức
void inDaThuc(DaThuc* da_thuc) {
    Node* tam = da_thuc->dau;
    if (tam == NULL) {
        printf("0\n");
        return;
    }
    while (tam != NULL) {
        if (tam->he_so > 0 && tam != da_thuc->dau) {
            printf(" + ");
        } else if (tam->he_so < 0) {
            printf(" - ");
        }
        
        if (abs(tam->he_so) != 1 || tam->bac == 0) {
            printf("%d", abs(tam->he_so));
        }
        
        if (tam->bac != 0) {
            printf(".x^%d", tam->bac);
        }
        
        tam = tam->tiep;
    }
    printf("\n");
}

// Cộng hai đa thức
DaThuc* congDaThuc(DaThuc* f, DaThuc* g) {
    DaThuc* ket_qua = taoDaThuc();
    Node* p1 = f->dau;
    Node* p2 = g->dau;

    while (p1 != NULL && p2 != NULL) {
        if (p1->bac > p2->bac) {
            themHangTu(ket_qua, p1->he_so, p1->bac);
            p1 = p1->tiep;
        } else if (p1->bac < p2->bac) {
            themHangTu(ket_qua, p2->he_so, p2->bac);
            p2 = p2->tiep;
        } else {
            themHangTu(ket_qua, p1->he_so + p2->he_so, p1->bac);
            p1 = p1->tiep;
            p2 = p2->tiep;
        }
    }

    while (p1 != NULL) {
        themHangTu(ket_qua, p1->he_so, p1->bac);
        p1 = p1->tiep;
    }

    while (p2 != NULL) {
        themHangTu(ket_qua, p2->he_so, p2->bac);
        p2 = p2->tiep;
    }

    return ket_qua;
}

int main() {
    DaThuc* f = taoDaThuc();
    DaThuc* g = taoDaThuc();

    printf("Nhap da thuc f(x):\n");
    nhapDaThuc(f);
    printf("Nhap da thuc g(x):\n");
    nhapDaThuc(g);

    printf("f(x) = ");
    inDaThuc(f);
    printf("g(x) = ");
    inDaThuc(g);

    DaThuc* h = congDaThuc(f, g);
    printf("h(x) = f(x) + g(x) = ");
    inDaThuc(h);

    return 0;
}
