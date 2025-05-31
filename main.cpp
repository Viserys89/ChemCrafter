// ==== FILE: main.cpp ====

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <functional>
#include <algorithm>

// Header-header lama yang sudah ada
#include "include/structs.h"
#include "include/experiment_list.h"
#include "include/history_list.h"
#include "include/reaction_engine.h"
#include "include/csv_writer.h"
#include "include/data_loader.h"
#include "include/compound_dictionary.h"
#include "include/challenge_mode.h"
#include "src/display.cpp"

// Header baru untuk Riwayat Tree
#include "include/riwayat_tree.h"

using namespace std;

// Variabel global untuk menyimpan tabel periodik dan daftar senyawa dari CSV
vector<Element> elements;
vector<Compound> compounds;

// Daftar Compound yang sudah user hasilkan (baik lewat reaksi maupun gabungan)
vector<Compound> userCompounds;
// Daftar pointer ke akar-akar pohon riwayat (Tree)
vector<RiwayatNode*> roots;

/**
 * Fungsi pembantu untuk mencari RiwayatNode* berdasar nama formulanya.
 * Digunakan saat user memilih 2 senyawa yang ingin digabung.
 *
 * @param rootList Daftar ‘akar’ (roots) pohon— ada kemungkinan lebih dari satu akar
 * @param target   Nama senyawa (formula) yang dicari, misal "CO2" atau "H2O".
 * @return Pointer ke RiwayatNode yang memiliki node->hasil == target.
 *         Jika tidak ketemu, kembalikan nullptr.
 */
RiwayatNode* cariNodeByFormula(const vector<RiwayatNode*>& rootList, const string& target) {
    for (RiwayatNode* root : rootList) {
        if (root == nullptr) continue;
        // Rekursi DFS via lambda
        function<RiwayatNode*(RiwayatNode*)> dfs = [&](RiwayatNode* node) -> RiwayatNode* {
            if (node->hasil == target) return node;
            for (RiwayatNode* child : node->children) {
                RiwayatNode* found = dfs(child);
                if (found != nullptr) return found;
            }
            return nullptr;
        };
        RiwayatNode* hasil = dfs(root);
        if (hasil != nullptr) return hasil;
    }
    return nullptr;
}

// Menampilkan menu utama lama + opsi tree
void tampilkanMenu() {
    cout << "\n=== PROGRAM LAB KIMIA VIRTUAL ===\n";
    cout << "1. Tampilkan Tabel Periodik\n";
    cout << "2. Tambahkan Unsur ke Eksperimen\n";
    cout << "3. Lihat Unsur yang Sudah Dimasukkan\n";
    cout << "4. Jalankan Reaksi\n";
    cout << "5. Lihat Riwayat Eksperimen (Linier)\n";
    cout << "6. Reset Unsur\n";
    cout << "7. Reset Riwayat (Linier)\n";
    cout << "8. Bersihkan Layar\n";
    cout << "9. Kamus Senyawa\n";
    cout << "10. Mode Challenge\n";
    cout << "11. Gabungkan Dua Senyawa (Tree)\n";
    cout << "12. Tampilkan Riwayat Pohon Eksperimen\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu: ";
}

string toUpperCase(string input) {
    for (char &c : input) {
        c = toupper(c);
    }
    return input;
}

void tampilkanTabelPeriodik() {
    cout << "\n--- TABEL PERIODIK SEDERHANA ---\n";
    for (size_t i = 0; i < elements.size(); ++i) {
        cout << elements[i].simbol << " (" << elements[i].nama << ")\t";
        if ((i + 1) % 5 == 0) cout << endl;
    }
    cout << endl;
}

int main() {
    // Muat data unsur dan senyawa dari CSV
    elements = loadElementsFromCSV("elements.csv");
    compounds = loadCompoundsFromCSV("compounds.csv");

    ExperimentNode* inputUnsur = nullptr;            // Linked list input unsur
    HistoryNode* headRiwayat = nullptr;               // Linked list riwayat linier
    HistoryNode* tailRiwayat = nullptr;

    int pilihan;
    do {
        tampilkanMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            // 1) Tampilkan Tabel Periodik
            case 1:
                tampilkanTabelPeriodik();
                break;

            // 2) Tambahkan Unsur ke Eksperimen
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

            // 3) Lihat Unsur yang Sudah Dimasukkan
            case 3:
                tampilkanUnsur(inputUnsur);
                break;

            // 4) Jalankan Reaksi
            case 4: {
                // Konversi linked list inputUnsur ke vector<string>
                vector<string> unsur = konversiKeVector(inputUnsur);
                if (unsur.empty()) {
                    cout << "[PERINGATAN] Belum ada unsur yang dimasukkan!\n";
                    break;
                }
                string deskripsi;
                string namaHasil = cekReaksi(unsur, deskripsi);
                cout << "\nHasil Reaksi: " << namaHasil << endl;
                if (!deskripsi.empty()) cout << "Deskripsi: " << deskripsi << endl;
                tambahRiwayat(headRiwayat, tailRiwayat, namaHasil);
                hapusSemuaUnsur(inputUnsur);

                // Tambahkan ke userCompounds & Tree jika senyawa diketahui
                if (namaHasil != "Tidak diketahui") {
                    // Cari Compound di daftar compounds (dari CSV)
                    Compound found;
                    bool ketemu = false;
                    for (auto& c : compounds) {
                        if (c.nama == namaHasil) {
                            found = c;
                            ketemu = true;
                            break;
                        }
                    }
                    if (ketemu) {
                        userCompounds.push_back(found);
                        // Buat RiwayatNode baru (leaf)
                        RiwayatNode* nodeBaru = new RiwayatNode();
                        nodeBaru->hasil = found.nama;
                        nodeBaru->bahan = unsur; // daftar simbol unsur
                        roots.push_back(nodeBaru);
                        cout << "[INFO] Senyawa \"" << found.nama << "\" ditambahkan ke Riwayat Tree.\n";
                    }
                }
                break;
            }

            // 5) Lihat Riwayat Eksperimen (Linier)
            case 5:
                cout << "\n--- Riwayat Eksperimen (Linier) ---\n";
                tampilkanRiwayat(headRiwayat);
                break;

            // 6) Reset Unsur
            case 6:
                hapusSemuaUnsur(inputUnsur);
                cout << "[INFO] Input unsur telah di-reset.\n";
                break;

            // 7) Reset Riwayat (Linier)
            case 7:
                hapusRiwayat(headRiwayat, tailRiwayat);
                cout << "[INFO] Riwayat linier telah dihapus.\n";
                break;

            // 8) Bersihkan Layar
            case 8:
                clearScreen();
                break;

            // 9) Kamus Senyawa
            case 9: {
                auto dict = CompoundDictionary::load("compounds_dictionary.csv");
                CompoundDictionary::displayAll(dict);
                break;
            }

            // 10) Mode Challenge
            case 10:
                runChallengeMode();
                break;

            // 11) Gabungkan Dua Senyawa (Tree)
            case 11: {
                if (userCompounds.size() < 2) {
                    cout << "[PERINGATAN] Belum cukup senyawa untuk digabung (minimal 2 senyawa).\n";
                    break;
                }
                // Tampilkan daftar senyawa yang telah dibuat user
                cout << "\n--- Daftar Senyawa yang Tersedia ---\n";
                for (size_t i = 0; i < userCompounds.size(); ++i) {
                    cout << "  [" << i << "] " << userCompounds[i].nama << "\n";
                }
                int idx1, idx2;
                cout << "Pilih indeks senyawa pertama: ";
                cin >> idx1;
                cout << "Pilih indeks senyawa kedua: ";
                cin >> idx2;
                // Validasi indeks
                if (idx1 < 0 || idx1 >= (int)userCompounds.size() ||
                    idx2 < 0 || idx2 >= (int)userCompounds.size() ||
                    idx1 == idx2) {
                    cout << "[PERINGATAN] Indeks tidak valid atau sama.\n";
                    break;
                }
                Compound comp1 = userCompounds[idx1];
                Compound comp2 = userCompounds[idx2];
                // Gabung
                Compound gabungan = combineCompounds(comp1, comp2);
                cout << "\nHasil Gabungan: " << gabungan.nama << endl;
                cout << "Deskripsi     : " << gabungan.deskripsi << endl;
                tambahRiwayat(headRiwayat, tailRiwayat, gabungan.nama);
                userCompounds.push_back(gabungan);

                // Atur Tree
                RiwayatNode* nodeGabungan = new RiwayatNode();
                nodeGabungan->hasil = gabungan.nama;
                nodeGabungan->bahan.push_back(comp1.nama);
                nodeGabungan->bahan.push_back(comp2.nama);

                // Cari node asal di roots
                RiwayatNode* node1 = cariNodeByFormula(roots, comp1.nama);
                RiwayatNode* node2 = cariNodeByFormula(roots, comp2.nama);
                if (node1 == nullptr) {
                    node1 = new RiwayatNode();
                    node1->hasil = comp1.nama;
                    node1->bahan = comp1.komposisi; // komposisi unsur
                    roots.push_back(node1);
                }
                if (node2 == nullptr) {
                    node2 = new RiwayatNode();
                    node2->hasil = comp2.nama;
                    node2->bahan = comp2.komposisi;
                    roots.push_back(node2);
                }
                // Tambahkan anak ke nodeGabungan
                nodeGabungan->children.push_back(node1);
                nodeGabungan->children.push_back(node2);
                // Hapus node1 & node2 dari roots
                auto it1 = find(roots.begin(), roots.end(), node1);
                if (it1 != roots.end()) roots.erase(it1);
                auto it2 = find(roots.begin(), roots.end(), node2);
                if (it2 != roots.end()) roots.erase(it2);
                // Tambahkan nodeGabungan sebagai root baru
                roots.push_back(nodeGabungan);

                cout << "[INFO] Senyawa \"" << gabungan.nama << "\" ditambahkan ke Riwayat Tree.\n";
                break;
            }

            // 12) Tampilkan Riwayat Pohon Eksperimen
            case 12:
                if (roots.empty()) {
                    cout << "[INFO] Belum ada riwayat eksperimen di Tree.\n";
                } else {
                    cout << "\n=== Riwayat Pohon Eksperimen ===\n";
                    for (RiwayatNode* root : roots) {
                        tampilkanRiwayatTree(root, 0);
                        cout << "--------------------------------\n";
                    }
                }
                break;

            // 0) Keluar
            case 0:
                cout << "\nMenyimpan riwayat ke riwayat.csv...\n";
                simpanRiwayatKeCSV(headRiwayat, "riwayat.csv");
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;

            default:
                cout << "[PERINGATAN] Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 0);

    // Cleanup linked-list lama
    hapusSemuaUnsur(inputUnsur);
    hapusRiwayat(headRiwayat, tailRiwayat);

    // Cleanup Tree
    for (RiwayatNode* root : roots) {
        hapusRiwayatTree(root);
    }
    roots.clear();

    return 0;
}
