// Digunakan untuk fungsi input dan output, seperti printf dan scanf.
#include <stdio.h>
// Digunakan untuk mengimpor file book.h
#include "../include/book.h"

int main() {
    // Variable untuk menyimpan pilihan menu
    int choice;
    do {
        // Menampilkan menu apa saja yang tersedia
        printf("\n=== MENU ===\n");
        printf("2. View History\n");
        printf("4. Delete History\n");
        printf("8. Exit\n");
        printf("Silahkan pilih menu (1-8): ");
        // Mengambil nilai input yang dipilih pengguna
        scanf("%d", &choice);

        // Proses pilihan pengguna
        switch (choice) {
            // Menu untuk melihat riwayat history
            case 2:
                // Memaggail fungsi yang memperoses lihat data history
                viewHistory();
                break;
            // Menu untuk delete data history
            case 4:
                // Memaggail fungsi yang memperoses delete data history
                deleteHistory();
                break;
            //Menu untuk keluar dari program book store
            case 8:
                printf("Kembali ke menu utama...\n");
                break;
            //kondisi default jika pilihan user diluar dari pilhan angka 1-8
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (choice != 8); // Loop hingga pengguna memilih angka 8 untuk keluar dari program
    return 0;
}