// ==== FILE: main.cpp ====
#include <iostream>
#include <vector>
#include <string>
#include "include/structs.h"
#include "include/experiment_list.h"
#include "include/history_list.h"
#include "include/reaction_engine.h"
#include "include/csv_writer.h"
#include "include/data_loader.h"
#include "src/display.cpp"
#include "include/compound_dictionary.h"
#include "include/challenge_mode.h"
#include <cctype>

using namespace std;

vector<Element> elements;
vector<Compound> compounds;
void tampilkanTabelPeriodik() {
    cout << "\n--- TABEL PERIODIK SEDERHANA ---\n";
    for (size_t i = 0; i < elements.size(); ++i) {
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
    cout << "8. Bersihkan Layar\n";
    cout << "9. Kamus Senyawa\n";
    cout << "10. Mode Challenge\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu: ";
}
void clearScreen();
string toUpperCase(string input) {
    for (char &c : input) {
        c = toupper(c);
    }
    return input;
}


int main() {
    elements = loadElementsFromCSV("elements.csv");
    compounds = loadCompoundsFromCSV("compounds.csv");

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
                simbol = toUpperCase(simbol);
                if (validElementSimbol(simbol)) {
                    tambahUnsur(inputUnsur, simbol);
                } else {
                    cout << "[PERINGATAN] Unsur tidak ditemukan dalam tabel periodik!\n";
                }
                break;
            }

            case 3:
                tampilkanUnsur(inputUnsur);
                break;

            case 4: {
                vector<string> unsur = konversiKeVector(inputUnsur);
                string deskripsi;
                string hasil = cekReaksi(unsur, deskripsi);
                cout << "\nHasil Reaksi: " << hasil << endl;
                if (!deskripsi.empty()) cout << "Deskripsi: " << deskripsi << endl;
                tambahRiwayat(headRiwayat, tailRiwayat, hasil);
                hapusSemuaUnsur(inputUnsur);
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

            case 8:
                clearScreen();
                break;
            case 9:{
                auto dict = CompoundDictionary::load("compounds_dictionary.csv");
                CompoundDictionary::displayAll(dict);
                break;
            }
            case 10:
            runChallengeMode();
            break;
            case 0:
                cout << "Menyimpan riwayat ke riwayat.csv...\n";
                simpanRiwayatKeCSV(headRiwayat, "riwayat.csv");
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    hapusSemuaUnsur(inputUnsur);
    hapusRiwayat(headRiwayat, tailRiwayat);

    return 0;
}
