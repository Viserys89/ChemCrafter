#ifndef COMPOUNDS_H
#define COMPOUNDS_H

#include "../include/structs.h"
using namespace std;

Compound compounds[] = {
    {"Air", {"H", "H", "O"}, "Air adalah senyawa kimia yang terdiri dari dua atom hidrogen dan satu atom oksigen (H2O)."},
    {"Garam", {"Na", "Cl"}, "Garam dapur atau natrium klorida (NaCl) biasa digunakan sebagai bumbu masak."},
    {"Karbon Dioksida", {"C", "O", "O"}, "Gas karbon dioksida (CO2) dihasilkan oleh respirasi dan pembakaran karbon."},
    {"Asam Sulfat", {"H", "H", "S", "O", "O", "O", "O"}, "Asam sulfat (H2SO4) adalah cairan sangat korosif dan banyak digunakan di industri kimia."},
    {"Pasir", {"Si", "O", "O"}, "Pasir terutama tersusun dari silikon dioksida (SiO2)."},
    {"Besi Oksida", {"Fe", "Fe", "O", "O", "O"}, "Besi oksida (Fe2O3) adalah senyawa yang biasa ditemukan pada karat besi."},
    {"Kalsium Nitrat", {"Ca", "N", "O", "O", "O"}, "Kalsium nitrat (Ca(NO3)2) digunakan sebagai pupuk dan dalam pendinginan beton."},
    {"Asam Nitrat", {"H", "N", "O", "O", "O"}, "Asam nitrat (HNO3) adalah zat korosif kuat yang digunakan untuk membuat bahan peledak dan pupuk."},
    {"Obsidian", {"Si", "O", "O", "Fe"}, "Obsidian adalah batuan beku vulkanik alami yang terbentuk dari pendinginan lava."}
};

const int totalCompounds = sizeof(compounds) / sizeof(compounds[0]);

#endif