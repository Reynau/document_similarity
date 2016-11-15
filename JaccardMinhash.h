#ifndef JACCARD_MH   // To make sure you don't declare the function more than once by including the header multiple times.
#define JACCARD_MH

#include <iostream>
#include <vector>
#include <set>

#include "HashFunctions.h"

using namespace std;

class JaccardMinhash {
private:
    HashFunctions hashFunctions;
    vector<string> doc1;
    vector<string> doc2;
public:
    JaccardMinhash(HashFunctions &hashFunctions,vector<string> &doc1, vector<string> &doc2) :
        hashFunctions(hashFunctions), doc1(doc1), doc2(doc2) {};

    string calculateMinHash (vector<string> &doc, unsigned int i);
    double MinhashSimilitude(unsigned int k);
};


#endif