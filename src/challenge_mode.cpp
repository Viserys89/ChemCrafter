// challenge_mode.cpp
#include "../include/challenge_mode.h"
#include "../include/data_loader.h"
#include <stack>
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

string buildFormulaFromKomposisi(const vector<string>& komposisi) {
    string result;
    for (const auto& elemen : komposisi) {
        result += elemen;
    }
    return result;
}

static string getUserFormulaFromStack() {
    stack<char> st;
    cout << "Masukkan simbol unsur satu per satu (ketik 0 lalu Enter jika selesai):\n";
    string sym;
    while (cin >> sym && sym != "0") {
        for (char c : sym) {
            st.push(c);
        }
    }
    string formula;
    while (!st.empty()) {
        formula.push_back(st.top());
        st.pop();
    }
    reverse(formula.begin(), formula.end());
    return formula;
}

void runChallengeMode() {
    vector<Compound> comps = loadCompoundsFromCSV("compounds.csv");
    if (comps.empty()) {
        cout << "Data compounds.csv kosong atau gagal dibaca.\n";
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, (int)comps.size() - 1);
    const Compound targetCompound = comps[dist(gen)];
    const string targetFormula = buildFormulaFromKomposisi(targetCompound.komposisi);

    bool done = false;
    while (!done) {
        cout << "\n=== Challenge Mode ===\n";
        cout << "Buatlah senyawa: " << targetCompound.nama << "\n";
        string userFormula = getUserFormulaFromStack();

        if (userFormula == targetFormula) {
            cout << "Selamat, kamu benar!\n";
            done = true;
        } else {
            cout << "Salah, coba ulang lagi.\n";
        }
    }
    cout << "Kembali ke menu utama...\n";
}
