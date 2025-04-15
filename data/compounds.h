// compounds.h
#ifndef COMPOUNDS_H
#define COMPOUNDS_H

#include "../include/structs.h"
using namespace std;

// Daftar kombinasi valid unsur yang menghasilkan senyawa
Compound compounds[] = {
    {"Air", {"H", "H", "O"}},
    {"Garam", {"Na", "Cl"}},
    {"Karbon Dioksida", {"C", "O", "O"}},
    {"Asam Sulfat", {"H", "H", "S", "O", "O", "O", "O"}},
    {"Pasir", {"Si", "O", "O"}},
    {"Besi Oksida", {"Fe", "Fe", "O", "O", "O"}},
    {"Kalsium Nitrat", {"Ca", "N", "O", "O", "O"}},
    {"Asam Nitrat", {"H", "N", "O", "O", "O"}},
    {"Obsidian", {"Si", "O", "O", "Fe"}}
};

const int totalCompounds = sizeof(compounds) / sizeof(compounds[0]);

#endif
