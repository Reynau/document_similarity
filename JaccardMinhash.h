#ifndef JACCARD_MH   // To make sure you don't declare the function more than once by including the header multiple times.
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
    double MinhashSimilitude(unsigned int k);
};


#endif