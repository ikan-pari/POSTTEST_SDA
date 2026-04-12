#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <limits>
#define MAX_DATAKERETA 50
#define MAX_ANTRIAN    20
#define MAX_RIWAYAT    20
using namespace std;

struct Kereta {
    int    nomorKereta;
    string namaKereta;
    string asalKota;
    string tujuanKota;
    string jamBerangkat;
    double hargaTiket;
};

struct Penumpang {
    string nama;
    int    nomorKereta;
    string asalKota;
    string tujuanKota;
    double hargaTiket;
};

struct Queue {
    Penumpang data[MAX_ANTRIAN];
    int front;
    int rear;
};

void initQueue(Queue &q) {
    q.front = -1;
    q.rear  = -1;
}

bool isQueueFull(const Queue &q) {
    return q.rear == MAX_ANTRIAN - 1;
}

bool isQueueEmpty(const Queue &q) {
    return q.front == -1 || q.front > q.rear;
}

bool enqueue(Queue &q, const Penumpang &p) {
    if (isQueueFull(q)) return false;
    if (q.front == -1) q.front = 0;
    q.rear++;
    q.data[q.rear] = p;
    return true;
}

bool dequeue(Queue &q, Penumpang &out) {
    if (isQueueEmpty(q)) return false;
    out = q.data[q.front];
    q.front++;
    if (isQueueEmpty(q)) q.front = q.rear = -1;
    return true;
}

bool peekQueue(const Queue &q, Penumpang &out) {
    if (isQueueEmpty(q)) return false;
    out = q.data[q.front];
    return true;
}

struct Stack {
    Penumpang data[MAX_RIWAYAT];
    int top;
};

void initStack(Stack &s) {
    s.top = -1;
}

bool isStackFull(const Stack &s) {
    return s.top == MAX_RIWAYAT - 1;
}

bool isStackEmpty(const Stack &s) {
    return s.top == -1;
}

bool push(Stack &s, const Penumpang &p) {
    if (isStackFull(s)) return false;
    s.top++;
    s.data[s.top] = p;
    return true;
}

bool pop(Stack &s, Penumpang &out) {
    if (isStackEmpty(s)) return false;
    out = s.data[s.top];
    s.top--;
    return true;
}

bool peekStack(const Stack &s, Penumpang &out) {
    if (isStackEmpty(s)) return false;
    out = s.data[s.top];
    return true;
}

Kereta jadwal[MAX_DATAKERETA];
int total = 0;

void garis()       { cout << string(80, '=') << endl; }
void garisPendek() { cout << string(80, '-') << endl; }

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
    if (n == 0) { cout << "\n  Belum ada data kereta.\n" << endl; garis(); return; }
    headerTabel();
    for (int i = 0; i < n; i++) cetakBaris(i + 1, *(arr + i));
    garis();
    cout << "  Total kereta: " << n << endl;
    garis();
}

void tambahKereta() {
    if (total >= MAX_DATAKERETA) { cout << "  Data sudah penuh." << endl; return; }
    Kereta &k = jadwal[total];
    cout << "\n  ===== Tambah Data Kereta =====\n";
    cout << "  Nomor Kereta  : "; cin >> k.nomorKereta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "  Nama Kereta   : "; getline(cin, k.namaKereta);
    cout << "  Kota Asal     : "; getline(cin, k.asalKota);
    cout << "  Kota Tujuan   : "; getline(cin, k.tujuanKota);
    cout << "  Jam Berangkat : "; getline(cin, k.jamBerangkat);
    cout << "  Harga Tiket   : "; cin >> k.hargaTiket;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    total++;
    cout << "\n  Data berhasil ditambahkan!" << endl;
}

void linearSearch(Kereta *arr, int n) {
    if (n == 0) { cout << "  Belum ada data." << endl; return; }
    string asal, tujuan;
    cout << "\n  ===== Linear Search (Rute) =====\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "  Kota Asal   : "; getline(cin, asal);
    cout << "  Kota Tujuan : "; getline(cin, tujuan);
    cout << "\n  Proses pencarian:\n" << string(60, '-') << endl;
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        cout << "  Iterasi " << setw(2) << (i+1) << " -> "
             << (arr+i)->asalKota << " -> " << (arr+i)->tujuanKota;
        if ((arr+i)->asalKota == asal && (arr+i)->tujuanKota == tujuan) {
            cout << "  <-- COCOK!\n\n";
            if (i != 0) swapData(arr, arr+i);
            headerTabel();
            cetakBaris(1, *arr);
            ketemu = true;
            break;
        } else cout << endl;
    }
    if (!ketemu) cout << "\n  Tidak ditemukan." << endl;
}

void sortByNomor(Kereta *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if ((arr+j)->nomorKereta < (arr+minIdx)->nomorKereta) minIdx = j;
        if (minIdx != i) swapData(arr+i, arr+minIdx);
    }
}

void jumpSearch(Kereta *arr, int n) {
    if (n == 0) { cout << "  Belum ada data." << endl; return; }
    int target;
    cout << "\n  ===== Jump Search =====\n";
    cout << "  Nomor Kereta: "; cin >> target;
    sortByNomor(arr, n);
    int step = sqrt(n), prev = 0;
    while (prev < n && (arr + min(step,n) - 1)->nomorKereta < target) { prev = step; step += sqrt(n); }
    for (int i = prev; i < min(step,n); i++) {
        if ((arr+i)->nomorKereta == target) {
            swapData(arr, arr+i);
            cout << "\n"; headerTabel(); cetakBaris(1, *arr); return;
        }
    }
    cout << "  Tidak ditemukan." << endl;
}

void merge(Kereta *arr, int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    Kereta L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l+i];
    for (int j = 0; j < n2; j++) R[j] = arr[m+1+j];
    int i=0, j=0, k=l;
    while (i<n1 && j<n2) { if (L[i].namaKereta < R[j].namaKereta) arr[k++]=L[i++]; else arr[k++]=R[j++]; }
    while (i<n1) arr[k++]=L[i++];
    while (j<n2) arr[k++]=R[j++];
}

void mergeSort(Kereta *arr, int l, int r) {
    if (l < r) { int m=(l+r)/2; mergeSort(arr,l,m); mergeSort(arr,m+1,r); merge(arr,l,m,r); }
}

void selectionSort(Kereta *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if ((arr+j)->hargaTiket < (arr+minIdx)->hargaTiket) minIdx = j;
        if (minIdx != i) swapData(arr+i, arr+minIdx);
    }
}

int partition(Kereta *arr, int low, int high) {
    double pivot = (arr+high)->hargaTiket;
    int i = low-1;
    for (int j = low; j < high; j++) {
        if ((arr+j)->hargaTiket < pivot) { i++; swapData(arr+i, arr+j); }
    }
    swapData(arr+i+1, arr+high);
    return i+1;
}

void quickSort(Kereta *arr, int low, int high) {
    if (low < high) { int pi = partition(arr,low,high); quickSort(arr,low,pi-1); quickSort(arr,pi+1,high); }
}

int bmSearch(string text, string pattern) {
    int m=pattern.size(), n=text.size();
    int bad[256];
    for (int i=0; i<256; i++) bad[i]=-1;
    for (int i=0; i<m; i++) bad[(int)pattern[i]]=i;
    int shift=0;
    while (shift<=n-m) {
        int j=m-1;
        while (j>=0 && pattern[j]==text[shift+j]) j--;
        if (j<0) return shift;
        else shift += max(1, j - bad[(int)text[shift+j]]);
    }
    return -1;
}

void cariBM(Kereta *arr, int n) {
    string key;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n  ===== Boyer Moore Search =====\n";
    cout << "  Nama Kereta: "; getline(cin, key);
    for (int i=0; i<n; i++) {
        if (bmSearch((arr+i)->namaKereta, key) != -1) {
            cout << "\n"; headerTabel(); cetakBaris(1, *(arr+i)); return;
        }
    }
    cout << "  Tidak ditemukan." << endl;
}

Kereta* cariKeretaByNomor(Kereta *arr, int n, int nomorKereta) {
    for (int i = 0; i < n; i++) {
        if ((arr + i)->nomorKereta == nomorKereta)
            return arr + i;
    }
    return nullptr;
}

void headerTabelPenumpang() {
    cout << left
         << setw(4)  << "No"
         << setw(20) << "Nama Penumpang"
         << setw(8)  << "No.KA"
         << setw(14) << "Asal"
         << setw(14) << "Tujuan"
         << "Harga (Rp)" << endl;
    cout << string(80, '-') << endl;
}

void cetakPenumpang(int no, const Penumpang *p) {
    cout << left
         << setw(4)  << no
         << setw(20) << p->nama
         << setw(8)  << p->nomorKereta
         << setw(14) << p->asalKota
         << setw(14) << p->tujuanKota
         << "Rp " << fixed << setprecision(0) << p->hargaTiket << endl;
}

void menuEnqueue(Queue &q, Kereta *arr, int n) {
    if (isQueueFull(q)) {
        cout << "\n  [OVERFLOW] Antrian penuh! Kapasitas maksimum " << MAX_ANTRIAN << " penumpang.\n";
        return;
    }
    Penumpang p;
    int noKA;
    cout << "\n  ===== Pesan Tiket (Masuk Antrian) =====\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "  Nama Penumpang : "; getline(cin, p.nama);
    tampilSemua(arr, n);
    cout << "  Nomor Kereta yang dipesan: "; cin >> noKA;
    Kereta *k = cariKeretaByNomor(arr, n, noKA);
    if (k == nullptr) { cout << "\n  Nomor kereta tidak ditemukan!\n"; return; }
    p.nomorKereta = k->nomorKereta;
    p.asalKota    = k->asalKota;
    p.tujuanKota  = k->tujuanKota;
    p.hargaTiket  = k->hargaTiket;
    enqueue(q, p);
    cout << "\n  " << p.nama << " berhasil masuk antrian untuk kereta "
         << k->namaKereta << " (" << k->asalKota << " -> " << k->tujuanKota << ").\n";
    cout << "  Posisi dalam antrian: " << (q.rear - q.front + 1) << "\n";
}

void menuDequeue(Queue &q, Stack &s) {
    if (isQueueEmpty(q)) {
        cout << "\n  [UNDERFLOW] Antrian kosong! Tidak ada penumpang yang diproses.\n";
        return;
    }
    Penumpang p;
    dequeue(q, p);
    cout << "\n  ===== Proses Tiket =====\n";
    garisPendek();
    cout << "  Penumpang diproses:\n";
    headerTabelPenumpang();
    cetakPenumpang(1, &p);
    garisPendek();
    cout << "  Tiket berhasil diterbitkan untuk " << p.nama << "!\n";
    if (isStackFull(s)) {
        cout << "  [PERINGATAN] Stack riwayat penuh. Transaksi tidak dicatat.\n";
    } else {
        push(s, p);
        cout << "  Transaksi dicatat ke riwayat.\n";
    }
}

void menuPop(Stack &s) {
    if (isStackEmpty(s)) {
        cout << "\n  [UNDERFLOW] Riwayat kosong! Tidak ada transaksi yang dibatalkan.\n";
        return;
    }
    Penumpang p;
    pop(s, p);
    cout << "\n  ===== Batalkan Transaksi Terakhir =====\n";
    garisPendek();
    cout << "  Transaksi yang dibatalkan:\n";
    headerTabelPenumpang();
    cetakPenumpang(1, &p);
    garisPendek();
    cout << "  Transaksi atas nama " << p.nama << " telah dihapus dari riwayat.\n";
}

void menuPeek(const Queue &q, const Stack &s) {
    cout << "\n  ===== Peek Antrian & Riwayat =====\n";
    garisPendek();
    Penumpang p;
    cout << "  [ANTRIAN] Penumpang terdepan:\n";
    if (peekQueue(q, p)) { headerTabelPenumpang(); cetakPenumpang(1, &p); }
    else cout << "  Antrian kosong.\n";
    cout << endl;
    cout << "  [RIWAYAT] Transaksi terakhir:\n";
    if (peekStack(s, p)) { headerTabelPenumpang(); cetakPenumpang(1, &p); }
    else cout << "  Riwayat kosong.\n";
    garisPendek();
}

void tampilSemuaAntrian(const Queue &q) {
    cout << "\n  ===== Semua Antrian Tiket =====\n";
    if (isQueueEmpty(q)) { cout << "  Antrian kosong.\n"; return; }
    headerTabelPenumpang();
    int jumlah = q.rear - q.front + 1;
    for (int i = 0; i < jumlah; i++) {
        const Penumpang *ptr = q.data + q.front + i;
        cetakPenumpang(i + 1, ptr);
    }
    garisPendek();
    cout << "  Total dalam antrian: " << jumlah << " penumpang.\n";
}

void tampilSemuaRiwayat(const Stack &s) {
    cout << "\n  ===== Riwayat Transaksi =====\n";
    if (isStackEmpty(s)) { cout << "  Riwayat kosong.\n"; return; }
    headerTabelPenumpang();
    for (int i = s.top; i >= 0; i--) {
        const Penumpang *ptr = s.data + i;
        cetakPenumpang(s.top - i + 1, ptr);
    }
    garisPendek();
    cout << "  Total riwayat: " << (s.top + 1) << " transaksi.\n";
}

void isiDataAwal() {
    Kereta sample[] = {
        {101, "Argo Bromo Anggrek", "Jakarta",   "Surabaya", "08:00", 450000},
        {205, "Gajayana",           "Malang",     "Jakarta",  "17:30", 380000},
        {312, "Taksaka",            "Yogyakarta", "Jakarta",  "10:15", 310000}
    };
    int n = sizeof(sample) / sizeof(Kereta);
    for (int i = 0; i < n; i++) jadwal[i] = sample[i];
    total = n;
}

int main() {
    isiDataAwal();

    Queue antrian;
    Stack riwayat;
    initQueue(antrian);
    initStack(riwayat);

    int pilihan;

    do {
        headerMenu();
        cout << "  ---- Data Kereta ----\n";
        cout << "  1.  Tampil Semua Kereta\n";
        cout << "  2.  Tambah Data Kereta\n";
        cout << "  3.  Linear Search\n";
        cout << "  4.  Jump Search\n";
        cout << "  5.  Merge Sort\n";
        cout << "  6.  Selection Sort\n";
        cout << "  7.  Boyer Moore Search\n";
        cout << "  8.  Quick Sort\n";
        cout << "  ---- Antrian & Riwayat ----\n";
        cout << "  9.  Pesan Tiket (Enqueue)\n";
        cout << "  10. Proses Tiket (Dequeue)\n";
        cout << "  11. Batalkan Transaksi Terakhir (Pop)\n";
        cout << "  12. Peek Antrian & Riwayat\n";
        cout << "  13. Tampil Semua Antrian\n";
        cout << "  14. Tampil Semua Riwayat\n";
        cout << "  0.  Keluar\n";
        garis();
        cout << "  Pilihan: "; cin >> pilihan;

        switch (pilihan) {
            case 1:  tampilSemua(jadwal, total); break;
            case 2:  tambahKereta(); break;
            case 3:  linearSearch(jadwal, total); break;
            case 4:  jumpSearch(jadwal, total); break;
            case 5:  mergeSort(jadwal, 0, total-1); tampilSemua(jadwal, total); break;
            case 6:  selectionSort(jadwal, total); tampilSemua(jadwal, total); break;
            case 7:  cariBM(jadwal, total); break;
            case 8:  quickSort(jadwal, 0, total-1); tampilSemua(jadwal, total); break;
            case 9:  menuEnqueue(antrian, jadwal, total); break;
            case 10: menuDequeue(antrian, riwayat); break;
            case 11: menuPop(riwayat); break;
            case 12: menuPeek(antrian, riwayat); break;
            case 13: tampilSemuaAntrian(antrian); break;
            case 14: tampilSemuaRiwayat(riwayat); break;
            case 0:  cout << "\n  Terima kasih sudah menggunakan Program.\n"; break;
            default: cout << "  Pilihan tidak valid.\n";
        }

        if (pilihan != 0) {
            cout << "\n  Tekan Enter...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (pilihan != 0);

    return 0;
}