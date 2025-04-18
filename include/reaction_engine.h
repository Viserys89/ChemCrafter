#ifndef REACTION_ENGINE_H
#define REACTION_ENGINE_H

#include <vector>
#include <string>
#include "structs.h"
using namespace std;

bool validElementSimbol(const string& simbol);
string cekReaksi(const vector<string>& unsur, string& deskripsi);

#endif
