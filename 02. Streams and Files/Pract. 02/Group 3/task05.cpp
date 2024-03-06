#include <iostream>
#include <fstream>

const int MAX_PAIRS_AMOUNT = 25;

struct Pair {
    int first = 0;
    int second = 0;
};

struct Relation {
    Pair pairs[MAX_PAIRS_AMOUNT];
    unsigned pairsAmount = 0;
};

void addPairToRelation(Relation& relation, const Pair& pair) {
    relation.pairs[relation.pairsAmount++] = pair; 
}

void serializePair(std::ostream& os, const Pair& pair) {
    os << pair.first << ' ' << pair.second;
}

void serializeRelation(std::ostream& os, const Relation& relation) {
    os << relation.pairsAmount;
    for (unsigned i = 0; i < relation.pairsAmount; i++) {
        os << std::endl;
        serializePair(os, relation.pairs[i]);
    }
}

Pair deserializePair(std::istream& is) {
    Pair pair;
    is >> pair.first >> pair.second;
    return pair;
}

Relation deserializeRelation(std::istream& is) {
    Relation relation;
    is >> relation.pairsAmount;

    for (unsigned i = 0; i < relation.pairsAmount; i++) {
        relation.pairs[i] = deserializePair(is);
    }

    return relation;
}

void writeRelationToFile(const char* fileName, const Relation& relation) {
    std::ofstream ofs(fileName);
    if (!ofs.is_open()) {
        std::cerr << "There was an error with opening the file.";
        return;
    }

    serializeRelation(ofs, relation);
    ofs.close();
}

void readRelationFromFile(const char* fileName, Relation& relation) {
    std::ifstream ifs(fileName);
    if (!ifs.is_open()) {
        std::cerr << "There was an error with opening the file.";
        return;
    }
    
    relation = deserializeRelation(ifs);
    ifs.close();
}

int main() {
    Relation rel;
    addPairToRelation(rel, { 10, 20 });
    addPairToRelation(rel, { -1, 4 });
    addPairToRelation(rel, { -2, 5 });
    addPairToRelation(rel, { 11, 17 });

    writeRelationToFile("relations.txt", rel);

    Relation deserialized;
    readRelationFromFile("relations.txt", deserialized);

    serializeRelation(std::cout, deserialized);
}
