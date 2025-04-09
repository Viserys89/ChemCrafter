// history_list.h
#ifndef HISTORY_LIST_H
#define HISTORY_LIST_H

#include "../include/structs.h"
#include <string>
using namespace std;

void tambahRiwayat(HistoryNode*& head, HistoryNode*& tail, const string& hasil);
void tampilkanRiwayat(HistoryNode* head);
void hapusRiwayat(HistoryNode*& head, HistoryNode*& tail);

#endif
