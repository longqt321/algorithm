#include <iostream>
#include <vector>

using namespace std;
string A = "bulul";
string B = "trebuemlultrebulll";
// Khởi tạo mảng 2 chiều cho quy hoạch động LCS
int dp[100][100];


string LCS_dequy(int i, int j){
    if (i < 0 || j < 0)   return "";
    if (A[i] == B[j]){
        return LCS_dequy(i - 1, j - 1) + A[i];
    }
    else{
        string left = LCS_dequy(i - 1, j);
        string right = LCS_dequy(i, j - 1);
        return (left.length() > right.length()) ? left : right;
    }
}

void LCS_QHD(int i,int j){
    int n = A.length();
    int m = B.length();
    // Khởi tạo giá trị ban đầu
    for (int i=0;i<=n;++i) dp[i][0] = 0;
    for (int j=0;j<=m;++j) dp[0][j] = 0;

    // dp[i][j] sẽ chứa độ dài của LCS của A[0..i-1] và B[0..j-1]
    for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j){
            if (A[i-1] == B[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    // Truy vết chuỗi con chung dài nhất
    // Truy vết từ dp[n][m] về dp[0][0]
    string result = "";
    int x = n, y = m;
    while (x > 0 && y > 0){
        if (A[x - 1] == B[y - 1]){
            result = A[x - 1] + result; // Thêm ký tự vào đầu chuỗi kết quả
            x--;
            y--;
        } else {
            // Nếu như việc di chuyển lên cho kết quả tối ưu hơn
            if (dp[x - 1][y] > dp[x][y - 1]) {
                x--; // Di chuyển lên
            } else {
                y--; // Di chuyển sang trái
            }
        }
    }
    cout << "LCS (QHD): " << result << endl;
}

int main(){
    int n = A.length();
    int m = B.length();
    string result = LCS_dequy(n - 1, m - 1);
    cout << "LCS: " << result << endl;
    LCS_QHD(n, m);

    return 0;
}