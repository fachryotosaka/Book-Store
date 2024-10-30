// Memastikan file ini hanya diikutkan sekali
#ifndef BOOK_H
#define BOOK_H

// Batas maksimal jumlah buku
#define MAX_BOOKS 100
// Batas maksimal jumlah history pembelian
#define MAX_HISTORY 100
// Definsi nama file dan menentukan lokasi file buku
#define FILENAME_BOOK "db/book.txt"
// Definsi nama file dan menentukan lokasi file history
#define FILENAME_HISTORY "db/history.txt"

// Struktur untuk menyimpan informasi data buku
typedef struct {
    int kode;
    char nama[100];
    char jenis[50];
    float harga;
} Buku;

// Struktur untuk menyimpan informasi data history pembelian
typedef struct {
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