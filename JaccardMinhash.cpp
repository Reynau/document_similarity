#include "JaccardMinhash.h"

#include <stdlib.h>     /* srand, rand */
#include<fstream>

using namespace std;

const bool comments = false;

/* Calculates:
 * To calculate hmin(S), you pass every member of S through the hash function h,
 * and find the member that gives the lowest result.
 * */
string JaccardMinhash::calculateMinHash (vector<string> &doc, unsigned int prime) {
    double hmin1 = this->hashFunctions.stringHash(doc[0], prime);
    string min1 = doc[0];
    for (unsigned int w = 1; w < doc.size(); ++w) {
        double h = this->hashFunctions.stringHash(doc[w], prime);
        if (hmin1 > h) { min1 = doc[w]; hmin1 = h; }
    }
    return min1;
}

/* Calculates:
 * The member x of a set S with the minimum value of h(x).
 * To calculate hmin(S), you pass every member of S through the hash function h,
 * and find the member that gives the lowest result.
 * */
double JaccardMinhash::MinhashSimilitude(unsigned int k) {
    vector<unsigned int> primes = this->hashFunctions.getPrimeNumbers();
    // Pre-evaluation: K needs to be < primes.size()
    if (k >= primes.size()) {
        k = (unsigned int)primes.size();
        cout << "K downsampled to primes vector size (" << primes.size() << ")." << endl;
    }

    unsigned int y = 0;
    // 1. For k hash functions: Calculate hmin for each doc
    for (unsigned int i = 0; i < k; ++i) {
        if (comments) cout << "Working on hash function #" << i << "." << endl;
        // 1.2. Calculates hmin for doc1
        if (comments) cout << "Calculating hmin for doc1... ";
        string min1 = calculateMinHash(this->doc1, primes[i]);
        if (comments) cout << "FINISHED! hmin word is \"" << min1 << "\"." << endl;
        // 1.3. Calculates hmin for doc2
        if (comments) cout << "Calculating hmin for doc2... ";
        string min2 = calculateMinHash(this->doc2, primes[i]);
        if (comments) cout << "FINISHED! hmin word is \"" << min2 << "\"." << endl;
        // 2. Calculate how many hmin coincided --> y
        if (min1 == min2) {
            ++y;
            if (comments) cout << "Hash function " << i << " generated same min \"" << min1 << "\"." << endl;
        }
        if (comments) cout << endl;
    }
    // 3. Return y/k
    return (double)y/(double)k;
}