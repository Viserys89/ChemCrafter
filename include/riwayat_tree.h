// riwayat_tree.h
#ifndef RIWAYAT_TREE_H
#define RIWAYAT_TREE_H

#include <string>
#include <vector>
using namespace std;

struct RiwayatNode {
    string hasil;
    vector<string> bahan;
    vector<RiwayatNode*> children;
};

void tampilkanRiwayatTree(RiwayatNode* node, int level = 0);
void hapusRiwayatTree(RiwayatNode* node);

#endif
