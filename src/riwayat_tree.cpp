// riwayat_tree.cpp
#include "../include/riwayat_tree.h"
#include <iostream>

void tampilkanRiwayatTree(RiwayatNode* node, int level) {
    if (node == nullptr) return;
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }
    cout << node->hasil << " (dari: ";
    for (size_t i = 0; i < node->bahan.size(); ++i) {
        cout << node->bahan[i];
        if (i + 1 < node->bahan.size()) {
            cout << " + ";
        }
    }
    cout << ")" << endl;
    for (RiwayatNode* child : node->children) {
        tampilkanRiwayatTree(child, level + 1);
    }
}

void hapusRiwayatTree(RiwayatNode* node) {
    if (node == nullptr) return;

    // Hapus dulu semua anak
    for (RiwayatNode* child : node->children) {
        hapusRiwayatTree(child);
    }
    delete node;
}
