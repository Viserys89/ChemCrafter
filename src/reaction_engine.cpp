// reaction_engine.cpp
#include "../include/reaction_engine.h"
#include "../data/compounds.h"
#include <algorithm> // for sort

string cekReaksi(vector<string> inputUnsur) {
    // Urutkan input dari user supaya cocok dengan kombinasi senyawa
    sort(inputUnsur.begin(), inputUnsur.end());

    for (int i = 0; i < totalCompounds; ++i) {
        vector<string> kombinasi = compounds[i].kombinasiUnsur;
        sort(kombinasi.begin(), kombinasi.end());

        if (kombinasi == inputUnsur) {
            return compounds[i].namaSenyawa;
        }
    }

    return "Tidak menghasilkan senyawa apapun.";
}
