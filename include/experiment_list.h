// experiment_list.h
#ifndef EXPERIMENT_LIST_H
#define EXPERIMENT_LIST_H

#include "../include/structs.h"
#include <vector>
#include <string>
using namespace std;

void tambahUnsur(ExperimentNode*& head, const string& simbol);
void tampilkanUnsur(ExperimentNode* head);
void hapusSemuaUnsur(ExperimentNode*& head);
vector<string> konversiKeVector(ExperimentNode* head);

#endif
