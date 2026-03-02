#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {

    Mahasiswa mhs[5];

    for(int i = 0; i < 5; i++) {
        cout << "Data Mahasiswa ke-" << i+1 << endl;
        cout << "Nama : ";
        cin >> mhs[i].nama;
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        cout << endl;
    }

    float ipkTertinggi = mhs[0].ipk;
    int indeks = 0;

    for(int i = 1; i < 5; i++) {
        if(mhs[i].ipk > ipkTertinggi) {
            ipkTertinggi = mhs[i].ipk;
            indeks = i;
        }
    }

    cout << "Mahasiswa dengan IPK tertinggi:" << endl;
    cout << "Nama : " << mhs[indeks].nama << endl;
    cout << "NIM  : " << mhs[indeks].nim << endl;
    cout << "IPK  : " << mhs[indeks].ipk << endl;

    return 0;
}