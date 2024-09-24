#include <iostream>
#include <string>
using namespace std;

const int MAX = 100; 

struct barang {
    int id;
    string nama;
    int jumlah;
    float harga;
};

void tambah_barang(barang* gudang, int* jumlah_barang) {
    if (*jumlah_barang >= MAX) {
        cout << "Gudang penuh!" << endl;
        return;
    }

    barang* b = &gudang[*jumlah_barang];
    b->id = *jumlah_barang + 1;
    
    cout << "Masukkan nama barang: ";
    cin >> b->nama;
    
    cout << "Masukkan jumlah barang: ";
    cin >> b->jumlah;

    cout << "Masukkan harga barang: ";
    cin >> b->harga;

    (*jumlah_barang)++; 
    cout << "Barang berhasil ditambahkan!\n";
}

void tampil_barang(barang* gudang, int jumlah_barang) {
    if (jumlah_barang == 0) {
        cout << "Tidak ada barang di gudang.\n";
        return;
    }

    cout << "\nDaftar Barang di Gudang:\n";
    cout << "ID\tNama\tJumlah\tHarga\n";
    for (int i = 0; i < jumlah_barang; i++) {
        barang* b = &gudang[i];
        cout << b->id << "\t" << b->nama << "\t" << b->jumlah << "\t" << b->harga << endl;
    }
}

void update_barang(barang* gudang, int jumlah_barang) {
    int id;
    cout << "Masukkan ID barang yang akan diupdate: ";
    cin >> id;

    if (id < 1 || id > jumlah_barang) {
        cout << "ID barang tidak ditemukan.\n";
        return;
    }

    barang* b = &gudang[id - 1]; 
    cout << "Update nama barang: ";
    cin >> b->nama;
    
    cout << "Update jumlah barang: ";
    cin >> b->jumlah;

    cout << "Update harga barang: ";
    cin >> b->harga;

    cout << "Barang berhasil diupdate!\n";
}

void hapus_barang(barang* gudang, int* jumlah_barang) {
    int id;
    cout << "Masukkan ID barang yang akan dihapus: ";
    cin >> id;

    if (id < 1 || id > *jumlah_barang) {
        cout << "ID barang tidak ditemukan.\n";
        return;
    }

    for (int i = id - 1; i < *jumlah_barang - 1; i++) {
        gudang[i] = gudang[i + 1];
    }
    (*jumlah_barang)--; 

    cout << "Barang berhasil dihapus!\n";
}

int main() {
    barang gudang[MAX]; 
    int jumlah_barang = 0; 

    int pilihan;
    do {
        cout << "\n====Menu Gudang Sembako===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampil Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambah_barang(gudang, &jumlah_barang);
                break;
            case 2:
                tampil_barang(gudang, jumlah_barang);
                break;
            case 3:
                update_barang(gudang, jumlah_barang);
                break;
            case 4:
                hapus_barang(gudang, &jumlah_barang);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}
