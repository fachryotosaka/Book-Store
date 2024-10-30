// Digunakan untuk fungsi input dan output, seperti printf dan scanf. 
#include <stdio.h>
//Digunakan untuk fungsi alokasi memori dan konversi, seperti atoi.
#include <stdlib.h>
//Digunakan untuk manipulasi string, seperti strcpy, dan strcmp.
#include <string.h>
// Digunakan untuk mengimpor file book.h
#include "../include/book.h"

// Fungsi untuk menampilkan data dari file history
void viewHistory() {
    // Membuka file history dalam mode read
    FILE *file = fopen(FILENAME_HISTORY, "r");

    // kondisi jika file history tidak berhasil dibuka
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file history\n");
        return;
    }

    // Variabel untuk membaca data per baris dan menghitung index
    char line[256];
    int index = 1;

    // menampilkan Text untuk header table
    printf("\n=== HISTORY PEMBELIAN ===\n");
    printf("No  Tanggal         Kode    Nama Buku                   Jenis       Harga    Jumlah  Total\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    
    // Membaca file baris per baris
    while (fgets(line, sizeof(line), file)) {
        // Menghapus karakter newline(\n) diakhir string
        line[strcspn(line, "\n")] = 0;

        // struct sementara untuk menyimpan data per baris
        History h;

        // Memisahkan data berdasarkan delimeiter '#'
        sscanf(line, "%[^#]#%[^#]#%[^#]#%[^#]#%f#%d#%f",
               h.tanggal, h.kode, h.nama, h.jenis, &h.harga, &h.jumlah, &h.total);
        
        // Menampilkan data dalam format tabel
        printf("%-3d %-14s %-7s %-28s %-10s %-8.0f %-7d %.0f\n",
               index++, h.tanggal, h.kode, h.nama, h.jenis, h.harga, h.jumlah, h.total);
    }
    
    // Menutup file setelah selesai dibaca
    fclose(file);
}

// Fungsi untuk menghapus data history
void deleteHistory() {
    // membuka file history dengan mode read
    FILE *file = fopen(FILENAME_HISTORY, "r");

    // kondisi jika file history tidak berhasil dibuka
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file history\n");
        return;
    }

    // Menghitung jumlah baris dalam file
    int lineCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        lineCount++;
    }
    // Mengembalikan pointer file ke awal
    rewind(file);

    // kondisi jika file history kosong
    if (lineCount == 0) {
        printf("\nTidak ada data history yang tersedia!\n");
        fclose(file);
        return;
    }

    // Array untuk menyimpan semua data history
    History histories[MAX_HISTORY];
    int index = 0;
    
    // looping utama proses delete
    while (1) {
        // Menampilkan text untuk header table
        printf("\n=== DELETE HISTORY ===\n");
        printf("No  Tanggal         Kode    Nama Buku                Jenis       Harga    Jumlah  Total\n");
        printf("--------------------------------------------------------------------------------------\n");
        
        // Reset posisi file dan index
        rewind(file);
        index = 0;
        
        // Membaca dan menampilkan semua data
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            sscanf(line, "%[^#]#%[^#]#%[^#]#%[^#]#%f#%d#%f",
                   histories[index].tanggal, histories[index].kode, 
                   histories[index].nama, histories[index].jenis, 
                   &histories[index].harga, &histories[index].jumlah, 
                   &histories[index].total);
            
            printf("%-3d %-14s %-7s %-28s %-10s %-8.0f %-7d %.0f\n",
                   index + 1, histories[index].tanggal, histories[index].kode,
                   histories[index].nama, histories[index].jenis,
                   histories[index].harga, histories[index].jumlah,
                   histories[index].total);
            index++;
        }

        // Input nomor data yang akan dihapus dengan validasi
        int choice;
        char input[10];
        int valid = 0;

        // Looping untuk meminta input yang valid
        do {
            printf("\nPilih nomor data yang akan dihapus (1-%d) atau 0 untuk batal: ", lineCount);
            scanf("%s", input);
            
            // Validasi apakah input adalah angka
            int isNumber = 1;
            for(int i = 0; input[i] != '\0'; i++) {
                if(input[i] < '0' || input[i] > '9') {
                    isNumber = 0;
                    break;
                }
            }
            
            // Kondisi jika yang diinput pengguna bukan angka
            if(!isNumber) {
                printf("Error: Masukan harus berupa angka!\n");
                continue;
            }
            
            choice = atoi(input);
            
            // kondisi jika user membatalkan hapus data
            if(choice == 0) {
                printf("Pembatalan penghapusan data...\n");
                fclose(file);
                return;
            } else if(choice < 1 || choice > lineCount) {
                // kondisi jika nomor yang dipilih user tidak ada dalam index
                printf("Error: Data dengan nomor %d tidak ditemukan!\n", choice);
            } else {
                valid = 1;
            }
        } while (!valid);

        // Tutup file sebelum menulis ulang
        fclose(file);

        // Buka file baru untuk menulis ulang data yang tidak dihapus
        file = fopen(FILENAME_HISTORY, "w");
        for (int i = 0; i < lineCount; i++) {
            if (i != choice - 1) { // Skip data yang dipilih untuk dihapus
                fprintf(file, "%s#%s#%s#%s#%.0f#%d#%.0f\n",
                       histories[i].tanggal, histories[i].kode,
                       histories[i].nama, histories[i].jenis,
                       histories[i].harga, histories[i].jumlah,
                       histories[i].total);
            }
        }
        fclose(file);
        printf("Data berhasil dihapus!\n");

        // Konfirmasi pengguna apakah ingin menghapus data lagi atau tidak
        char lanjut;
        printf("\nIngin menghapus data lagi? (y/n): ");
        scanf(" %c", &lanjut);
        
        if(lanjut != 'y' && lanjut != 'Y') {
            break;
        }

        // Buka file lagi untuk iterasi berikutnya
        file = fopen(FILENAME_HISTORY, "r");
        if (file == NULL) {
            printf("Error: Tidak dapat membuka file history\n");
            return;
        }

        // Update jumlah data untuk iterasi berikutnya
        lineCount = 0;
        while (fgets(line, sizeof(line), file)) {
            lineCount++;
        }
        
        // kondisi jika semua data sudah terhapus
        if (lineCount == 0) {
            printf("\nSemua data history telah dihapus!\n");
            fclose(file);
            return;
        }
    }
}