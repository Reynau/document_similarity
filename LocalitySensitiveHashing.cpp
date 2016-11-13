#include "LocalitySensitiveHashing.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <limits>
//#include "JaccardMinhash.h" // for hash_f function 

using namespace std;

vector<unsigned int> hashFunctions;
unsigned int numHashFunctions;
unsigned int stages;
unsigned int buckets;

bool MinHash_comments = false;
bool ComputeMinHashForSet_comments = false;
bool LSHSimilitude_comments = true;
bool comments = true;

 /* MinHash is a hashing scheme that tents to produce similar signatures for sets
  * that have a high Jaccard similarity.
  * 
  * The Jaccard similarity between two sets is the relative number of elements
  * these sets have in common: J(A, B) = |A ∩ B| / |A ∪ B| A MinHash signature is
  * a sequence of numbers produced by multiple hash functions hi. It can be shown
  * that the Jaccard similarity between two sets is also the probability that
  * this hash result is the same for the two sets: J(A, B) = Pr[hi(A) = hi(B)].
  * Therefore, MinHash signatures can be used to estimate Jaccard similarity
  * between two sets. Moreover, it can be shown that the expected estimation
  * error is O(1 / sqrt(n)), where n is the size of the signature (the number of
  * hash functions that are used to produce the signature).
  */

//double jaccardIndex(vector<unsigned int> doc1, vector<unsigned int> doc2) {
//
//    vector<unsigned int> words_intersection, words_union;
//    sort(doc1.begin(), doc1.end());
//    sort(doc2.begin(), doc2.end());
//
//    set_intersection(doc1.begin(),doc1.end(),doc2.begin(),doc2.end(),back_inserter(words_intersection));
//    set_union (doc1.begin(),doc1.end(),doc2.begin(),doc2.end(),back_inserter(words_union));
//    
//    if (words_union.empty()) {
//        return 0;
//    }
//    
//    for (unsigned int s : doc1) cout << s << endl << endl;
//    for (unsigned int s : doc2) cout << s << endl;
//
//    return (double) words_intersection.size() / words_union.size();
//}

vector<unsigned int> MinHash() {
    vector<unsigned int> hash_coefs  = vector<unsigned int>(numHashFunctions);
    
    srand (time(NULL));
    for (int i = 0; i < numHashFunctions; i++)
    { 
        hash_coefs [i] = rand()%10000;    
        if (MinHash_comments) cout << hash_coefs [i] << " ";
    }
    if (MinHash_comments) cout << endl;
    return hash_coefs;
}

unsigned int hashFunction(string str, unsigned int p) {
    unsigned long long h = 5381;
    for (unsigned int i = 0; i < str.size(); ++i)
        h = ((h << 5) + h) + str[i]; // (h * 33 + c)
    return h % p;
}

vector<unsigned int> ComputeMinHashForSet(vector<string> doc){
    vector<unsigned int> minHashes = vector<unsigned int>(numHashFunctions, numeric_limits<unsigned int>::max()); //Inicializamos el vector de signatures con el valor máximo de un string
    
    //sort(doc.begin(), doc.end()); //Ordenamos el documento
    if (ComputeMinHashForSet_comments) cout << endl; 
    for (string str: doc){
        for (int h = 0; h < numHashFunctions; h++){
            unsigned int hash = hashFunction(str, hashFunctions[h]);
            minHashes[h] = min(minHashes[h], hash);
            if (ComputeMinHashForSet_comments) cout << "\tHash calculado" << h << " " << minHashes[h];
        }
        if (ComputeMinHashForSet_comments) cout << endl; 
    }
    return minHashes;
}

vector<vector<int>> minHashMatrix;

double LSHSimilitude(vector<string> &doc1, vector<string> &doc2, unsigned int stages, unsigned int buckets, unsigned int n) {
    // signature size n
    ::numHashFunctions = n;
    ::stages = stages;
    ::buckets = buckets;
    if (comments) cout << "Calculating Min Hash Values... ";
    ::hashFunctions = MinHash(); //Declaramos un vector de hash índices para computar el hash del documento
    if (comments) cout << "done" << endl;
    if (comments) cout << "Computing MinHash of doc1... ";
    vector<unsigned int> sig1 = ComputeMinHashForSet(doc1);
    if (comments) cout << "done" << endl;
    if (comments) cout << "Computing MinHash of doc2... ";
    vector<unsigned int> sig2 = ComputeMinHashForSet(doc2);
    if (comments) cout << "done" << endl;
    
    
    
    
    
    double sim = 0;
    for (int i = 0; i < numHashFunctions; i++) {
        if (sig1[i] == sig2[i]) {
            sim += 1;
        }
        if (LSHSimilitude_comments) cout << sig1[i] << " " << sig2[i] << endl;
    }
    if (LSHSimilitude_comments)  cout << "LSH Similitude finaled " << sim << " " << ::numHashFunctions << " " << ((double)sim / (double)::numHashFunctions) << endl;
    return ((double)sim / (double)::numHashFunctions);
}


/* General idea: Generate from the collection of all elements (words in our
 * example) a small list of candidate pairs: pairs of elements whose similarity
 * must be evaluated.*/

/* For words matrices: Hash columns to many buckets, and make elements of the 
 * same bucket candidate pairs.*/

/* Pick a similiarity threshold t, a fraction < 1.*/

/* We want a pair of columns c and d of the words matriz M to be a candidate 
 * pair if and only if their words agree in at least fraction t of the rows.
 * I.e. M(i,c) = M(i,d) for at least fraction t values of i. */

/* Big idea: hash columns of words matrix M several times.*/

/* Arrange that (only) similar columns are likely to hash to the same bucket.*/

/* Candidate pairs are those that hash at least once to the same bucket.*/

/* Divide matriz M into b bands of r rows.*/

/* For each band, hash its portion of each column to a hash table with k buckets.
 * Make k as large as possible.*/

/* Candidate column pairs are those that hash to the same bucket for >= 1 band.*/

/* Tune b and r to catch most similar pairs, but few nonsimilar pairs*/


/* Tune to get almost all pairs with similar signatures, but eliminate most 
 * pairs that do not have similar words. */

/* Check that candidate pairs really do have similar signatures.*/
