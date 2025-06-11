// compound_dictionary.cpp
#include "../include/compound_dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

vector<CompoundInfo> CompoundDictionary::load(const string& csvPath) {
    vector<CompoundInfo> dict;
    ifstream file(csvPath);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << csvPath << "\n";
        return dict;
    }

    string line;
    // Baca header
    getline(file, line);
    // Baca tiap baris
    while (getline(file, line)) {
        stringstream ss(line);
        string formula, name, desc;
        getline(ss, formula, ',');
        getline(ss, name, ',');
        getline(ss, desc, ',');
        if (!formula.empty()) {
            dict.push_back({formula, name, desc});
        }
    }
    file.close();
    return dict;
}

void CompoundDictionary::displayAll(const vector<CompoundInfo>& dict) {
    cout << "\n=== KAMUS SENYAWA ===\n\n";

    int maxRows = 5;
    int total = dict.size();
    int cols = ceil(total / (float)maxRows);

    // Buat array 2D [maxRows][cols]
    vector<vector<string>> table(maxRows, vector<string>(cols, ""));

    // Format setiap item ke bentuk string
    for (int i = 0; i < total; ++i) {
        int col = i / maxRows;
        int row = i % maxRows;
        const auto& item = dict[i];
        ostringstream oss;
        oss << item.formula << " - " << item.name << ": " << item.description;
        table[row][col] = oss.str();
    }

    // Hitung lebar kolom maksimal
    vector<size_t> colWidths(cols, 0);
    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < maxRows; ++r) {
            if (table[r][c].length() > colWidths[c]) {
                colWidths[c] = table[r][c].length();
            }
        }
    }

    // Cetak tabel sejajar per baris
    for (int r = 0; r < maxRows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (!table[r][c].empty()) {
                cout << left << setw(colWidths[c] + 4) << table[r][c];
            }
        }
        cout << "\n";
    }
}