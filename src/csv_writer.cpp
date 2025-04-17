#include "../include/csv_writer.h"
#include <fstream>

void simpanRiwayatKeCSV(HistoryNode* head, const string& namaFile) {
    ofstream file(namaFile);
    file << "No,Hasil Eksperimen\n";

    int i = 1;
    while (head) {
        file << i++ << "," << head->hasil << "\n";
        head = head->next;
    }
    file.close();
}