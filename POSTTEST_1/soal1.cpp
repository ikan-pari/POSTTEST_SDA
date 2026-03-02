#include <iostream>
using namespace std;


// Analisis Kompleksitas Algoritma FindMin

// Pseudocode dan Cost:

// 1  procedure FindMin           C1   1      1
// 2  min ← A[0]                  C2   1      1
// 3  for i ← 1 to n-1            C3   n      n
// 4      if A[i] < min           C4   n-1    n-1
// 5          min ← A[i]          C5   0      n-1
// 6      end if                  C6   n-1    n-1
// 7  end for                     C7   n      n
// 8  return min                  C8   1      1

// Best Case (Tmin):
// kondisi if selalu salah
// T(n) = 4n + konstanta
// Big-O = O(n)

// Worst Case (Tmax):
// kondisi if selalu benar
// T(n) = 5n + konstanta
// Big-O = O(n)

// Kesimpulan:
// Best case dan worst case sama-sama O(n)


int main() {

    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;

    int min = A[0];
    int indeks = 0;

    for(int i = 1; i < n; i++) {
        if(A[i] < min) {
            min = A[i];
            indeks = i;
        }
    }

    cout << "Nilai minimum : " << min << endl;
    cout << "Indeks        : " << indeks << endl;

    return 0;
}