#include "../include/reaction_engine.h"
#include "../data/compounds.h"
#include <algorithm>

string cekReaksi(vector<string> inputUnsur, string& deskripsi) {
    sort(inputUnsur.begin(), inputUnsur.end());

    for (int i = 0; i < totalCompounds; ++i) {
        vector<string> kombinasi = compounds[i].kombinasiUnsur;
        sort(kombinasi.begin(), kombinasi.end());

        if (kombinasi == inputUnsur) {
            deskripsi = compounds[i].deskripsi;
            return compounds[i].namaSenyawa;
        }
    }

    deskripsi = "";
    return "Tidak menghasilkan senyawa apapun.";
}