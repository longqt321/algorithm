### Bài 1: Đánh số độ phức tạp thuật toán

#### a, Thuật toán đệ quy $a^n$

Nhận xét:
Với trường hợp n = 0, thuật toán lập tức kết thúc và trả về kết quả -> Độ phức tạp là O(1) cho trường hợp cơ sở
Với trường hợp n > 0, thuật toán sẽ đệ quy tối đa n lần, với mỗi lần tốn O(1) để thực hiện tính toán.
Vậy độ phức tạp thời gian của thuật toán trên là O(n)

#### b, Thuật toán lặp tính $a^n$

Xét vòng lặp for, ta thấy rằng vòng lặp sẽ được thực thi đúng N lần, với mỗi lần thực hiện 1 phép tính có độ phức tạp O(1)
Vậy độ phức tạp thời gian của thuật toán trên là O(n)

#### c, Thuật toán đệ quy tính số Lucas thứ n

Với trường hợp n = 0 hoặc n = 1, thuật toán lập tức kết thúc và trả về kết quả -> Độ phức tạp là O(1) cho trường hợp cơ sở
Với trường hợp n > 1, với mỗi tầng đệ quy thứ n, thuật toán sẽ phân thành 2 nhánh tương ứng cho nhánh n-1 và n-2, sau đó nhánh n-1 sẽ tiếp tục đệ quy phân thành 2 nhánh n-2 và n-3, tương tự với những nhánh còn lại.
Ta nhận thấy rằng, với mỗi nút đại diện cho số Lucas thứ k, ta cần tính toán 2 nút con tương ứng đại diện cho k-1 và k-2. Từ đó ta thấy rằng cây đệ quy của thuật toán này sẽ tương tự như cây nhị phân => Sẽ có $2^n$ nút, mỗi nút thực hiện 1 phép toán O(1)
Vậy độ phức tạp thời gian của thuật toán trên là O($2^n$)

### Bài 2: Thuật toán quy hoạch động tìm dãy con chung dài nhất của 2 dãy X và Y

#### a, Dùng giả lệnh trình bày thuật toán.

Bước 1: Khởi tạo mảng 2 chiều dp[n][m]. Với n là độ dài xâu X, m là độ dài xâu Y
Bước 2: Khởi tạo giá trị ban đầu cho mảng

```cpp
    for (int i=0;i<=n;++i) dp[i][0] = 0;
    for (int j=0;j<=m;++j) dp[0][j] = 0;
```

Bước 3: Tính toán độ dài của dãy con chung dài nhất

```cpp
for (int i=1;i<=n;++i){
        for (int j=1;j<=m;++j){
            if (A[i-1] == B[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
```

Bước 4: Truy vết để lấy dãy con chung dài nhất

```cpp
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
```

Đánh giá độ phức tạp:
Việc tính toán độ dài của dãy con chung dài nhất sử dụng 2 vòng lặp for lồng nhau, với mỗi lần lặp, ta chỉ thực hiện 1 phép toán O(1). Vậy độ phức tạp của việc tính toán độ dài là O(n\*m)
Việc truy vết để lấy dãy con chung dài nhất sử dụng 1 vòng lặp, với mỗi bước của vòng lặp ta thực hiện 1 phép toán O(1) (Giả sử xem việc nối kí tự mới vào xâu kết quả chỉ tốn O(1)). Ta thấy rằng, dãy con chung dài nhất có độ dài tối đa bằng min(n,m). Vì vậy, vòng lặp chỉ được thực hiện min(n,m) lần. Vì vậy độ phức tạp của bước truy vết là O(min(n,m)).

Vậy độ phức tạp cuối cũng sẽ là max(O(n*m),O(min(n,m))) = O(n*m);
