#include "JaccardMinhash.h"

#include <stdlib.h>
#include<fstream>

using namespace std;

const bool comments = false;

/* Calculates:
 * To calculate hmin(S), you pass every member of S through the hash function h,
 * and find the member that gives the lowest result.
 * */
string JaccardMinhash::calculateMinHash (vector<string> &set, unsigned int prime) {
    double hmin1 = this->hashFunctions.stringHash(set[0], prime);
    string min1 = set[0];
    for (unsigned int w = 1; w < set.size(); ++w) {
        double h = this->hashFunctions.stringHash(set[w], prime);
        if (hmin1 > h) { min1 = set[w]; hmin1 = h; }
    }
    return min1;
}

/* Calculates:
 * The member x of a set S with the minimum value of h(x).
 * To calculate hmin(S), you pass every member of S through the hash function h,
 * and find the member that gives the lowest result.
 * */
double JaccardMinhash::MinhashSimilitude(unsigned int t) {
    vector<unsigned int> primes = this->hashFunctions.getPrimeNumbers();
    // Pre-evaluation: K needs to be < primes.size()
    if (t >= primes.size()) {
        t = (unsigned int)primes.size();
        cout << "K downsampled to primes vector size (" << primes.size() << ")." << endl;
    }

    unsigned int y = 0;
    // 1. For k hash functions: Calculate hmin for each doc
    for (unsigned int i = 0; i < t; ++i) {
        if (comments) cout << "Working on hash function #" << i << "." << endl;
        // 1.2. Calculates hmin for set1
        if (comments) cout << "Calculating hmin for set1... ";
        string min1 = calculateMinHash(this->set1, primes[i]);
        if (comments) cout << "FINISHED! hmin word is \"" << min1 << "\"." << endl;
        // 1.3. Calculates hmin for set2
        if (comments) cout << "Calculating hmin for set2... ";
        string min2 = calculateMinHash(this->set2, primes[i]);
        if (comments) cout << "FINISHED! hmin word is \"" << min2 << "\"." << endl;
        // 2. Calculate how many hmin coincided --> y
        if (min1 == min2) {
            ++y;
            if (comments) cout << "Hash function " << i << " generated same min \"" << min1 << "\"." << endl;
        }
        if (comments) cout << endl;
    }
    // 3. Return y/k
    return (double)y/(double)t;
}