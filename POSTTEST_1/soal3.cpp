#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {

    int* awal = arr;
    int* akhir = arr + n - 1;

    while(awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;

        awal++;
        akhir--;
    }
}

int main() {

    int nilai[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "Array sebelum dibalik:" << endl;

    int* p = nilai;
    while(p < nilai + n) {
        cout << "Nilai: " << *p << " | Alamat: " << p << endl;
        p++;
    }

    reverseArray(nilai, n);

    cout << endl;
    cout << "Array setelah dibalik:" << endl;

    p = nilai;
    while(p < nilai + n) {
        cout << "Nilai: " << *p << " | Alamat: " << p << endl;
        p++;
    }

    return 0;
}