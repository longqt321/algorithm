#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int a[1000],n,input[1000];


void radix_sort(int start, int end) {
    int amax = *max_element(a + start, a + end + 1); // Tìm giá trị lớn nhất trong mảng
    vector<int> cnt(amax + 1, 0); // Tạo mảng đếm với kích thước amax + 1
    for (int i = start; i <= end; ++i) {
        cnt[a[i]]++; // Tăng giá trị đếm cho mỗi phần tử
    }
    int k=1;
    for (int i=0;i<=amax;++i){
        for (int j=1;j<=cnt[i];++j){
            a[k++] = i; // Ghi lại các phần tử vào mảng a
        }
    }
}


int main() {
    cout << "Nhap so phan tu cua mang: ";
    cin >> n;
    for (int i=1;i<=n;++i){
        input[i] = rand() % 100; // Khởi tạo mảng ngẫu nhiên
        a[i] = input[i];
    }
    cout << "Mang truoc khi sap xep: ";
    for (int i=1;i<=n;++i){
        cout << a[i] << " ";
    }

    radix_sort(1, n);
    cout << "\nMang sau khi sap xep: ";
    for (int i=1;i<=n;++i){
        cout << a[i] << " ";
    }
    sort(input + 1, input + n + 1); // Sắp xếp mảng input để so sánh
    bool ok = true;
    for (int i=1;i<=n;++i){
        if (a[i] != input[i]) {
            ok = false; // Nếu có phần tử không khớp, đánh dấu là không đúng
            break;
        }
    }
    if (ok) {
        cout << "\nSap xep chinh xac!" << endl;
    } else {
        cout << "\nSap xep sai!" << endl;
    }
    return 0;
}