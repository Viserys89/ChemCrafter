#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <vector>
#include <string>
#include "structs.h"
using namespace std;

vector<Element> loadElementsFromCSV(const string& filename);
vector<Compound> loadCompoundsFromCSV(const string& filename);

#endif