#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n; // Số lượng mặt hàng
int capacity; // Dung lượng của cái túi
int values[1000];
int weights[1000];
int dp1[1000][1000]; // Bảng DP để lưu trữ giá trị tối ưu cho bài toán cái túi 0/1 cơ bản
int dp2[1000]; // Bảng DP để lưu trữ giá trị tối ưu cho bài toán cái túi vô hạn
double dp3[1000]; // Bảng DP để lưu trữ giá trị tối ưu cho bài toán cái túi phân số


void init(){
    for (int i=0;i<1000;++i) {
        for (int j=0;j<1000;++j) {
            dp1[i][j] = 0; // Khởi tạo bảng DP với giá trị 0
        }
    }
    for (int i=0;i<1000;++i) {
        dp2[i] = 0; // Khởi tạo bảng DP cho bài toán cái túi vô hạn với giá trị 0
    }
    for (int i=0;i<1000;++i) {
        dp3[i] = 0.0; // Khởi tạo bảng DP cho bài toán cái túi phân số với giá trị 0.0
    }
}

// Bài toán cái túi 0/1 cơ bản, dạng đơn giản nhất
void knapsack01_basic(int capacity) {
    init();
    for (int i=1;i<=n;++i){
        for (int j=0;j<=capacity;++j){
            if (j < weights[i]) {
                dp1[i][j] = dp1[i-1][j]; // Không chọn mặt hàng i do không đủ trọng lượng
            } else {
                dp1[i][j] = max(dp1[i-1][j], dp1[i-1][j-weights[i]] + values[i]); // Chọn hoặc không chọn mặt hàng i
            }
        }
    }
    vector<int> selected_items; // Lưu trữ các mặt hàng được chọn
    int w = capacity;
    for (int i = n; i > 0; --i) {
        if (dp1[i][w] != dp1[i-1][w]) { // Nếu giá trị khác, tức là mặt hàng i được chọn
            selected_items.push_back(i);
            w -= weights[i]; // Giảm trọng lượng còn lại
        }
    }
    cout << "Giá trị tối ưu của cái túi 0/1 cơ bản là: " << dp1[n][capacity] << '\n';
    // In ra các mặt hàng được chọn
    cout << "Các mặt hàng được chọn: ";
    for (int i = selected_items.size() - 1; i >= 0; --i) {
        cout << selected_items[i] << " ";
    }
    cout << '\n';
}

// Bài toán cái túi vô hạn.  Tức một món đồ có thể được chọn vô hạn lần, miễn là trọng lượng <= capacity
void knapsack01_infinite(int capacity) {
    init();
    for (int w=0;w<=capacity;++w){
        for (int i=1;i<=n;++i){
            if (weights[i] <= w) {
                dp2[w] = max(dp2[w], dp2[w-weights[i]] + values[i]); // Chọn mặt hàng i nếu có thể
            }
        }
    }
    vector<int> selected_items; // Lưu trữ các mặt hàng được chọn
    int w = capacity;
    while (w > 0) {
        for (int i = 1; i <= n; ++i) {
            if (weights[i] <= w && dp2[w] == dp2[w - weights[i]] + values[i]) {
                selected_items.push_back(i); // Mặt hàng i được chọn
                w -= weights[i]; // Giảm trọng lượng còn lại
                break; // Chọn mặt hàng này và tiếp tục với trọng lượng mới
            }
        }
    }
    cout << "Giá trị tối ưu của cái túi vô hạn là: " << dp2[capacity] << '\n';
    cout << "Các mặt hàng được chọn: ";
    for (int i = selected_items.size() - 1; i >= 0; --i) {
        cout << selected_items[i] << " ";
    }
    cout << '\n';
   
}

// Bài toán cái túi phân số, tức là có thể chọn một phần của mặt hàng
void fractional_knapsack(double capacity) {
    init();
    vector<pair<double, int>> items; // Lưu trữ giá trị trên trọng lượng của mỗi mặt hàng
    for (int i = 1; i <= n; ++i) {
        items.push_back({(double)values[i] / weights[i], i}); // Tính giá trị trên trọng lượng
    }
    sort(items.rbegin(), items.rend()); // Sắp xếp theo giá trị trên trọng lượng giảm dần

    double total_value = 0.0;
    for (const auto& item : items) {
        int index = item.second;
        if (weights[index] <= capacity) {
            total_value += values[index]; // Chọn toàn bộ mặt hàng
            capacity -= weights[index];
        } else {
            total_value += item.first * capacity; // Chọn phần còn lại của mặt hàng
            break; // Không còn dung lượng trong túi
        }
    }

    cout << "Giá trị tối ưu của cái túi phân số là: " << total_value << '\n';
}

int main() {
    srand(time(0)); // Khởi tạo seed cho hàm rand()
    cout << "Nhập số lượng mặt hàng và dung lượng của cái túi: ";
    cin >> n >> capacity;
    for (int i=1;i<=n;++i){
        values[i] = rand() % 10; // Khởi tạo giá trị ngẫu nhiên
        weights[i] = rand() % 10; // Khởi tạo trọng lượng ngẫu nhiên
    }
    cout << "Số lượng mặt hàng: " << n << endl;
    for (int i=1;i<=n;++i){
        cout << "Mặt hàng " << i << ": Giá trị = " << values[i] << ", Trọng lượng = " << weights[i] << endl;
    }
    knapsack01_basic(capacity); // Giải bài toán cái túi 0/1 cơ bản
    knapsack01_infinite(capacity); // Giải bài toán cái túi vô hạn
    fractional_knapsack((double)capacity); // Giải bài toán cái túi phân số
    return 0;
}