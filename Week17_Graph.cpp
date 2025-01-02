#include <iostream>
using namespace std;

#define MAX 100  // Số đỉnh tối đa trong đồ thị

class Graph {
private:
    int adjMatrix[MAX][MAX];  // Ma trận kề
    int n;  // Số đỉnh

public:
    Graph(int vertices) {
        n = vertices;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjMatrix[i][j] = 0;  // Khởi tạo ma trận kề bằng 0
            }
        }
    }

    // Thêm cạnh vào đồ thị
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;  // Nếu là đồ thị vô hướng
    }

    // Hiển thị ma trận kề
    void displayGraph() {
        cout << "Ma tran ke cua do thi" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Duyệt BFS
    void BFS(int start) {
        int queue[MAX], front = 0, rear = 0;
        int visited[MAX] = {0};  // Mảng đánh dấu các đỉnh đã thăm
        int bfsOrder[MAX], bfsIndex = 0;

        queue[rear++] = start;
        visited[start] = 1;

        while (front < rear) {
            int current = queue[front++];
            bfsOrder[bfsIndex++] = current;

            for (int i = 0; i < n; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }

        cout << "Thu tu duyet BFS ";
        for (int i = 0; i < bfsIndex; i++) {
            cout << bfsOrder[i] << " ";
        }
        cout << endl;
    }

    // Duyệt DFS
    void DFS(int start) {
        int stack[MAX], top = -1;
        int visited[MAX] = {0};  // Mảng đánh dấu các đỉnh đã thăm
        int dfsOrder[MAX], dfsIndex = 0;

        stack[++top] = start;

        while (top >= 0) {
            int current = stack[top--];

            if (!visited[current]) {
                visited[current] = 1;
                dfsOrder[dfsIndex++] = current;

                for (int i = n - 1; i >= 0; i--) {  // Duyệt từ đỉnh lớn đến nhỏ
                    if (adjMatrix[current][i] == 1 && !visited[i]) {
                        stack[++top] = i;
                    }
                }
            }
        }

        cout << "Thu tu duyet DFS ";
        for (int i = 0; i < dfsIndex; i++) {
            cout << dfsOrder[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int n, m;
    cout << "Nhap so dinh ";
    cin >> n;

    Graph g(n);

    cout << "Nhap so canh ";
    cin >> m;

    cout << "Nhap cac canh u v " << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.displayGraph();

    int start;
    cout << "Nhap dinh bat dau duyet ";
    cin >> start;

    g.BFS(start);
    g.DFS(start);

    return 0;
}
