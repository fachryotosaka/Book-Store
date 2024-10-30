// Memastikan file ini hanya diikutkan sekali
#ifndef BOOK_H
#define BOOK_H

#define MAX_BOOKS 100
#define MAX_HISTORY 100
#define MAX_LENGTH 100
#define FILENAME_BOOK "../db/book.txt"
#define FILENAME_HISTORY "../db/history.txt"


// Struktur untuk menyimpan informasi data buku
typedef struct {
    int kode;
    char nama[MAX_LENGTH];
    char jenis[50];
    float harga;
} Buku;

// Struktur untuk menyimpan informasi data history pembelian
typedef struct {
    int id;           // ID unik untuk setiap transaksi
    char tanggal[20]; //tanggal pembelian
    char kode[10]; //kode buku
    char nama[100]; //nama buku
    char jenis[50]; //jenis buku
    float harga; //harga buku
    int jumlah; //jumlah buku yang dibeli
    float total; //total harga
} History;

void viewHistory(); //deklarasi fungsi viewHistory untuk menampilkan data history
void deleteHistory(); //deklarasi fungsi viewHistory untuk delete data history
void listMenu(); //deklarasi fungsi listMenu untuk menampilkan daftar menu yang tersedia

#endif // BOOK_H

// RUNNING PROGRAM
// gcc -o bookstore src/main.c src/book.c -I include
// .\bookstore