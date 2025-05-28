#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int a[1000],n,input[1000];


void radix_sort(int start, int end) {
    int amax = *max_element(a + start, a + end + 1); // Tìm giá trị lớn nhất trong mảng

    for (int exp = 1; amax / exp > 0; exp *= 10) {
        int output[1000] = {0};
        int count[10] = {0};

        for (int i = start; i <= end; ++i)
            count[(a[i] / exp) % 10]++;

        for (int i = 1; i < 10; ++i)
            count[i] += count[i - 1];

        for (int i = end; i >= start; --i) {
            int idx = (a[i] / exp) % 10;
            output[start + (--count[idx])] = a[i];
        }

        for (int i = start; i <= end; ++i)
            a[i] = output[i];
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