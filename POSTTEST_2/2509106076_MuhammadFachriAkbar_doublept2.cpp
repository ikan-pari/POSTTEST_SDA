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
		cout << "  Data sudah penuh." << endl;
		return;
	}
	Kereta &k = jadwal[total];

	cout << "\n  ===== Tambah Data Kereta =====" << endl;

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

	cout << "\n  ===== Linear Search (Rute) =====" << endl;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "  Kota Asal   : "; getline(cin, asal);
	cout << "  Kota Tujuan : "; getline(cin, tujuan);

	cout << "\n  Proses pencarian:" << endl;
	cout << string(60, '-') << endl;

	bool ketemu = false;

	for (int i = 0; i < n; i++) {
		cout << "  Iterasi " << setw(2) << (i + 1) << " -> "
			 << (arr + i)->asalKota << " -> " << (arr + i)->tujuanKota;

		if ((arr + i)->asalKota == asal && (arr + i)->tujuanKota == tujuan) {
			cout << "  <-- COCOK!" << endl;

			if (i != 0) swapData(arr, arr + i);

			cout << "\n";
			headerTabel();
			cetakBaris(1, *(arr));

			ketemu = true;
			break;
		} else {
			cout << endl;
		}
	}

	if (!ketemu)
		cout << "\n  Tidak ditemukan." << endl;
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
	if (n == 0) { cout << "  Belum ada data." << endl; return; }

	int target;
	cout << "\n  ===== Jump Search =====" << endl;
	cout << "  Nomor Kereta: "; cin >> target;

	sortByNomor(arr, n);

	int step = sqrt(n);
	int prev = 0;

	while (prev < n && (arr + min(step, n) - 1)->nomorKereta < target) {
		prev = step;
		step += sqrt(n);
	}

	for (int i = prev; i < min(step, n); i++) {
		if ((arr + i)->nomorKereta == target) {
			swapData(arr, arr + i);
			cout << "\n";
			headerTabel();
			cetakBaris(1, *arr);
			return;
		}
	}

	cout << "  Tidak ditemukan." << endl;
}

void merge(Kereta *arr, int l, int m, int r) {
	int n1 = m - l + 1;
	int n2 = r - m;

	Kereta L[n1], R[n2];

	for (int i = 0; i < n1; i++) L[i] = arr[l + i];
	for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

	int i = 0, j = 0, k = l;

	while (i < n1 && j < n2) {
		if (L[i].namaKereta < R[j].namaKereta)
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}

	while (i < n1) arr[k++] = L[i++];
	while (j < n2) arr[k++] = R[j++];
}

void mergeSort(Kereta *arr, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void selectionSort(Kereta *arr, int n) {
	for (int i = 0; i < n - 1; i++) {
		int minIdx = i;
		for (int j = i + 1; j < n; j++) {
			if ((arr + j)->hargaTiket < (arr + minIdx)->hargaTiket)
				minIdx = j;
		}
		if (minIdx != i) swapData(arr + i, arr + minIdx);
	}
}

int partition(Kereta *arr, int low, int high) {
	double pivot = (arr + high)->hargaTiket;
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if ((arr + j)->hargaTiket < pivot) {
			i++;
			swapData(arr + i, arr + j);
		}
	}
	swapData(arr + i + 1, arr + high);
	return i + 1;
}

void quickSort(Kereta *arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int bmSearch(string text, string pattern) {
	int m = pattern.size(), n = text.size();
	int bad[256];
	for (int i = 0; i < 256; i++) bad[i] = -1;
	for (int i = 0; i < m; i++) bad[(int)pattern[i]] = i;

	int shift = 0;
	while (shift <= n - m) {
		int j = m - 1;
		while (j >= 0 && pattern[j] == text[shift + j]) j--;
		if (j < 0) return shift;
		else shift += max(1, j - bad[(int)text[shift + j]]);
	}
	return -1;
}

void cariBM(Kereta *arr, int n) {
	string key;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "\n  ===== Boyer Moore Search =====" << endl;
	cout << "  Nama Kereta: ";
	getline(cin, key);

	for (int i = 0; i < n; i++) {
		if (bmSearch((arr + i)->namaKereta, key) != -1) {
			cout << "\n";
			headerTabel();
			cetakBaris(1, *(arr + i));
			return;
		}
	}

	cout << "  Tidak ditemukan." << endl;
}

void isiDataAwal() {
	Kereta sample[] = {
		{101, "Argo Bromo Anggrek", "Jakarta", "Surabaya", "08:00", 450000},
		{205, "Gajayana", "Malang", "Jakarta", "17:30", 380000},
		{312, "Taksaka", "Yogyakarta", "Jakarta", "10:15", 310000}
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
		cout << "  1. Tampil Semua" << endl;
		cout << "  2. Tambah Data" << endl;
		cout << "  3. Linear Search" << endl;
		cout << "  4. Jump Search" << endl;
		cout << "  5. Merge Sort" << endl;
		cout << "  6. Selection Sort" << endl;
		cout << "  7. Boyer Moore" << endl;
		cout << "  8. Quick Sort" << endl;
		cout << "  0. Keluar" << endl;

		garis();
		cout << "  Pilihan: "; cin >> pilihan;

		switch (pilihan) {
			case 1: tampilSemua(jadwal, total); break;
			case 2: tambahKereta(); break;
			case 3: linearSearch(jadwal, total); break;
			case 4: jumpSearch(jadwal, total); break;
			case 5: mergeSort(jadwal, 0, total - 1); tampilSemua(jadwal, total); break;
			case 6: selectionSort(jadwal, total); tampilSemua(jadwal, total); break;
			case 7: cariBM(jadwal, total); break;
			case 8: quickSort(jadwal, 0, total - 1); tampilSemua(jadwal, total); break;
			case 0: cout << "\n  Terima kasih.\n"; break;
			default: cout << "  Pilihan salah.\n";
		}

		if (pilihan != 0) {
			cout << "\n  Tekan Enter...";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
		}

	} while (pilihan != 0);

	return 0;
}