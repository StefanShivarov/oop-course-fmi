#include <iostream>
#include <fstream>

const short MAX_PAIRS_AMOUNT = 25;

struct Pair {
	double a;
	double b;
};

struct Relation {

	Pair pairs[MAX_PAIRS_AMOUNT];
	size_t pairsAmount = 0;
};

void initPair(Pair& pair) {
	std::cin >> pair.a >> pair.b;
}

void readPairFromFile(std::ifstream& ifs, Pair& pair) {
	ifs >> pair.a >> pair.b;
}

void writePairToFile(std::ofstream& ofs, const Pair& pair) {
	ofs << pair.a << pair.b;
}

void addPairToRelation(Relation& relation, const Pair& pair) {
	if (relation.pairsAmount >= MAX_PAIRS_AMOUNT) {
		std::cout << "Can't add more pairs!" << std::endl;
		return;
	}
	relation.pairs[relation.pairsAmount++] = pair;
}

void readRelationFromFile(const char* fileName, Relation& relation) {

	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return;
	}

	ifs >> relation.pairsAmount;
	for (int i = 0; i < relation.pairsAmount; i++) {
		readPairFromFile(ifs, relation.pairs[i]);
	}

	ifs.close();
}

void writeRelationToFile(const char* fileName, const Relation& relation) {

	std::ofstream ofs(fileName);
	if (!ofs.is_open()) {
		return;
	}

	ofs << relation.pairsAmount;
	for (int i = 0; i < relation.pairsAmount; i++) {
		writePairToFile(ofs, relation.pairs[i]);
	}
	ofs.close();
}



int main() {

	Pair p1, p2;
	initPair(p1);
	initPair(p2);

	Relation rel;
	addPairToRelation(rel, p1);
	addPairToRelation(rel, p2);

	writeRelationToFile("relations.txt", rel);
}