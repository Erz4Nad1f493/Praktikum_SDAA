#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct barang {
    int id;
    string nama;
    int jumlah;
    float harga;
    barang* next;
};

stack<barang*> stack_undo; 
queue<barang*> queue_barang; 

void tambah_barang(barang** head, int* jumlah_barang) {
    barang* new_barang = new barang;
    (*jumlah_barang)++;

    new_barang->id = *jumlah_barang;

    cout << "Masukkan nama barang: ";
    cin >> new_barang->nama;

    cout << "Masukkan jumlah barang: ";
    cin >> new_barang->jumlah;

    cout << "Masukkan harga barang: ";
    cin >> new_barang->harga;

    new_barang->next = NULL;

    if (*head == NULL) {
        *head = new_barang;
    } else {
        barang* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_barang;
    }

    cout << "Barang berhasil ditambahkan ke gudang!\n";
}

void tampil_barang(barang* head) {
    if (head == NULL) {
        cout << "Tidak ada barang di gudang.\n";
        return;
    }

    cout << "\nDaftar Barang di Gudang:\n";
    cout << "ID\tNama\tJumlah\tHarga\n";

    barang* temp = head;
    while (temp != NULL) {
        cout << temp->id << "\t" << temp->nama << "\t" << temp->jumlah << "\t" << temp->harga << endl;
        temp = temp->next;
    }
}

void update_barang(barang* head, int jumlah_barang) {
    int id;
    cout << "Masukkan ID barang yang akan diupdate: ";
    cin >> id;

    if (id < 1 || id > jumlah_barang) {
        cout << "ID barang tidak ditemukan.\n";
        return;
    }

    barang* temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }

    if (temp != NULL) {
        cout << "Update nama barang: ";
        cin >> temp->nama;

        cout << "Update jumlah barang: ";
        cin >> temp->jumlah;

        cout << "Update harga barang: ";
        cin >> temp->harga;

        cout << "Barang berhasil diupdate!\n";
    }
}

void hapus_barang(barang** head, int* jumlah_barang) {
    int id;
    cout << "Masukkan ID barang yang akan dihapus: ";
    cin >> id;

    if (id < 1 || id > *jumlah_barang) {
        cout << "ID barang tidak ditemukan.\n";
        return;
    }

    barang* temp = *head;
    barang* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        stack_undo.push(temp); 
        (*jumlah_barang)--;
        cout << "Barang berhasil dihapus!\n";
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        prev->next = temp->next;
        stack_undo.push(temp); 
        (*jumlah_barang)--;
        cout << "Barang berhasil dihapus!\n";
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}

void undo_hapus(barang** head, int* jumlah_barang) {
    if (stack_undo.empty()) {
        cout << "Tidak ada barang yang bisa di-undo.\n";
        return;
    }

    barang* last_deleted = stack_undo.top();
    stack_undo.pop();

    last_deleted->next = NULL;
    (*jumlah_barang)++;

    if (*head == NULL) {
        *head = last_deleted;
    } else {
        barang* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = last_deleted;
    }

    cout << "Barang dengan ID " << last_deleted->id << " berhasil dipulihkan!\n";
}

void terima_barang_baru() {
    barang* new_barang = new barang;

    cout << "Masukkan nama barang baru: ";
    cin >> new_barang->nama;

    cout << "Masukkan jumlah barang baru: ";
    cin >> new_barang->jumlah;

    cout << "Masukkan harga barang baru: ";
    cin >> new_barang->harga;

    new_barang->next = NULL;
    queue_barang.push(new_barang);

    cout << "Barang baru diterima dan dimasukkan ke antrian untuk diproses.\n";
}

void proses_barang_baru(barang** head, int* jumlah_barang) {
    if (queue_barang.empty()) {
        cout << "Tidak ada barang baru yang perlu diproses.\n";
        return;
    }

    barang* new_barang = queue_barang.front();
    queue_barang.pop();

    (*jumlah_barang)++;
    new_barang->id = *jumlah_barang;

    if (*head == NULL) {
        *head = new_barang;
    } else {
        barang* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_barang;
    }

    cout << "Barang baru dengan ID " << new_barang->id << " berhasil diproses dan dimasukkan ke gudang.\n";
}

int main() {
    barang* gudang = NULL;
    int jumlah_barang = 0;

    int pilihan;
    do {
        cout << "\n====Menu Gudang Sembako===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampil Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Undo Hapus Barang\n";
        cout << "6. Terima Barang Baru\n";
        cout << "7. Proses Barang Baru\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambah_barang(&gudang, &jumlah_barang);
                break;
            case 2:
                tampil_barang(gudang);
                break;
            case 3:
                update_barang(gudang, jumlah_barang);
                break;
            case 4:
                hapus_barang(&gudang, &jumlah_barang);
                break;
            case 5:
                undo_hapus(&gudang, &jumlah_barang);
                break;
            case 6:
                terima_barang_baru();
                break;
            case 7:
                proses_barang_baru(&gudang, &jumlah_barang);
                break;
            case 8:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 8);

    return 0;
}
