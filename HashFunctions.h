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
    const vector<unsigned int> getPrimeNumbers();
    unsigned  int integerHash(unsigned int x);
    double stringHash(string str, unsigned int p);
    unsigned int hash_str(string s, int A, int B, int C);
    unsigned long HashVector(const vector<unsigned int>& v);

};

#endif //DOCUMENT_SIMILARITY_HASHFUNCTIONS_H
