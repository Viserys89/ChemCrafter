#include "../include/reaction_engine.h"
#include "../include/structs.h"
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;
extern vector<Element> elements;
extern vector<Compound> compounds;

bool validElementSimbol(const string& simbol) {
    for (const auto& e : elements) {
        if (e.simbol == simbol) return true;
    }
    return false;
}

string cekReaksi(const vector<string>& unsur, string& deskripsi) {
    vector<string> input = unsur;
    sort(input.begin(), input.end());

    for (const auto& c : compounds) {
        if (input.size() != c.komposisi.size()) {
            continue;
        }

        vector<string> target = c.komposisi;
        sort(target.begin(), target.end());

        if (input == target) {
            deskripsi = c.deskripsi;
            return c.nama;
        }
    }

    deskripsi = "Reaksi tidak menghasilkan senyawa yang dikenal.";
    return "Tidak diketahui";
}

