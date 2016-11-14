//
// Created by Xavi on 14/11/2016.
//

#ifndef DOCUMENT_SIMILARITY_HASHFUNCTIONS_H
#define DOCUMENT_SIMILARITY_HASHFUNCTIONS_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class HashFunctions {

private:
    vector<unsigned int> primeNumbers;

    void loadPrimeNumbers();
public:
    HashFunctions();
    const vector<unsigned int> &getPrimeNumbers();
    uint64_t integerHash(uint64_t x);
    double stringHash(string str, unsigned int p);

};


#endif //DOCUMENT_SIMILARITY_HASHFUNCTIONS_H
