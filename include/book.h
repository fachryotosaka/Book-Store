#ifndef BOOK_H
#define BOOK_H

#define MAX_BOOKS 100
#define MAX_HISTORY 100
#define MAX_LENGTH 100
#define FILENAME_BOOK "db/book.txt"
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
    int id;           
    char tanggal[20]; 
    char kode[10]; 
    char nama[100]; 
    char jenis[50];
    float harga; 
    int jumlah; 
    float total;
} History;

int getNewId(FILE* file);
int getNewIdFromCurrentTotal(int totalBuku);
void loadBuku(Buku buku[], int *totalBuku);
void inputBuku(Buku buku[], int *totalBuku);
void saveBuku(const Buku buku[], int totalBuku);
void cleanup(Buku buku[], int totalBuku);

void viewHistory(); 
void deleteHistory(); 
void listMenu(); 

#endif // BOOK_H

// RUNNING PROGRAM
// gcc -o bookstore src/main.c src/book.c -I include
// .\bookstore