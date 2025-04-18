#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>
#include <vector>
using namespace std;

struct Element {
    int id;
    string simbol;
    string nama;
};

struct Compound {
    string nama;
    vector<string> komposisi;
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