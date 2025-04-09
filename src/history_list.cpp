// history_list.cpp
#include "../include/history_list.h"
#include <iostream>
using namespace std;

void tambahRiwayat(HistoryNode*& head, HistoryNode*& tail, const string& hasil) {
    HistoryNode* baru = new HistoryNode{hasil, nullptr, nullptr};
    if (!head) {
        head = tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
}

void tampilkanRiwayat(HistoryNode* head) {
    cout << "\nRiwayat Eksperimen:\n";
    if (!head) {
        cout << "(Belum ada riwayat)\n";
        return;
    }

    int i = 1;
    while (head) {
        cout << i++ << ". " << head->hasil << endl;
        head = head->next;
    }
}

void hapusRiwayat(HistoryNode*& head, HistoryNode*& tail) {
    while (head) {
        HistoryNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}
