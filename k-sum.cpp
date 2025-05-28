#include<iostream>
#include<vector>
#include<algorithm>

// Bài toán k-sum, tìm dãy con có tổng bằng k.

using namespace std;
int n, k;
int a[1000];
vector<int>trace; // Mảng trace để lưu trữ các phần tử đã chọn
int cnt=0;
int dp[1000][1000]; // Bảng DP để lưu trữ giá trị tối ưu cho bài toán k-sum

void init() {
    cnt=0;
    trace.clear();
    for (int i=1;i<=n;++i) {
        dp[i][0] = 1; // Khởi tạo dp[i][0] = 1, tức là có một cách để chọn dãy con có tổng bằng 0 (không chọn phần tử nào)
    }
}

// Thuật toán tìm k-sum = backtracking, độ phức tạp O(2^n). To vãi l
void quaylui(int i,int k){
    if (k==0){
        cnt++;
        cout << "Tìm thấy dãy con có tổng bằng k: ";
        for (int x : trace) {
            cout << x << " "; // In ra các phần tử trong dãy con
        }
        cout << '\n';
        return;
    }
    if (i > n || k < 0) {
        return; // Nếu đã duyệt hết mảng hoặc k < 0 thì dừng
    }
    // Không chọn phần tử a[i]
    quaylui(i + 1, k);
    // Chọn phần tử a[i]
    trace.push_back(a[i]); // Lưu phần tử a[i] vào trace
    quaylui(i + 1, k - a[i]); // Gọi đệ quy với k giảm đi giá trị của a[i]
    trace.pop_back();
}

// Thuật toán tìm k-sum = DP, độ phức tạp O(n*k). Dùng bảng DP để lưu trữ số cách chọn dãy con có tổng bằng k
void dp_coban(int k){
    for (int i=1;i<=n;++i){
        for (int j=1;j<=k;++j){
            if (j < a[i]) {
                dp[i][j] = dp[i-1][j]; // Không chọn phần tử a[i]
            } else {
                dp[i][j] = dp[i-1][j] + dp[i-1][j-a[i]]; // Chọn hoặc không chọn phần tử a[i]
            }
        }
    }
}

int main(){
    cout << "Nhập số lượng phần tử và giá trị k: ";
    cin >> n >> k;
    for (int i=1;i<=n;++i){
        a[i] = rand() % 10+1; // Khởi tạo giá trị ngẫu nhiên từ 1 đến 10
    }
    cout << "Mảng a: ";
    for (int i=1;i<=n;++i){
        cout << a[i] << " "; // In ra mảng a
    }
    cout << '\n';
    cout << "Tìm kiếm bằng phương pháp backtracking:\n";
    init();
    quaylui(1, k); // Gọi hàm backtracking từ phần tử đầu tiên
    cout << "Tổng số dãy con có tổng bằng k: (backtracking) " << cnt << '\n';
    init();
    cout << "Tìm kiếm bằng phương pháp DP:\n";
    dp_coban(k); // Gọi hàm DP để tính số cách chọn dãy con có tổng bằng k
    cout << "Số cách chọn dãy con có tổng bằng k: (QHĐ) " << dp[n][k] << '\n';
    return 0;
}