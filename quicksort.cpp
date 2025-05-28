#include <iostream>
#include <algorithm>
using namespace std;
int a[1000],n,input[1000];


void radix_sort(int left, int right) {
    if (left >= right) return;
    int i = left, j = right, pivot = a[(left + right) / 2];
    // Chọn phần tử giữa làm chốt
    while (i <= j) {
        while (a[i] < pivot) i++; // Tìm phần tử lớn hơn chốt từ bên trái
        while (a[j] > pivot) j--; // Tìm phần tử nhỏ hơn chốt từ bên phải
        if (i <= j) {
            swap(a[i], a[j]); // Hoán đổi hai phần tử
            i++;
            j--;
        }
    }

    radix_sort(left, j); 
    radix_sort(i, right); 
}

int main() {
    cout << "Nhap so phan tu cua mang: ";
    cin >> n;
    for (int i=1;i<=n;++i){
        input[i] = rand() % 10; // Khởi tạo mảng ngẫu nhiên
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