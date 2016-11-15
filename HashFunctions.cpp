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
unsigned int HashFunctions::integerHash(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
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

//#define A 54059 /* a prime */
//#define B 76963 /* another prime */
//#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
unsigned int HashFunctions::hash_str(string s, int A, int B, int C)
{
   unsigned int h = FIRSTH;
   for (unsigned int i = 0; i < s.size(); ++i)
     h = (h * A) ^ (s[0] * B);
   return h % C; // or return h % C;
}