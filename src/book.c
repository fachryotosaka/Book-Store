#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../include/book.h"

void loadBuku(Buku buku[], int *totalBuku) {
    FILE *file = fopen(FILENAME_BOOK, "r");
    if (file == NULL) {
        printf("File tidak ditemukan, membuat file baru.\n");
        return;
    }

    int newId = getNewId(file);
    fclose(file); 

    file = fopen(FILENAME_BOOK, "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk memuat data.\n");
        return;
    }

    while (fscanf(file, "%d#%99[^#]#%49[^#]#%f\n", 
                  &buku[*totalBuku].kode,
                  buku[*totalBuku].nama, 
                  buku[*totalBuku].jenis,
                  &buku[*totalBuku].harga) == 4) {
        (*totalBuku)++;
    }
    fclose(file);

    if (*totalBuku > 0) {
        buku[0].kode = newId; 
    }
}

void inputBuku(Buku buku[], int *totalBuku) { 
    if (*totalBuku >= MAX_BOOKS) {
        printf("Database buku sudah penuh.\n");
        return;
    }

    Buku newBuku;

    // Ambil ID baru dari file
    FILE *file = fopen(FILENAME_BOOK, "r");
    if (file == NULL) {
        perror("Gagal membuka file untuk mendapatkan ID baru.\n");
        newBuku.kode = 1; // Jika file tidak ada, mulai dari 1
    } else {
        newBuku.kode = getNewId(file);
        fclose(file);
    }

    printf("Nama Buku: ");
    scanf(" %[^\n]", newBuku.nama);
    printf("Jenis Buku: ");
    scanf(" %[^\n]", newBuku.jenis);
    printf("Harga Buku: ");
    scanf("%f", &newBuku.harga);

    buku[*totalBuku] = newBuku;
    (*totalBuku)++;

    printf("Data buku berhasil ditambahkan.\n");
}

int getNewIdFromCurrentTotal(int totalBuku) {
    return totalBuku + 1;
}

void saveBuku(const Buku buku[], int totalBuku) {
    FILE *file = fopen(FILENAME_BOOK, "a");
    if (file == NULL) {
        perror("Gagal membuka file untuk menyimpan data");
        return;
    }

    // Simpan data buku terakhir ke file
    fprintf(file, "%d#%s#%s#%.2f\n", 
            buku[totalBuku - 1].kode, 
            buku[totalBuku - 1].nama, 
            buku[totalBuku - 1].jenis, 
            buku[totalBuku - 1].harga);

    fclose(file);
    printf("Data buku berhasil disimpan.\n");
}

void cleanup(Buku buku[], int totalBuku) {
    saveBuku(buku, totalBuku);
    printf("Kembali ke menu utama...\n");
}

void view_databuku() {
    
    // Membuka file book dalam mode read
    FILE *file = fopen(FILENAME_BOOK, "r");

    if (file == NULL) {
        printf("Error: Tidak dapat membuka file history\n");
        return;
    }

    // Variabel untuk membaca data per baris
    char line[MAX_LENGTH];
    int index = 1;

    // Menampilkan teks untuk header tabel
    printf("\n=== DAFTAR BUKU ===\n");
    printf("No  Kode    Nama Buku                   Jenis       Harga\n");
    printf("------------------------------------------------------------\n");


    // Membaca file baris per baris
    while (fgets(line, sizeof(line), file)) {

        // Menghapus karakter newline (\n) di akhir string
        line[strcspn(line, "\n")] = 0;

        // Struct sementara untuk menyimpan data per baris
        Buku buku;

        // Memisahkan data berdasarkan delimiter '#'
        sscanf(line, "%d#%99[^#]#%49[^#]#%f", 
            &buku.kode, 
            buku.nama, 
            buku.jenis, 
            &buku.harga);
        
        // Menampilkan data dalam format tabel
        printf("%-3d %-7d %-28s %-10s %.2f\n",
            index++, 
            buku.kode, 
            buku.nama, 
            buku.jenis, 
            buku.harga);
    }
    
    // Menutup file setelah selesai dibaca
    fclose(file);
    return;
}


void beliBuku(){
    
    char line[MAX_LENGTH];
    FILE *fileBook = fopen(FILENAME_BOOK, "r");
    

    if (fileBook == NULL) {
    printf("Error: Tidak dapat membuka file buku\n");
    return;  
    }

    // Menghitung Jumlah data Buku
    int count = 0;

    while(fgets(line, sizeof(line),fileBook)){
        count++;
    } fseek(fileBook, 0, SEEK_SET); //Reset pointer file ke awal

    FILE *fileHistory = fopen(FILENAME_HISTORY, "a+");
    if (fileHistory == NULL) {
        printf("Error: Tidak dapat membuka file history\n");
        fclose(fileBook);  
        return;
    }

    // Validasi data buku memiliki data atau tidak, abort if not
    if (fgets(line, sizeof(line), fileBook) == NULL) {
    printf("\nTidak ada data Buku yang tersedia!\n");
    fclose(fileBook);
    fclose(fileHistory);
    return;
    }
    
    
    int entry = 0;
    Buku bukuEntry[MAX_ENTRY];
    History historyEntry[MAX_ENTRY];
    char repeat ='y';

    // LOOP OPTION BELI
    do {

        view_databuku();

        char input[10];
        char *endptr;

        printf("Masukan nomor kode buku yang ingin dibeli (0 - %d) atau 0 untuk membatalkan pembelian: ", count);
        scanf("%s", &input);
        
        int buyId = 0;
        buyId = strtol(input, &endptr, 10);

        if (*endptr != '\0') {
        printf("Error: Masukan harus berupa angka!\n");
        continue;
        }

        if(buyId == 0){
            printf("Pembelian dibatalkan \n");
            fclose(fileBook);
            fclose(fileHistory);
            return; 
        }else if (buyId > count){
            printf("Data buku tidak ditemukan \n");
            continue;
        }


        fseek(fileBook, 0, SEEK_SET);
        bukuEntry[entry] = getBukuById(fileBook, buyId); //Mencari data buku berdasarkan id

        if (bukuEntry[entry].kode == 0){
            printf("Error : Data buku tidak ditemukan\n");
            continue;
        }


        printf("Masukan jumlah yang ingin dibeli : ");
        scanf("%s", &input);

        int jumlah = strtol(input, &endptr, 10);
        
        if (*endptr != '\0') {
        printf("Error: Masukan harus berupa angka!\n");
        continue;
        }

        char date[11];
        getCurrentDate(date, sizeof(date)); // Get date dan simpan pada variable date
        

        //Assign setiap value ke dalam struct History
        historyEntry[entry].id = getNewId(fileHistory);
        safeStrCopy(historyEntry[entry].tanggal, date, sizeof(historyEntry[entry].tanggal));// Memastikan adanya terminator null di akhir string
        snprintf(historyEntry[entry].kode, sizeof(historyEntry[entry].kode), "%d", bukuEntry[entry].kode); // Mengubah int ke string
        safeStrCopy(historyEntry[entry].nama, bukuEntry[entry].nama, sizeof(historyEntry[entry].nama));
        safeStrCopy(historyEntry[entry].jenis, bukuEntry[entry].jenis, sizeof(historyEntry[entry].jenis));
        historyEntry[entry].harga = bukuEntry[entry].harga;
        historyEntry[entry].jumlah = jumlah;
        historyEntry[entry].total = bukuEntry[entry].harga * jumlah;

        

        // Validasi melanjutkan pembelian buku
        if(entry < 11){
            printf("Buku telah dimasukan dalam keranjang\n");
            printf("Apakah anda ingin lanjut membeli buku? (y/n) : ");
            scanf(" %c", &repeat);
        }else{
            printf("Keranjang anda sudah penuh\n");
            repeat = 'n';
            break;
        }
        entry++;
    }while(repeat !='n' && repeat !='N');

    printf("\n=== KERANJANG PEMBELIAN ===\n");
    printf("No  Tanggal         Kode    Nama Buku                   Jenis       Harga    Jumlah  Total\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i<entry; i++){
        printf("%-3d %-14s %-7s %-28s %-10s %-8.0f %-7d %.0f\n",
               i+1, 
               historyEntry[i].tanggal, 
               historyEntry[i].kode, 
               historyEntry[i].nama, 
               historyEntry[i].jenis, 
               historyEntry[i].harga, 
               historyEntry[i].jumlah, 
               historyEntry[i].total);
    }

    char confirm;

    printf("Apakah anda ingin mengkonfirmasi pembelian? (y/n) : ");
    scanf(" %c", &confirm);

    // Validasi konfirmasi
    if(confirm == 'Y' || confirm == 'y'){
        
        fileHistory = fopen(FILENAME_HISTORY, "a");// Re-open file dengan write mode
        if (fileHistory == NULL) {
            printf("Error: Tidak dapat membuka file history\n");
            fclose(fileBook);  
            fclose(fileHistory);  
            return;
        }

        // Save data setiap history
        for(int i = 0; i < entry; i++){
            if (fprintf(fileHistory, "%d#%s#%s#%s#%s#%.0f#%d#%.0f\n",
                        historyEntry[i].id, 
                        historyEntry[i].tanggal, 
                        historyEntry[i].kode,
                        historyEntry[i].nama, 
                        historyEntry[i].jenis,
                        historyEntry[i].harga, 
                        historyEntry[i].jumlah,
                        historyEntry[i].total) < 0) {
                // Handle error jika gagal menulis file
                perror("Error menulis history pada file\n");
                fclose(fileBook);
                fclose(fileHistory);
                return;
            }
            fflush(fileHistory);
        }
    }else{
        printf("Pembelian dibatalkan\n");
        fclose(fileBook);
        fclose(fileHistory);
        return;
    }

    
    printf("Buku berhasil di beli\n");
    fclose(fileBook);
    fclose(fileHistory);
    return;
}


void DeleteBook() {
    int kode_to_delete;

    view_databuku();

    printf("\nMasukkan kode buku yang ingin dihapus (0 untuk batal): ");
    scanf("%d", &kode_to_delete);

    if (kode_to_delete == 0) {
        printf("Penghapusan dibatalkan.\n");
        return;
    }

    FILE *file = fopen(FILENAME_BOOK, "r");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk membaca\n");
        return;
    }

    Buku books[MAX_BOOKS];
    int totalBooks = 0;

    // membaca buku kedalam array
    while (fscanf(file, "%d#%99[^#]#%49[^#]#%f\n", 
                  &books[totalBooks].kode,
                  books[totalBooks].nama, 
                  books[totalBooks].jenis,
                  &books[totalBooks].harga) == 4) {
        totalBooks++;
    }
    fclose(file);

    // menuliskan semua buku kecuali buku yang mau dihapus
    file = fopen(FILENAME_BOOK, "w");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk menulis\n");
        return;
    }

    for (int i = 0; i < totalBooks; i++) {
        if (books[i].kode != kode_to_delete) {
            fprintf(file, "%d#%s#%s#%.2f\n", 
                    books[i].kode, 
                    books[i].nama, 
                    books[i].jenis, 
                    books[i].harga);
        }
    }
    fclose(file);
    printf("Buku dengan kode %d berhasil dihapus.\n", kode_to_delete);
}


// Fungsi untuk menampilkan data dari file history
void viewHistory() {
    // Membuka file history dalam mode read
    FILE *file = fopen(FILENAME_HISTORY, "r");

    // Kondisi jika file history tidak berhasil dibuka
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file history\n");
        return;
    }

    // Variabel untuk membaca data per baris dan menghitung index
    char line[256];
    int index = 1;

    // Menampilkan teks untuk header tabel
    printf("\n=== HISTORY PEMBELIAN ===\n");
    printf("No  Tanggal         Kode    Nama Buku                   Jenis       Harga    Jumlah  Total\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    
    // Membaca file baris per baris
    while (fgets(line, sizeof(line), file)) {
        // Menghapus karakter newline (\n) di akhir string
        line[strcspn(line, "\n")] = 0;

        // Struct sementara untuk menyimpan data per baris
        History h;

        // Memisahkan data berdasarkan delimiter '#'
        sscanf(line, "%d#%[^#]#%[^#]#%[^#]#%[^#]#%f#%d#%f",
               &h.id, h.tanggal, h.kode, h.nama, h.jenis, &h.harga, &h.jumlah, &h.total);
        
        // Menampilkan data dalam format tabel
        printf("%-3d %-14s %-7s %-28s %-10s %-8.0f %-7d %.0f\n",
               index++, h.tanggal, h.kode, h.nama, h.jenis, h.harga, h.jumlah, h.total);
    }
    
    // Menutup file setelah selesai dibaca
    fclose(file);
}

// Fungsi untuk menghapus data history
void deleteHistory() {
    // Membuka file history dengan mode read
    FILE *file = fopen(FILENAME_HISTORY, "r");

    // Kondisi jika file history tidak berhasil dibuka
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

    // Kondisi jika file history kosong
    if (lineCount == 0) {
        printf("\nTidak ada data history yang tersedia!\n");
        fclose(file);
        return;
    }

    // Array untuk menyimpan semua data history
    History histories[MAX_HISTORY];
    int index = 0;
    
    // Looping utama proses delete
    while (1) {
        // Menampilkan teks untuk header tabel
        printf("\n=== DELETE HISTORY ===\n");
        printf("No  Tanggal         Kode    Nama Buku                Jenis       Harga    Jumlah  Total\n");
        printf("--------------------------------------------------------------------------------------\n");
        
        // Reset posisi file dan index
        rewind(file);
        index = 0;
        
        // Membaca dan menampilkan semua data
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            sscanf(line, "%d#%[^#]#%[^#]#%[^#]#%[^#]#%f#%d#%f",
                   &histories[index].id, histories[index].tanggal, histories[index].kode, 
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
            
            // Kondisi jika user membatalkan hapus data
            if(choice == 0) {
                printf("Pembatalan penghapusan data...\n");
                fclose(file);
                return;
            } else if(choice < 1 || choice > lineCount) {
                // Kondisi jika nomor yang dipilih user tidak ada dalam index
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
                fprintf(file, "%d#%s#%s#%s#%s#%.0f#%d#%.0f\n",
                       histories[i].id, histories[i].tanggal, histories[i].kode,
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
        
        // Kondisi jika semua data sudah terhapus
        if (lineCount == 0) {
            printf("\nSemua data history telah dihapus!\n");
            fclose(file);
            return;
        }
    }
}

int getNewId(FILE* file){
    int maxId = 0;
    char line [MAX_LENGTH];

    // Loop setiap line di file
    while(fgets(line, sizeof(line), file) !=NULL){
        
        // Remove spaces/newline
        line[strcspn(line, "\n")] = '\0';

        // Seperate string, ambil id
        char *idStr = strtok(line, "#");

        if(idStr != NULL){
            // Parse id ke int
            int id = atoi(idStr);

            //Check dan replace max id dengan id terbesar
            if(maxId < id){
                maxId = id;
            } 
        }

    }

    //Return id terbesar + 1
    return ++maxId;

}

// Helper untuk memotong spasi
void trimLeadingSpaces(char* str) {
    char* p = str;
    while (isspace((unsigned char)*p)) p++;
    memmove(str, p, strlen(p) + 1);
}

Buku getBukuById(FILE *file, int searchId) {
    int id;
    char line[MAX_LENGTH];
    Buku b = {0}; 

    if (file == NULL) {
        printf("Error: Tidak dapat membuka file buku\n");
        return b;  
    }

    while (fgets(line, sizeof(line), file)) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';


        char *idStr = strtok(line, "#");
        if (idStr == NULL) {
            continue; // Skip line tanpa id
        }

        // parse id ke string
        id = atoi(idStr);
        

        // memotong sisa line dari spasi
        char *remainingLine = strtok(NULL, ""); 
        if (remainingLine) {
            trimLeadingSpaces(remainingLine);
        }

        // Check id sesuai id search
        if (id == searchId) {
            if (sscanf(remainingLine, "%99[^#]#%49[^#]#%f", 
                       b.nama, 
                       b.jenis, 
                       &b.harga) == 3) { // Expecting 3 field
                b.kode = id; // Set the kode
               
                return b; // Return buku sesuai id
            }
        }
    }

    return b; // Return default book (empty)
}

void getCurrentDate(char *date, size_t dateSize) {
    time_t now = time(NULL); // Ambil tanggal sekrang
    struct tm *localTime = localtime(&now); // ubah ke waktu lokal

    // Format tanggal ke "YYYY-MM-DD" dan simpan pada pointer date
    strftime(date, dateSize, "%Y-%m-%d", localTime);
}

//Helper untuk menambahkan null terminator
void safeStrCopy(char *dest, const char *src, size_t destSize) {
    strncpy(dest, src, destSize - 1);       
    dest[destSize - 1] = '\0'; 
}