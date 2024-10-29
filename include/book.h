#ifndef BOOK_H
#define BOOK_H

#define MAX_BOOKS 100
#define MAX_HISTORY 100
#define FILENAME_BOOK "../db/book.txt"
#define FILENAME_HISTORY "../db/history.txt"

typedef struct {
    int kode;
    char nama[100];
    char jenis[50];
    float harga;
} Buku;

typedef struct {
    int kode_buku;
    float total_harga;
} History;

#endif // BOOK_H
