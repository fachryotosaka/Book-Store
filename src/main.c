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
        printf("3. View Data buku\n");
        printf("4. Delete History\n");
        printf("5. Delete Buku\n");
        printf("6. Beli Buku\n");
        printf("7. Exit\n");
        printf("Silahkan pilih menu (1-7): ");

        scanf("%d", &choice);

        // Proses pilihan pengguna
        switch (choice) {
            case 1:
                inputBuku(daftarBuku, &totalBuku);
                break;
            case 2:
                viewHistory();
            case 3:
                view_databuku(); // Memanggil fungsi untuk melihat data buku
                break;
            case 4:
                deleteHistory();
                break;
            case 5:
                // Memaggail fungsi yang memperoses delete buku
                DeleteBook();
                break;
            case 6:
                beliBuku();
            //Menu untuk keluar dari program book store
            case 7:
                cleanup(daftarBuku, totalBuku);
                break;
            //kondisi default jika pilihan user diluar dari pilhan angka 1-8
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 7); // Loop hingga pengguna memilih angka 8 untuk keluar dari program
    return 0;
}
