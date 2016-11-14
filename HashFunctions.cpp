//
// Created by Xavi on 14/11/2016.
//

#include "HashFunctions.h"


void HashFunctions::loadPrimeNumbers () {
    ifstream File;
    File.open("primes.txt");
    if (File.is_open()) {
        int number;
        while(File >> number)
            this->primeNumbers.push_back(number);
    }
    File.close();
}

HashFunctions::HashFunctions() {
    this->loadPrimeNumbers();
}

const vector<unsigned int> &HashFunctions::getPrimeNumbers() {
    return this->primeNumbers;
}

/*
 * Hashing for numbers, necesari for LSH.
 * @param x Number to hash.
 */
uint64_t HashFunctions::integerHash(uint64_t x) {
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

/*
 * Hashing for strings, necesari for minHash.
 * @param str String to hash.
 * @param p Prime number to use in the hash function.
 */
double HashFunctions::stringHash(string str, unsigned int p) {
    unsigned long long hash = 5381;
    for (unsigned int i = 0; i < str.size(); ++i)
        hash = (((hash << 5) + hash) + str[i]);
    return hash % p;
}