#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n,a[1000];
int dp[1000]; // Bảng DP để lưu trữ giá trị tối ưu cho bài toán LIS


// Thuật toán tìm LIS cơ bản, độ phức tạp O(n^2)
void LIS_coban(){
    for (int i=1;i<=n;++i){
        dp[i] = 1; // Khởi tạo giá trị tối ưu ban đầu là 1 (mỗi phần tử đơn lẻ)
        for (int j=1;j<i;++j){
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1); // Cập nhật giá trị tối ưu nếu tìm thấy chuỗi tăng dần
            }
        }
    }
    int max_length = 0;
    for (int i=1;i<=n;++i){
        max_length = max(max_length, dp[i]); // Tìm độ dài chuỗi tăng dần dài nhất
    }

    cout << "Do dai cua chuoi tang dan dai nhat la: " << max_length << '\n';
    vector<int> lis; // Lưu trữ chuỗi tăng dần dài nhất
    for (int i=n; i>=1; --i) {
        if (dp[i] == max_length) {
            lis.push_back(a[i]); // Thêm phần tử vào chuỗi tăng dần
            max_length--; // Giảm độ dài cần tìm
        }
    }
    cout << "(Lưu ý, chuỗi này không chính xác. Thuật toán LIS nâng cao này chỉ trả về độ dài của dãy con tăng lớn nhất, không trả về đúng dãy con đó)";
    cout << "Chuoi tang dan dai nhat la: ";
    for (int i=lis.size()-1; i>=0; --i) {
        cout << lis[i] << " "; // In ra chuỗi tăng dần
    }
    cout << '\n';
}

// Thuật toán tìm LIS nâng cao, giảm độ phức tạp từ O(n^2) xuống O(n log n). Dùng tìm kiếm nhị phân
void LIS_nangcao(){
    vector<int> lis; // Mảng lưu trữ chuỗi tăng dần
    for (int i=1;i<=n;++i){
        auto it = lower_bound(lis.begin(), lis.end(), a[i]); // Tìm vị trí chèn của a[i] trong lis
        if (it == lis.end()) {
            lis.push_back(a[i]); // Nếu không tìm thấy, thêm vào cuối
        } else {
            *it = a[i]; // Nếu tìm thấy, thay thế giá trị tại vị trí đó
        }
    }
    cout << "Do dai cua chuoi tang dan dai nhat la: " << lis.size() << endl; // In độ dài chuỗi tăng dần dài nhất
    cout << "Chuoi tang dan dai nhat la: ";
    for (int i=0;i<lis.size();++i){
        cout << lis[i] << " "; // In ra chuỗi tăng dần
    }
    cout << '\n';
}

int main() {
    srand(time(0)); // Khởi tạo seed cho hàm rand()
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    for (int i=1;i<=n;++i){
        a[i] = rand() % 20; // Khởi tạo giá trị ngẫu nhiên từ 0 đến 19
    }
    cout << "Cac phan tu trong mang: ";
    for (int i=1;i<=n;++i){
        cout << a[i] << " "; // In ra các phần tử trong mảng
    }
    cout << '\n';
    LIS_coban(); // Gọi hàm tìm chuỗi tăng dần dài nhất
    LIS_nangcao(); // Gọi hàm tìm chuỗi tăng dần dài nhất nâng cao
    return 0;
}