#include <iostream>
#include <string>
using namespace std;

struct BukuNode {
    string judulBuku;
    BukuNode* next;

    BukuNode(string judul) {
        judulBuku = judul;
        next = nullptr;
    }
};

BukuNode* tambahBuku(BukuNode* head, string judul) {
    BukuNode* newNode = new BukuNode(judul);
    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;
    }
    
    BukuNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

bool cariBuku(BukuNode* head, string judulDicari) {
    if (head == nullptr) return false;

    BukuNode* temp = head;
    do {
        if (temp->judulBuku == judulDicari) {
            return true;
        }
        temp = temp->next;
    } while (temp != head);

    return false;
}

int main() {
    BukuNode* head = nullptr;
    
    head = tambahBuku(head, "Struktur Data dengan C++");
    head = tambahBuku(head, "Pengantar Algoritma");
    head = tambahBuku(head, "Pemrograman Berorientasi Objek");
    head = tambahBuku(head, "Sistem Basis Data");

    string buku1 = "Pengantar Algoritma";
    string buku2 = "Kalkulus Lanjut";

    cout << "Mencari buku '" << buku1 << "': " 
         << (cariBuku(head, buku1) ? "Ditemukan" : "Tidak Ditemukan") << endl; 

    cout << "Mencari buku '" << buku2 << "': " 
         << (cariBuku(head, buku2) ? "Ditemukan" : "Tidak Ditemukan") << endl; 

    return 0;
}