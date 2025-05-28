#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int n; // Kích thước mê cung
int a[1000][1000] = {};
bool visited[1000][1000] = {};// Mảng để đánh dấu các ô đã đi qua
vector<pair<int, int>> path; // Mảng để lưu trữ đường đi

// Sử dụng thuật toán nước loang (flood fill) để tìm đường đi trong mê cung
void loang(int x,int y){
    if (x== n && y == n) {
        // Nếu đã đến đích (ô cuối cùng), in ra đường đi
        cout << "Đường đi từ (1,1) đến (" << n << "," << n << "):\n";
        for (const auto& p : path) {
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << '\n';
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

int main(){
    cout << "Nhập kích thước mê cung: ";
    cin >> n;
    cout << "Nhập mê cung (1 = đường đi, 0 = tường):\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j]; // Nhập mê cung
        }
    }
    loang(1, 1); // Bắt đầu từ ô (1, 1)
    return 0;
}