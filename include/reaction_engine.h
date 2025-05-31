#ifndef REACTION_ENGINE_H
#define REACTION_ENGINE_H

#include <vector>
#include <string>
#include "structs.h"
using namespace std;

bool validElementSimbol(const string& simbol);
string cekReaksi(const vector<string>& unsur, string& deskripsi);
Compound createCompound(const vector<string>& komposisi);
Compound combineCompounds(const Compound& c1, const Compound& c2);

#endif
