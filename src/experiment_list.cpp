// experiment_list.cpp
#include "../include/experiment_list.h"
#include <iostream>
using namespace std;

void tambahUnsur(ExperimentNode*& head, const string& simbol) {
    ExperimentNode* baru = new ExperimentNode{simbol, nullptr};
    if (!head) {
        head = baru;
    } else {
        ExperimentNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
}

void tampilkanUnsur(ExperimentNode* head) {
    cout << "Unsur yang dimasukkan: ";
    if (!head) {
        cout << "(belum ada)" << endl;
        return;
    }

    while (head) {
        cout << head->simbolUnsur << " ";
        head = head->next;
    }
    cout << endl;
}

void hapusSemuaUnsur(ExperimentNode*& head) {
    while (head) {
        ExperimentNode* temp = head;
        head = head->next;
        delete temp;
    }
}

vector<string> konversiKeVector(ExperimentNode* head) {
    vector<string> result;
    while (head) {
        result.push_back(head->simbolUnsur);
        head = head->next;
    }
    return result;
}
