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

barang* sortedMergeByName(barang* a, barang* b) {
    barang* result = NULL;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    if (a->nama <= b->nama) {
        result = a;
        result->next = sortedMergeByName(a->next, b);
    } else {
        result = b;
        result->next = sortedMergeByName(a, b->next);
    }
    return result;
}

void split(barang* source, barang** front, barang** back) {
    barang* fast;
    barang* slow;
    slow = source;
    fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSort(barang** headRef) {
    barang* head = *headRef;
    barang* a;
    barang* b;

    if ((head == NULL) || (head->next == NULL)) {
        return;
    }

    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = sortedMergeByName(a, b);
}

barang* getTail(barang* cur) {
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

barang* partition(barang* low, barang* high, barang** newLow, barang** newHigh) {
    barang* pivot = high;
    barang* prev = NULL, *cur = low, *tail = pivot;

    while (cur != pivot) {
        if (cur->harga > pivot->harga) {
            if ((*newLow) == NULL) (*newLow) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev) prev->next = cur->next;
            barang* temp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newLow) == NULL) (*newLow) = pivot;
    (*newHigh) = tail;

    return pivot;
}

barang* quickSortRecur(barang* low, barang* high) {
    if (!low || low == high)
        return low;

    barang* newLow = NULL, *newHigh = NULL;

    barang* pivot = partition(low, high, &newLow, &newHigh);

    if (newLow != pivot) {
        barang* temp = newLow;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;

        newLow = quickSortRecur(newLow, temp);

        temp = getTail(newLow);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newHigh);

    return newLow;
}

void quickSort(barang** headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
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
        cout << "9. Sorting Barang (Ascending by Name)\n";
        cout << "10. Sorting Barang (Descending by Price)\n";
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
            case 9:
                mergeSort(&gudang);
                cout << "Barang berhasil diurutkan secara ascending berdasarkan nama.\n";
                break;
            case 10:
                quickSort(&gudang);
                cout << "Barang berhasil diurutkan secara descending berdasarkan harga.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 8);

    return 0;
}
