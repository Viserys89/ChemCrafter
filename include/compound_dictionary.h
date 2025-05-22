#ifndef COMPOUND_DICTIONARY_H
#define COMPOUND_DICTIONARY_H

#include <vector>
#include <string>

struct CompoundInfo {
    std::string formula;
    std::string name;
    std::string description;
};

class CompoundDictionary {
public:
    // Muat file CSV ke vector<CompoundInfo>
    static std::vector<CompoundInfo> load(const std::string& csvPath);

    // Tampilkan semua entri ke stdout
    static void displayAll(const std::vector<CompoundInfo>& dict);
};

#endif // COMPOUND_DICTIONARY_H
