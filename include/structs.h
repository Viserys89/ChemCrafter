#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
using namespace std;

struct Element {
    int nomorAtom;
    string simbol;
    string nama;
};

struct Compound {
    string namaSenyawa;
    vector<string> kombinasiUnsur;
    string deskripsi;
};

struct ExperimentNode {
    string simbolUnsur;
    ExperimentNode* next;
};

struct HistoryNode {
    string hasil;
    HistoryNode* prev;
    HistoryNode* next;
};

#endif