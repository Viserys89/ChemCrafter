// reaction_engine.cpp
#include "../include/reaction_engine.h"
#include "../include/structs.h"
#include <unordered_map>
#include <map>
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

Compound combineCompounds(const Compound& c1, const Compound& c2) {
    vector<string> newKomposisi = c1.komposisi;
    newKomposisi.insert(newKomposisi.end(), c2.komposisi.begin(), c2.komposisi.end());

    map<string, int> countMap;
    for (const string& elem : newKomposisi) {
        countMap[elem]++;
    }

    vector<pair<string,int>> elems;
    for (const auto& p : countMap) {
        elems.push_back(p);
    }
    sort(elems.begin(), elems.end(), [](const pair<string,int>& a, const pair<string,int>& b) {
        if (a.first == "H" && b.first != "H") return true;
        if (b.first == "H" && a.first != "H") return false;
        if (a.first == "C" && b.first != "C") return true;
        if (b.first == "C" && a.first != "C") return false;
        return a.first < b.first;
    });

    string formula;
    for (const auto& p : elems) {
        formula += p.first;
        if (p.second > 1) {
            formula += to_string(p.second);
        }
    }

    Compound result;
    result.nama = formula;
    result.komposisi = newKomposisi;
    result.deskripsi = "Hasil gabungan " + c1.nama + " dan " + c2.nama;
    return result;
}
Compound createCompound(const vector<string>& komposisi) {
    Compound c;
    c.komposisi = komposisi;
    map<string,int> freq;
    for (auto& e : komposisi) freq[e]++;
    string formula;
    for (auto& p : freq) {
        formula += p.first;
        if (p.second > 1) formula += to_string(p.second);
    }
    c.nama = formula;
    c.deskripsi = "Senyawa hasil dari input unsur.";
    return c;
}
