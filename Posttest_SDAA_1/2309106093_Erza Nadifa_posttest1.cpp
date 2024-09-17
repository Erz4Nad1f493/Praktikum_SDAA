#include <iostream>
using namespace std;

int pindahkanPiringan(int jumlah_piringan, char menara_asal, char menara_tujuan, char menara_sementara) {
    if (jumlah_piringan == 1) {
        cout << "Pindahkan piringan dari " << menara_asal << " ke " << menara_tujuan << endl;
        return 1; 
    }

    int langkah_1 = pindahkanPiringan(jumlah_piringan - 1, menara_asal, menara_sementara, menara_tujuan);

    cout << "Pindahkan piringan dari " << menara_asal << " ke " << menara_tujuan << endl;
    int langkah_2 = 1;

    int langkah_3 = pindahkanPiringan(jumlah_piringan - 1, menara_sementara, menara_tujuan, menara_asal);

    return langkah_1 + langkah_2 + langkah_3;
}

int main() {
    int jumlah_piringan = 3; 
    char menara_asal = 'A'; 
    char menara_tujuan = 'C'; 
    char menara_sementara = 'B'; 

    int total_langkah = pindahkanPiringan(jumlah_piringan, menara_asal, menara_tujuan, menara_sementara);

    cout << "Total langkah yang diperlukan: " << total_langkah << endl;

    return 0;
}
