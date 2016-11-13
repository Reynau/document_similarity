#include "JaccardMinhash.h"

#include <stdlib.h>     /* srand, rand */

using namespace std;

const bool comments = false;
const vector<int> primes = {2, 23, 59, 97, 137, 179, 227, 269, 313, 367, 419, 461, 509, 571, 617, 661, 727, 773,
                            829, 883, 947, 1009, 1051, 1103, 1171, 1129, 1289, 1327, 1427, 1471, 1523, 1579, 1621};

/* Universal Hashing:
 * https://en.wikipedia.org/wiki/Universal_hashing#Hashing_strings
 * */
double hash_f(string str, int p) {
    unsigned long long h = 5381;
    for (unsigned int i = 0; i < str.size(); ++i)
        h = ((h << 5) + h) + str[i]; // (h * 33 + c)
    return h % p;
}

/* Calculates:
 * To calculate hmin(S), you pass every member of S through the hash function h,
 * and find the member that gives the lowest result.
 * */
string calculateMinHash (vector<string> &doc, unsigned int i) {
    double hmin1 = hash_f(doc[0], primes[i]);
    string min1 = doc[0];
    for (unsigned int w = 1; w < doc.size(); ++w) {
        double h = hash_f(doc[w], primes[i]);
        if (hmin1 > h) { min1 = doc[w]; hmin1 = h; }
    }
    return min1;
}

/* Calculates:
 * The member x of a set S with the minimum value of h(x).
 * To calculate hmin(S), you pass every member of S through the hash function h,
 * and find the member that gives the lowest result.
 * */
double MinhashSimilitude(vector<string> &doc1, vector<string> &doc2, unsigned int k) {
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
        string min1 = calculateMinHash(doc1, i);
        if (comments) cout << "FINISHED! hmin word is \"" << min1 << "\"." << endl;
        // 1.3. Calculates hmin for doc2
        if (comments) cout << "Calculating hmin for doc2... ";
        string min2 = calculateMinHash(doc2, i);
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