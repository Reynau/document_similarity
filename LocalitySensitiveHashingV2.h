#ifndef DOCUMENT_SIMILARITY_LSH_H
#define DOCUMENT_SIMILARITY_LSH_H

#include <string>
#include <map>

#include "HashFunctions.h"

class LSH {
private:
    HashFunctions hashFunctions;
    vector<string> doc1;
    vector<string> doc2;

    unsigned int k; // Tamaño single
    unsigned int t; // Numero de hash functions
    unsigned int b; // Numero de bands

    unsigned int calculateMinHash (vector<string> &set, unsigned int prime);
public:
    LSH(HashFunctions &hashFunctions, vector<string> &doc1, vector<string> &doc2,
    unsigned int k, unsigned int t, unsigned int b) :
            hashFunctions(hashFunctions), doc1(doc1), doc2(doc2), k(k), t(t), b(b) {}

    double generate();
    void divideKShingles(vector<string> &doc);
    vector<unsigned int> calculateMinhashSignature(vector<string> &doc);
    map<unsigned long, pair<bool, bool>> generateBucketMap(vector<vector<unsigned int>> signatureMatrix);
    double calculateJaccardSimilarity(map<unsigned long, pair<bool, bool>> &bucketMap);
};

#endif
