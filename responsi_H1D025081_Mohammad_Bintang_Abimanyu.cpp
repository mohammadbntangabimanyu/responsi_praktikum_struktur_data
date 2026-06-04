/*
    Nama : Mohammad Bintang Abimanyu
    NIM  : H1D025081
    File : Responsi_H1D025081_Mohammad Bintang Abimanyu.cpp
*/

#include <iostream>
#include <string> //agar bisa menggunakan tipe data string

using namespace std; 

//Mengubah nama node* menjadi address untuk memudahkan pemahaman
typedef struct Node* address;

//Definisi struktur Node untuk queue dan stack
struct Node {
    string nama;
    address next;
};

// Pointer utama untuk queue dan stack
address front = NULL; //--> menunjuk ke antrian paling depan
address rear = NULL; //--> menunjuk ke antrian paling belakang
address top = NULL; //--> menunjuk ke elemen teratas stack

//pengecekan apakah queue kosong
bool isQueueEmpty() {
    return front == NULL;
}

//pengecekan apakah stack kosong
bool isStackEmpty() {
    return top == NULL;
}

// Menu 1: Tambah antrian (Enqueue)
void daftarPasien(string nama) {
    address baru = new Node();
    baru->nama = nama;
    baru->next = NULL;

    if (isQueueEmpty()) {
        front = rear = baru; //ketika antrian kosong, node baru menjadi front dan rear
    } else {
        rear->next = baru;
        rear = baru;
    }
    cout << "---> Pasien atas nama " << nama << " berhasil didaftarkan ke antrian. <--\n";
}

// Menu 2: Panggil pasien (Dequeue + Push ke Stack)
void panggilPasien() {
    if (isQueueEmpty()) {
        cout << "---> Peringatan: Antrian kosong, tidak ada yang bisa dipanggil! <--\n";
        return;
    }

    // Ambil data dari antrian terdepan
    address temp = front;
    string pasien_diproses = temp->nama;

    cout << "---> Pasien atas nama " << pasien_diproses << " sedang diperiksa <--\n";

    // Proses dequeue
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    delete temp;

    // ketika pasien sudah diproses, data pasien tersebut akan otomatis masuk ke stack sebagai riwayat pemeriksaan
    address baru = new Node();
    baru->nama = pasien_diproses;
    baru->next = top;
    top = baru;
}

// Menu 3: Cetak isi queue
void tampilkanAntrian() {
    // jika antrian kosong, tampilkan pesan khusus
    if (isQueueEmpty()) {
        cout << "=> Antrian saat ini kosong.<= \n";
        return;
    }
    cout << "--- Daftar Antrian Saat Ini ---\n";
    address saat_ini = front;
    //looping while untuk menampilkan semua pasien yang sedang mengantri, dengan nomor urutannya
    int nomor = 1;
    while (saat_ini != NULL) {
        cout << nomor << ". " << saat_ini->nama << "\n";
        saat_ini = saat_ini->next;
        nomor++;
    }
}

// Menu 4: Cetak isi stack (LIFO)
void tampilkanRiwayat() {
    // jika stack kosong, tampilkan pesan khusus
    if (isStackEmpty()) {
        cout << "---> Belum ada riwayat pemeriksaan. <--\n";
        return;
    }
    cout << "=== Riwayat Pemeriksaan (Terbaru ke Terlama) ===\n";
    address saat_ini = top;
    //looping while untuk menampilkan riwayat pasien yang sudah diproses
    while (saat_ini != NULL) {
        cout << "- " << saat_ini->nama << "\n";
        saat_ini = saat_ini->next;
    }
}

int main() {
    char pilihan; 
    string nama_pasien;
    char pilih_ulang;

    do {
        cout << "\n=== SISTEM LAYANAN ABIMANYU SEHAT ===\n";
        cout << "1. Daftar Pasien Baru (Antrian)\n";
        cout << "2. Panggil Pasien Selanjutnya\n";
        cout << "3. Tampilkan Antrian Pasien Saat Ini\n";
        cout << "4. Tampilkan Riwayat Pemeriksaan\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;

        
        // Proteksi jika user menginput di luar karakter '1' sampai '5'
        if (pilihan < '1' || pilihan > '5') {
            cout << "\nInput tidak sesuai! hanya boleh input 1-5\n";
            
            // Looping ketat untuk memastikan user hanya menginput y atau n
            while (true) {
                cout << "Mau ulangi proses? (y/n): ";
                cin >> pilih_ulang;

                if (pilih_ulang == 'y' || pilih_ulang == 'Y') {
                    pilihan = '0'; // Trigger nilai netral agar loop do-while berputar ulang
                    break;         // Keluar dari loop y/n
                } 
                else if (pilih_ulang == 'n' || pilih_ulang == 'N') {
                    pilihan = '5'; // Bypass nilai ke '5' untuk menghentikan program
                    cout << "Keluar dari program. Terima kasih!\n";
                    break;         // Keluar dari loop y/n
                } 
                else {
                    cout << "Pilihan salah! Harap masukkan 'y' atau 'n'.\n";
                }
            }
            continue; // Skip switch-case di bawah, langsung lompat ke evaluasi while utama
        }

        switch (pilihan) {
            case '1':
                cout << "Masukkan Nama Pasien: ";
                cin.get(); // Buang karakter enter sisa input menu
                getline(cin, nama_pasien);
                daftarPasien(nama_pasien);
                break;
            case '2':
                panggilPasien();
                break;
            case '3':
                tampilkanAntrian();
                break;
            case '4':
                tampilkanRiwayat();
                break;
            case '5':
                cout << "Keluar dari program. Terima kasih!\n";
                break;
        }
    } while (pilihan != '5');

    return 0;
}