#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
using namespace std;

// Struct untuk unsur kimia
struct Element {
    int Nomor;
    string simbol;
    string nama;
};

// Struct untuk senyawa hasil gabungan unsur
struct Compound {
    string namaSenyawa;
    vector<string> kombinasiUnsur; // misalnya {"H", "H", "O"}
};

// Node untuk single linked list (bahan eksperimen user)
struct ExperimentNode {
    string simbolUnsur;
    ExperimentNode* next;
};

// Node untuk double linked list (riwayat eksperimen)
struct HistoryNode {
    string hasil;
    HistoryNode* prev;
    HistoryNode* next;
};

#endif
