#ifndef RIWAYAT_TREE_H
#define RIWAYAT_TREE_H

#include <string>
#include <vector>
using namespace std;

/**
 * Struct RiwayatNode
 * - hasil   : formula senyawa yang dihasilkan (misal "CO2", "H2O", "H2CO3", dst.)
 * - bahan   : daftar formula senyawa/unsur yang digabung untuk menghasilkan "hasil"
 *             (misal {"C","O","O"} untuk CO2; atau {"CO2","H2O"} untuk H2CO3)
 * - children: pointer ke anak-anak node ini (anak = senyawa/unsur yang menjadi bahan)
 *
 * Dengan struktur ini, setiap kali user membuat senyawa baru ATAU menggabungkan dua senyawa,
 * akan tercipta satu RiwayatNode. Jika menggabungkan, node hasilnya akan memiliki 2 anak
 * (atau lebih, jika memperluas menjadi multigabungan).
 */
struct RiwayatNode {
    string hasil;
    vector<string> bahan;
    vector<RiwayatNode*> children;
};

/**
 * Fungsi untuk menampilkan riwayat bergerak dari node ROOT ke anaknya.
 * Ditampilkan dengan indentasi, agar terlihat struktur bercabang.
 *
 * @param node  Pointer ke node awal (root) pohon riwayat.
 * @param level Level kedalaman (paling awal dipanggil dengan level = 0).
 */
void tampilkanRiwayatTree(RiwayatNode* node, int level = 0);

/**
 * Hapus seluruh node di dalam subtree (rekursif).
 * Memastikan tidak ada memory leak ketika program selesai.
 */
void hapusRiwayatTree(RiwayatNode* node);

#endif // RIWAYAT_TREE_H
