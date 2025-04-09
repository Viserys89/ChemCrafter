#include <iostream>
#include <vector>
#include <string>
#include "include/structs.h"
#include "include/experiment_list.h"
#include "include/history_list.h"
#include "include/reaction_engine.h"
#include "data/elements.h"

using namespace std;

void tampilkanTabelPeriodik() {
    cout << "\n--- TABEL PERIODIK SEDERHANA ---\n";
    for (int i = 0; i < totalElements; ++i) {
        cout << elements[i].simbol << " (" << elements[i].nama << ")\t";
        if ((i + 1) % 5 == 0) cout << endl;
    }
    cout << endl;
}

void tampilkanMenu() {
    cout << "\n=== PROGRAM LAB KIMIA VIRTUAL ===\n";
    cout << "1. Tampilkan Tabel Periodik\n";
    cout << "2. Tambahkan Unsur ke Eksperimen\n";
    cout << "3. Lihat Unsur yang Sudah Dimasukkan\n";
    cout << "4. Jalankan Reaksi\n";
    cout << "5. Lihat Riwayat Eksperimen\n";
    cout << "6. Reset Unsur\n";
    cout << "7. Reset Riwayat\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu: ";
}

int main() {
    ExperimentNode* inputUnsur = nullptr;
    HistoryNode* headRiwayat = nullptr;
    HistoryNode* tailRiwayat = nullptr;

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkanTabelPeriodik();
                break;

            case 2: {
                string simbol;
                cout << "Masukkan simbol unsur (misal H, O, Na): ";
                cin >> simbol;
                tambahUnsur(inputUnsur, simbol);
                break;
            }

            case 3:
                tampilkanUnsur(inputUnsur);
                break;

            case 4: {
                vector<string> unsur = konversiKeVector(inputUnsur);
                string hasil = cekReaksi(unsur);
                cout << "\nHasil Reaksi: " << hasil << endl;
                tambahRiwayat(headRiwayat, tailRiwayat, hasil);
                hapusSemuaUnsur(inputUnsur); // reset input setelah reaksi
                break;
            }

            case 5:
                tampilkanRiwayat(headRiwayat);
                break;

            case 6:
                hapusSemuaUnsur(inputUnsur);
                cout << "Input unsur telah di-reset.\n";
                break;

            case 7:
                hapusRiwayat(headRiwayat, tailRiwayat);
                cout << "Riwayat telah dihapus.\n";
                break;

            case 0:
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    // Bersihkan memori
    hapusSemuaUnsur(inputUnsur);
    hapusRiwayat(headRiwayat, tailRiwayat);

    return 0;
}
