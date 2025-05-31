// ==== FILE: riwayat_tree.cpp ====
#include "../include/riwayat_tree.h"
#include <iostream>

/**
 * Menampilkan satu node dan subtree-nya, dengan indentasi sesuai level.
 *
 * Contoh output (misal pohon untuk H2CO3):
 *
 * H2CO3 (dari: CO2 + H2O)
 *   CO2 (dari: C + O + O)
 *   H2O (dari: H + H + O)
 *
 * Level 0: H2CO3
 * Level 1: CO2, H2O
 * Level 2: (jika ada anak di bawah CO2 atau H2O)
 */
void tampilkanRiwayatTree(RiwayatNode* node, int level) {
    if (node == nullptr) return;

    // Cetak indentasi sesuai kedalaman
    for (int i = 0; i < level; ++i) {
        cout << "  "; // dua spasi per level
    }

    // Tampilkan formula hasil dan bahan-bahannya
    cout << node->hasil << " (dari: ";
    for (size_t i = 0; i < node->bahan.size(); ++i) {
        cout << node->bahan[i];
        if (i + 1 < node->bahan.size()) {
            cout << " + ";
        }
    }
    cout << ")" << endl;

    // Rekursif tampilkan anak-anaknya
    for (RiwayatNode* child : node->children) {
        tampilkanRiwayatTree(child, level + 1);
    }
}

/**
 * Menghapus seluruh node di subtree, rekursif.
 * Setelah anak-anak dihapus, baru node itu sendiri di-delete.
 */
void hapusRiwayatTree(RiwayatNode* node) {
    if (node == nullptr) return;

    // Hapus dulu semua anak
    for (RiwayatNode* child : node->children) {
        hapusRiwayatTree(child);
    }

    // Lalu hapus node ini
    delete node;
}
