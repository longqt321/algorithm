#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;
int n; // Kích thước mê cung
int a[1000][1000] = {};
bool visited[1000][1000] = {};// Mảng để đánh dấu các ô đã đi qua
vector<pair<int, int>> path; // Mảng để lưu trữ đường đi

void init(){
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            visited[i][j] = false; // Đánh dấu tất cả ô chưa được đi qua
        }
    }
    path.clear();
}

// Sử dụng thuật toán nước loang (flood fill) để tìm đường đi trong mê cung
void loang(int x,int y){
    if (x== n && y == n) {
        path.push_back({x, y}); // Lưu trữ ô cuối cùng (đích)
        visited[x][y] = true; // Đánh dấu ô cuối cùng đã đi qua
        // Nếu đã đến đích (ô cuối cùng), in ra đường đi
        cout << "Đường đi từ (1,1) đến (" << n << "," << n << "):\n";
        for (const auto& p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << '\n';
        cout << "Số nước cần di chuyển: " << path.size() - 1 << '\n'; // In ra số nước cần di chuyển
        return;
    }
    if (x < 1 || x > n || y < 1 || y > n || a[x][y] == 0) {
        return; // Nếu ra ngoài mê cung hoặc gặp tường thì dừng và quay lui
    }
    if (visited[x][y]) {
        return; // Nếu ô đã được đánh dấu là đã đi qua thì dừng
    }
    visited[x][y] = true; // Đánh dấu ô đã đi qua
    path.push_back({x, y}); // Lưu trữ ô đã đi qua
    int dx[] = {0, 1, 0, -1}; // Các hướng di chuyển: phải, xuống, trái, lên
    int dy[] = {1, 0, -1, 0}; // Các hướng di chuyển: phải, xuống, trái, lên
    for (int i = 0; i < 4; ++i) {
        int u = x + dx[i]; // Tính toạ độ ô mới
        int v = y + dy[i]; // Tính toạ độ ô mới
        loang(u, v); // Gọi đệ quy để tiếp tục đi
    }
    path.pop_back(); // Quay lui, loại bỏ ô hiện tại khỏi đường đi
}

void bfs(int x,int y){
    queue<pair<int, int>> q; // Hàng đợi BFS
    map<pair<int, int>, pair<int, int>> parent; // Để truy ngược đường đ
    q.push({x, y}); // Bắt đầu từ ô (x, y)
    visited[x][y] = true; // Đánh dấu ô đã đi qua

    while (!q.empty()) {
        auto current = q.front(); // Lấy ô đầu tiên trong hàng đợi
        q.pop();
        x = current.first;
        y = current.second;

        if (x == n && y == n) {
            pair<int, int> p = {n, n};
            while(p != make_pair(1, 1)) { // Truy ngược đường đi từ đích về nguồn
                path.push_back(p); // Lưu trữ đường đi
                p = parent[p]; // Lấy cha của ô hiện tại
            }
            path.push_back({1, 1}); // Thêm ô bắt đầu vào đường đi
            reverse(path.begin(), path.end()); // Đảo ngược đường đi để từ (1, 1) đến (n, n)

            // Nếu đã đến đích, in ra đường đi
            cout << "Đường đi từ (1,1) đến (" << n << "," << n << "):\n";
            for (const auto& p : path) {
                cout << "(" << p.first << "," << p.second << ") ";
            }
            cout << '\n';
            cout << "Số nước cần di chuyển: " << path.size() - 1 << '\n'; // In ra số nước cần di chuyển
            return;
        }

        int dx[] = {0, 1, 0, -1}; // Các hướng di chuyển: phải, xuống, trái, lên
        int dy[] = {1, 0, -1, 0}; // Các hướng di chuyển: phải, xuống, trái, lên

        for (int i = 0; i < 4; ++i) {
            int u = x + dx[i]; // Tính toạ độ ô mới
            int v = y + dy[i]; // Tính toạ độ ô mới
            if (u >= 1 && u <= n && v >= 1 && v <= n && a[u][v] == 1 && !visited[u][v]) {
                visited[u][v] = true; // Đánh dấu ô đã đi qua                
                q.push({u, v}); // Thêm ô vào hàng đợi
                parent[{u, v}] = {x, y}; // Lưu trữ cha của ô mới
            }
        }
    }
}

int main(){
    cout << "Nhập kích thước mê cung: ";
    cin >> n;
    cout << "Nhập mê cung (1 = đường đi, 0 = tường):\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j]; // Nhập mê cung
        }
    }
    init();
    cout << "Tìm đường bằng thuật toán nước loang:\n";
    loang(1, 1); // Bắt đầu từ ô (1, 1)
    init();
    cout << "Tìm đường bằng thuật toán BFS:\n";
    bfs(1, 1); // Bắt đầu từ ô (1, 1) với thuật toán BFS
    return 0;
}