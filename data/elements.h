// elements.h
#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "../include/structs.h"
using namespace std;

// Daftar unsur kimia
Element elements[] = {
    {1, "H", "Hidrogen"},
    {2, "O", "Oksigen"},
    {3, "C", "Karbon"},
    {4, "Na", "Natrium"},
    {5, "Cl", "Klor"},
    {6, "Si", "Silikon"},
    {7, "Fe", "Besi"},
    {8, "N", "Nitrogen"},
    {9, "S", "Sulfur"},
    {10, "Ca", "Kalsium"}
};

const int totalElements = sizeof(elements) / sizeof(elements[0]);

#endif
