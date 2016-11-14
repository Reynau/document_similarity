#ifndef SENSITIVE_HASHING   // To make sure you don't declare the function more than once by including the header multiple times.
#define SENSITIVE_HASHING

#include <string>
#include <vector>

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
    void computeMinHashForSet(vector<string> &doc, vector<pair<string,unsigned int>> &hashSet, const vector<unsigned int> &primes);
    void breakSetIntoBandRows(vector<pair<string,unsigned int>> &hashSet,  vector<vector<unsigned int>> &hashMatrix);
    void computeMinHashForMatrix(vector<vector<unsigned int>> &hashMatrix, vector<unsigned int> &bucketSet);
    template <typename T> double similitude(vector<T> &a, vector<T> &b);
};



#endif