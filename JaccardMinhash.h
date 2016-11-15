#ifndef JACCARD_MH
#define JACCARD_MH

#include <iostream>
#include <vector>

#include "HashFunctions.h"

using namespace std;

class JaccardMinhash {
private:
    HashFunctions hashFunctions;
    vector<string> set1;
    vector<string> set2;
public:
    JaccardMinhash(HashFunctions &hashFunctions,vector<string> &set1, vector<string> &set2) :
        hashFunctions(hashFunctions), set1(set1), set2(set2) {};

    string calculateMinHash (vector<string> &set, unsigned int i);
    double MinhashSimilitude(unsigned int t);
};

#endif