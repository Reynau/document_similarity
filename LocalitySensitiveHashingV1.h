#ifndef SENSITIVE_HASHING
#define SENSITIVE_HASHING

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>

#include "sharedFunctions.h"
#include "HashFunctions.h"

using namespace std;

class LocalitySensitiveHashing {
private:
    HashFunctions hashFunctions;
    vector<string> &doc1;
    vector<string> &doc2;

    unsigned int numHashFunctions;
    unsigned int numBands;
    unsigned int rowsInBands;

public:
    LocalitySensitiveHashing(HashFunctions &hashFunctions, vector<string> &doc1, vector<string> &doc2,
                             unsigned int k, unsigned int b) :
        hashFunctions(hashFunctions), doc1(doc1), doc2(doc2), numHashFunctions(k), numBands(b), rowsInBands (k/b) {};

    double LSHSimilitude();
    void computeMinHashForSet(map<string, int> &docShingles, vector<pair<string,unsigned int>> &hashSet, const vector<unsigned int> &primes);
    void breakSetIntoBandRows(vector<pair<string,unsigned int>> &hashSet,  vector<vector<pair<string,unsigned int>>> &hashMatrix);
    void computeMinHashForMatrix(vector<vector<pair<string,unsigned int>>> &hashMatrix, vector<unsigned int> &bucketSet, const vector<unsigned int> &primes);
    template <typename T> double similitude(vector<T> &a, vector<T> &b);
};

#endif