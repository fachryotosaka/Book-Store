#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/book.h"

int main() {
    Buku daftarBuku[MAX_BOOKS];
    History history[MAX_HISTORY];
    int totalBuku = 0;
    int totalHistory = 0;

    loadBuku(daftarBuku, &totalBuku);

    int choice;
    do {
        printf("\n=== MENU ===\n");
        printf("1. Input\n");
        printf("2. View History\n");
        printf("4. Delete History\n");
        printf("5. Delete Book\n");
        printf("8. Exit\n");
        printf("Silahkan pilih menu (1-8): ");

        scanf("%d", &choice);

        // Proses pilihan pengguna
        switch (choice) {
            case 1:
                inputBuku(daftarBuku, &totalBuku);
                break;
            case 2:
                viewHistory();
                break;
            // Menu untuk delete data history
            case 4:
                // Memaggail fungsi yang memperoses delete data history
                deleteHistory();
                break;
            //Menu untuk keluar dari program book store
            case 8:
                cleanup(daftarBuku, totalBuku);
                break;
            //kondisi default jika pilihan user diluar dari pilhan angka 1-8
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 8); // Loop hingga pengguna memilih angka 8 untuk keluar dari program
    return 0;
}
