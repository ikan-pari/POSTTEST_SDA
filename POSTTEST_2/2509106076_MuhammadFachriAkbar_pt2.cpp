#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <limits>
#define MAX_DATAKERETA 50
using namespace std;

struct Kereta {
    int nomorKereta;
    string namaKereta;
    string asalKota;
    string tujuanKota;
    string jamBerangkat;
    double hargaTiket;
};

Kereta jadwal[MAX_DATAKERETA];
int total = 0;

void garis() {
    cout << string(80, '=') << endl;
}

void headerMenu() {
    garis();
    cout << setw(52) << "SISTEM MANAJEMEN KEBERANGKATAN KERETA API" << endl;
    garis();
}

void headerTabel() {
    cout << left
         << setw(5)  << "No"
         << setw(8)  << "No.KA"
         << setw(22) << "Nama Kereta"
         << setw(14) << "Asal"
         << setw(14) << "Tujuan"
         << setw(7)  << "Jam"
         << "Harga (Rp)" << endl;
    cout << string(80, '-') << endl;
}

void cetakBaris(int no, const Kereta &k) {
    cout << left
         << setw(5)  << no
         << setw(8)  << k.nomorKereta
         << setw(22) << k.namaKereta
         << setw(14) << k.asalKota
         << setw(14) << k.tujuanKota
         << setw(7)  << k.jamBerangkat
         << "Rp " << fixed << setprecision(0) << k.hargaTiket << endl;
}

void swapData(Kereta *a, Kereta *b) {
    Kereta tmp = *a;
    *a = *b;
    *b = tmp;
}

void tampilSemua(Kereta *arr, int n) {
    headerMenu();
    if (n == 0) {
        cout << "\n  Belum ada data kereta.\n" << endl;
        garis();
        return;
    }
    headerTabel();
    for (int i = 0; i < n; i++) {
        cetakBaris(i + 1, *(arr + i));
    }
    garis();
    cout << "  Total kereta: " << n << endl;
    garis();
}

void tambahKereta() {
    if (total >= MAX_DATAKERETA) {
        cout << "  Data sudah penuh, tidak bisa menambah lagi." << endl;
        return;
    }

    Kereta &k = jadwal[total];

    cout << "\n  ===== Tambah Data Kereta =====" << endl;

    cout << "  Nomor Kereta  : ";
    cin >> k.nomorKereta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "  Nama Kereta   : ";
    getline(cin, k.namaKereta);

    cout << "  Kota Asal     : ";
    getline(cin, k.asalKota);

    cout << "  Kota Tujuan   : ";
    getline(cin, k.tujuanKota);

    cout << "  Jam Berangkat : ";
    getline(cin, k.jamBerangkat);

    cout << "  Harga Tiket   : ";
    cin >> k.hargaTiket;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    total++;
    cout << "\n  Data berhasil ditambahkan!" << endl;
}

void linearSearch(Kereta *arr, int n) {
    if (n == 0) {
        cout << "  Belum ada data." << endl;
        return;
    }

    string asal, tujuan;

    cout << "\n  ===== Linear Search (Rute) =====" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "  Kota Asal   : ";
    getline(cin, asal);

    cout << "  Kota Tujuan : ";
    getline(cin, tujuan);

    cout << "\n  Proses pencarian:" << endl;
    cout << string(60, '-') << endl;

    bool ketemu = false;

    for (int i = 0; i < n; i++) {
        string a = (arr + i)->asalKota;
        string t = (arr + i)->tujuanKota;

        cout << "  Iterasi " << setw(2) << (i + 1) << " -> "
             << "[" << (arr + i)->namaKereta << "] "
             << a << " -> " << t;

        if (a == asal && t == tujuan) {
            cout << "  <-- COCOK!" << endl;

            if (i != 0) swapData(arr, arr + i);

            cout << "\n  Kereta ditemukan:" << endl;
            cout << string(60, '-') << endl;
            headerTabel();
            cetakBaris(1, *(arr));
            cout << string(60, '-') << endl;

            ketemu = true;
            break;
        } else {
            cout << "  (tidak cocok)" << endl;
        }
    }

    if (!ketemu) {
        cout << "\n  Kereta rute " << asal << " -> " << tujuan << " tidak ditemukan." << endl;
    }
}

void sortByNomor(Kereta *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->nomorKereta < (arr + minIdx)->nomorKereta)
                minIdx = j;
        }
        if (minIdx != i) swapData(arr + i, arr + minIdx);
    }
}

void jumpSearch(Kereta *arr, int n) {
    if (n == 0) {
        cout << "  Belum ada data." << endl;
        return;
    }

    int target;
    cout << "\n  ===== Jump Search (Nomor Kereta) =====" << endl;
    cout << "  Nomor Kereta yang dicari: ";
    cin >> target;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    sortByNomor(arr, n);

    cout << "\n  (Data diurutkan berdasarkan nomor kereta dulu)" << endl;

    int step = sqrt(n);
    int prev = 0;
    int found = -1;

    cout << "\n  Proses Jump Search (step = " << step << "):" << endl;
    cout << string(60, '-') << endl;

    while (prev < n && (arr + min(step, n) - 1)->nomorKereta < target) {
        int idx = min(step, n) - 1;

        cout << "  Jump ke indeks " << idx
             << " -> No.KA [" << (arr + idx)->nomorKereta << "] < " << target << endl;

        prev = step;
        step += sqrt(n);

        if (prev >= n) break;
    }

    cout << "  Cek linear di blok [" << prev << " .. " << min(step, n) - 1 << "]" << endl;

    for (int i = prev; i < min(step, n); i++) {
        cout << "  Cek indeks " << i
             << " -> No.KA [" << (arr + i)->nomorKereta << "]";

        if ((arr + i)->nomorKereta == target) {
            cout << "  <-- KETEMU!" << endl;
            found = i;
            break;
        } else {
            cout << endl;
        }
    }

    if (found != -1) {
        swapData(arr, arr + found);

        cout << "\n  Kereta ditemukan:" << endl;
        cout << string(60, '-') << endl;
        headerTabel();
        cetakBaris(1, *arr);
        cout << string(60, '-') << endl;
    } else {
        cout << "\n  Kereta nomor " << target << " tidak ditemukan." << endl;
    }
}

void mergeHelper(Kereta *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Kereta *kiri = new Kereta[n1];
    Kereta *kanan = new Kereta[n2];

    for (int i = 0; i < n1; i++) kiri[i] = *(arr + l + i);
    for (int j = 0; j < n2; j++) kanan[j] = *(arr + m + 1 + j);

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (kiri[i].namaKereta <= kanan[j].namaKereta)
            *(arr + k++) = kiri[i++];
        else
            *(arr + k++) = kanan[j++];
    }

    while (i < n1) *(arr + k++) = kiri[i++];
    while (j < n2) *(arr + k++) = kanan[j++];

    delete[] kiri;
    delete[] kanan;
}

void mergeSort(Kereta *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        mergeHelper(arr, l, m, r);
    }
}

void urutNama(Kereta *&arr, int n) {
    if (n == 0) {
        cout << "  Belum ada data." << endl;
        return;
    }

    mergeSort(arr, 0, n - 1);

    cout << "\n  Data berhasil diurutkan berdasarkan nama (A-Z).\n" << endl;
    tampilSemua(arr, n);
}

void urutHarga(Kereta *&arr, int n) {
    if (n == 0) {
        cout << "  Belum ada data." << endl;
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->hargaTiket < (arr + minIdx)->hargaTiket)
                minIdx = j;
        }
        if (minIdx != i) swapData(arr + i, arr + minIdx);
    }

    cout << "\n  Data berhasil diurutkan berdasarkan harga (termurah ke termahal).\n" << endl;
    tampilSemua(arr, n);
}

void isiDataAwal() {
    Kereta sample[] = {
        {101, "Argo Bromo Anggrek", "Jakarta", "Surabaya", "08:00", 450000},
        {205, "Gajayana", "Malang", "Jakarta", "17:30", 380000},
        {312, "Taksaka", "Yogyakarta", "Jakarta", "10:15", 310000},
        {418, "Bima", "Jakarta", "Surabaya", "21:00", 420000},
        {523, "Lodaya", "Bandung", "Solo", "07:00", 275000},
        {630, "Sembrani", "Jakarta", "Surabaya", "19:45", 395000},
        {744, "Sancaka", "Yogyakarta", "Surabaya", "06:30", 190000},
    };

    int n = sizeof(sample) / sizeof(Kereta);

    for (int i = 0; i < n; i++) jadwal[i] = sample[i];

    total = n;
}

int main() {
    isiDataAwal();
    int pilihan;

    do {
        headerMenu();

        cout << "  1. Tampil Semua Jadwal Kereta" << endl;
        cout << "  2. Tambah Data Kereta Baru" << endl;
        cout << "  3. Cari Kereta berdasarkan Rute (Linear Search)" << endl;
        cout << "  4. Cari Kereta berdasarkan Nomor (Jump Search)" << endl;
        cout << "  5. Urutkan Nama Kereta A-Z (Merge Sort)" << endl;
        cout << "  6. Urutkan Harga Tiket Termurah (Selection Sort)" << endl;
        cout << "  0. Keluar" << endl;

        garis();

        cout << "  Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilSemua(jadwal, total);
                break;
            case 2:
                tambahKereta();
                break;
            case 3:
                linearSearch(jadwal, total);
                break;
            case 4:
                jumpSearch(jadwal, total);
                break;
            case 5: {
                Kereta *p = jadwal;
                urutNama(p, total);
                break;
            }
            case 6: {
                Kereta *p = jadwal;
                urutHarga(p, total);
                break;
            }
            case 0:
                cout << "\n  Terima kasih, program selesai." << endl;
                break;
            default:
                cout << "  Pilihan tidak valid!" << endl;
        }

        if (pilihan != 0) {
            cout << "\n  Tekan Enter untuk kembali ke menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (pilihan != 0);

    return 0;
}