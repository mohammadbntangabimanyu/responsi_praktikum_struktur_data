/*
    Nama : Mohammad Bintang Abimanyu
    NIM  : H1D025081
    Shift Awal : F
    Shift Akhir : C
*/

#include <iostream>
#include <string> 

using namespace std; 

// Sederhanakan penulisan pointer struct menjadi address
typedef struct Node* address;

// Node universal untuk method antrian dan riwayat
struct Node {
    string nama;
    address next;
};

// Pointer utama penunjuk memori
address front = NULL; // ini untuk menunjuk ke antrian paling depan
address rear = NULL;  // ini untuk menunjuk ke antrian paling belakang
address top = NULL;   // ini untuk menunjuk ke stack paling atas (riwayat terbaru)

// fungsi cek antrian kosong
bool isQueueEmpty() {
    return front == NULL;
}

// fungsi cek stack kosong
bool isStackEmpty() {
    return top == NULL;
}

// Menu 1: Tambah antrian (Enqueue)
void daftar_pasien() {
    string nama; 

    cout << "Masukkan Nama Pasien: ";
    // buang enter sisa menu utama agar getline tidak skip
    cin.get(); 
    // pakai getline supaya bisa membaca nama dengan spasi
    getline(cin, nama); 

    address newNode = new Node();
    newNode->nama = nama;
    newNode->next = NULL;

    if (isQueueEmpty()) {
        front = rear = newNode; 
    } else {
        rear->next = newNode;  
        rear = newNode;        
    }
    cout << "=> Pasien " << nama << " berhasil didaftarkan ke antrian.\n";
}

// Menu 2: Panggil pasien (Dequeue + Push ke Stack)
void panggil_pasien() {
    if (isQueueEmpty()) {
        cout << "---> Peringatan: Antrian kosong, tidak ada yang bisa dipanggil! <--\n";
        return;
    }

    // ambil data antrian terdepan
    address temp = front;
    string pasien_diproses = temp->nama;

    cout << "---> Pasien atas nama " << pasien_diproses << " sedang diperiksa <--\n";

    // proses hapus dari antrian (Dequeue)
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    delete temp;

    // setelah di hapus di antrian, otomatis push ke stack riwayat
    address baru = new Node();
    baru->nama = pasien_diproses;
    baru->next = top;
    top = baru;
}

// Menu 3: Cetak isi queue (FIFO)
void tampilkan_antrian() {
    if (isQueueEmpty()) {
        cout << "=> Antrian saat ini kosong.<= \n";
        return;
    }
    cout << "--- Daftar Antrian Saat Ini ---\n";
    address saat_ini = front;
    int nomor = 1;
    
    while (saat_ini != NULL) {
        cout << nomor << ". " << saat_ini->nama << "\n";
        saat_ini = saat_ini->next;
        nomor++;
    }
}

// Menu 4: Cetak isi stack (LIFO)
void tampilkan_riwayat() {
    if (isStackEmpty()) {
        cout << "---> Belum ada riwayat pemeriksaan. <--\n";
        return;
    }
    cout << "=== Riwayat Pemeriksaan (Terbaru ke Terlama) ===\n";
    address saat_ini = top;
    
    while (saat_ini != NULL) {
        cout << "- " << saat_ini->nama << "\n";
        saat_ini = saat_ini->next;
    }
}

int main() {
    char pilihan; 
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

        // Validasi input selain menu 1-5
        if (pilihan < '1' || pilihan > '5') {
            cout << "\nInput tidak sesuai! hanya boleh input 1-5\n";
            
            while (true) {
                cout << "Mau ulangi proses? (y/n): ";
                cin >> pilih_ulang;

                if (pilih_ulang == 'y' || pilih_ulang == 'Y') {
                    pilihan = '0'; 
                    break;         
                } 
                else if (pilih_ulang == 'n' || pilih_ulang == 'N') {
                    pilihan = '5'; 
                    cout << "Keluar dari program. Terima kasih!\n";
                    break;         
                } 
                else {
                    cout << "Pilihan salah! Harap masukkan 'y' atau 'n'.\n";
                }
            }
            continue; 
        }

        switch (pilihan) {
            case '1':
                daftar_pasien();
                break;
            case '2':
                panggil_pasien();
                break;
            case '3':
                tampilkan_antrian();
                break;
            case '4':
                tampilkan_riwayat();
                break;
            case '5':
                cout << "Keluar dari program. Terima kasih!\n";
                break;
        }
    } while (pilihan != '5');

    return 0;
}