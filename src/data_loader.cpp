#include "../include/data_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
vector<Element> loadElementsFromCSV(const string& filename) {
    vector<Element> elements;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return elements;
    }

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, simbol, nama;
        getline(ss, idStr, ',');
        getline(ss, simbol, ',');
        getline(ss, nama, ',');

        Element el;
        el.id = stoi(idStr);
        el.simbol = simbol;
        el.nama = nama;
        elements.push_back(el);
    }

    return elements;
}

vector<Compound> loadCompoundsFromCSV(const string& filename) {
    vector<Compound> compounds;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return compounds;
    }

    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (row.size() < 3) continue;

        Compound cmp;

        cmp.nama = row[0];
        cmp.nama.erase(remove(cmp.nama.begin(), cmp.nama.end(), '"'), cmp.nama.end());
        cmp.nama.erase(remove_if(cmp.nama.begin(), cmp.nama.end(), ::isspace), cmp.nama.end());

        for (size_t i = 1; i < row.size() - 1; ++i) {
            string elemen = row[i];
            elemen.erase(remove(elemen.begin(), elemen.end(), '"'), elemen.end());
            elemen.erase(remove_if(elemen.begin(), elemen.end(), ::isspace), elemen.end());
            cmp.komposisi.push_back(elemen);
        }
        string deskripsi = row.back();
        deskripsi.erase(remove(deskripsi.begin(), deskripsi.end(), '"'), deskripsi.end());
        cmp.deskripsi = deskripsi;

        compounds.push_back(cmp);
    }

    return compounds;
}
