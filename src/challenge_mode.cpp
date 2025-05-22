#include "../include/challenge_mode.h"
#include "../include/data_loader.h"
#include <stack>
#include <iostream>
#include <random>
#include <algorithm>

// Membuat ulang formula string dari komposisi vektor
std::string buildFormulaFromKomposisi(const std::vector<std::string>& komposisi) {
    std::string result;
    for (const auto& elemen : komposisi) {
        result += elemen;
    }
    return result;
}

// Baca input user via stack dan bangun ulang formula
static std::string getUserFormulaFromStack() {
    std::stack<char> st;
    std::cout << "Masukkan simbol unsur satu per satu (ketik 0 lalu Enter jika selesai):\n";
    std::string sym;
    while (std::cin >> sym && sym != "0") {
        for (char c : sym) {
            st.push(c);
        }
    }
    std::string formula;
    while (!st.empty()) {
        formula.push_back(st.top());
        st.pop();
    }
    std::reverse(formula.begin(), formula.end());
    return formula;
}

void runChallengeMode() {
    std::vector<Compound> comps = loadCompoundsFromCSV("compounds.csv");
    if (comps.empty()) {
        std::cout << "Data compounds.csv kosong atau gagal dibaca.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, (int)comps.size() - 1);
    const Compound targetCompound = comps[dist(gen)];
    const std::string targetFormula = buildFormulaFromKomposisi(targetCompound.komposisi);

    bool done = false;
    while (!done) {
        std::cout << "\n=== Challenge Mode ===\n";
        std::cout << "Buatlah senyawa: " << targetCompound.nama << "\n";
        std::string userFormula = getUserFormulaFromStack();

        if (userFormula == targetFormula) {
            std::cout << "Selamat, kamu benar!\n";
            done = true;
        } else {
            std::cout << "Salah, coba ulang lagi.\n";
        }
    }
    std::cout << "Kembali ke menu utama...\n";
}
