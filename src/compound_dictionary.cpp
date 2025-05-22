#include "../include/compound_dictionary.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>

std::vector<CompoundInfo> CompoundDictionary::load(const std::string& csvPath) {
    std::vector<CompoundInfo> dict;
    std::ifstream file(csvPath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << csvPath << "\n";
        return dict;
    }

    std::string line;
    // Baca header
    std::getline(file, line);
    // Baca tiap baris
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string formula, name, desc;
        std::getline(ss, formula, ',');
        std::getline(ss, name, ',');
        std::getline(ss, desc, ',');
        if (!formula.empty()) {
            dict.push_back({formula, name, desc});
        }
    }
    file.close();
    return dict;
}

void CompoundDictionary::displayAll(const std::vector<CompoundInfo>& dict) {
    std::cout << "\n=== KAMUS SENYAWA ===\n\n";

    int maxRows = 5;
    int total = dict.size();
    int cols = std::ceil(total / (float)maxRows);

    // Buat array 2D [maxRows][cols]
    std::vector<std::vector<std::string>> table(maxRows, std::vector<std::string>(cols, ""));

    // Format setiap item ke bentuk string
    for (int i = 0; i < total; ++i) {
        int col = i / maxRows;
        int row = i % maxRows;
        const auto& item = dict[i];
        std::ostringstream oss;
        oss << item.formula << " - " << item.name << ": " << item.description;
        table[row][col] = oss.str();
    }

    // Hitung lebar kolom maksimal
    std::vector<size_t> colWidths(cols, 0);
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
                std::cout << std::left << std::setw(colWidths[c] + 4) << table[r][c];
            }
        }
        std::cout << "\n";
    }
}