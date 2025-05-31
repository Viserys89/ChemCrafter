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

/**
 * Fungsi combineCompounds:
 * - Mengambil c1.komposisi dan c2.komposisi (vector<string> unsur-unsur di dalam masing-masing senyawa).
 * - Menggabungkan semua unsur dari kedua komposisi tersebut.
 * - Menghitung frekuensi tiap unsur, lalu merangkai formula baru memakai aturan:
 *     1) Jika ada H, letakkan H terlebih dahulu.
 *     2) Jika ada C, letakkan C berikutnya.
 *     3) Sisanya diurutkan secara alfabet (A-Z).
 * - Menghasilkan Compound baru: nama = formula baru, komposisi = gabungan vector,
 *   deskripsi = "Hasil gabungan X dan Y".
 */
Compound combineCompounds(const Compound& c1, const Compound& c2) {
    // 1) Gabungkan isi vektor komposisi
    vector<string> newKomposisi = c1.komposisi;
    newKomposisi.insert(newKomposisi.end(), c2.komposisi.begin(), c2.komposisi.end());

    // 2) Hitung frekuensi tiap elemen
    map<string, int> countMap;
    for (const string& elem : newKomposisi) {
        countMap[elem]++;
    }

    // 3) Siapkan vektor elemen agar bisa di-sort menurut aturan Hill-like:
    //    - H dulu (jika ada), lalu C (jika ada), lalu sisanya alfabet.
    vector<pair<string,int>> elems;
    for (const auto& p : countMap) {
        elems.push_back(p); // p.first = nama unsur, p.second = jumlah
    }
    sort(elems.begin(), elems.end(), [](const pair<string,int>& a, const pair<string,int>& b) {
        if (a.first == "H" && b.first != "H") return true;
        if (b.first == "H" && a.first != "H") return false;
        if (a.first == "C" && b.first != "C") return true;
        if (b.first == "C" && a.first != "C") return false;
        return a.first < b.first;
    });

    // 4) Buat string formula baru
    string formula;
    for (const auto& p : elems) {
        formula += p.first;
        if (p.second > 1) {
            formula += to_string(p.second);
        }
    }

    // 5) Bentuk Compound result
    Compound result;
    result.nama = formula;
    result.komposisi = newKomposisi;
    result.deskripsi = "Hasil gabungan " + c1.nama + " dan " + c2.nama;
    return result;
}
Compound createCompound(const vector<string>& komposisi) {
    // Contoh implementasi sederhana:
    Compound c;
    c.komposisi = komposisi;
    // Buat formula: hitung frekuensi tiap unsur → susun C, H, lalu alfabet
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
