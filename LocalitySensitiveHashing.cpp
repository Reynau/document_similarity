#include "LocalitySensitiveHashing.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <limits>
//#include "JaccardMinhash.h" // for hash_f function 

using namespace std;

vector<double> hashFunctionsPrimes;
vector<pair<string,unsigned int>> hashSet1; 
vector<pair<string,unsigned int>> hashSet2; 

vector<vector<unsigned int>> hashMatrix1;
vector<vector<unsigned int>> hashMatrix2;

vector<unsigned int> bucketSet1;
vector<unsigned int> bucketSet2;

int numHashFunctions;
int numBands;
int rowsInBands;

bool jaccardIndex_comments = false;
bool MinHash_comments = false;
bool ComputeMinHashForSet_comments = false;
bool similitude_comments = false;
bool comments = true;

/*
 * Hashing for numbers, necesari for LSH.
 * @param x Number to hash.
 */
uint64_t hashFunction(uint64_t x) {
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
double hashFunction(string str, unsigned int p) {
    unsigned long long hash = 5381;
    for (unsigned int i = 0; i < str.size(); ++i)
        hash = (((hash << 5) + hash) + str[i]) % p;
    return hash;
}

/*
 * Check if a number is prime.
 * @param n Number to to check.
 */
bool isPrime(unsigned int n) {
    bool prime = true;
    for(int i = 2; i <= n/2; ++i) if(n%i == 0) return false;
    return prime;
}

/*
 * Generate n numHashFunctions prime numbers to use in hashFunction for strings.
 */
void minHashPrimes() {
    hashFunctionsPrimes  = vector<double>(numHashFunctions);
    int n = 0;
    srand (time(NULL));
    if (MinHash_comments) cout << endl;
    for (double i = 2; (n < numHashFunctions); i++){
        if (isPrime(i)) { 
            hashFunctionsPrimes[n] = i;
            if (MinHash_comments) cout << i << endl;
            n++;
            i += numHashFunctions*4;
        }
    }
    if (MinHash_comments) cout << endl;
}

/*
 * Compute the minHash for a set of strings (documento to compare).
 * @param doc Vector of strings to Hash.
 * @param hashSet Set of pairs wiht minHashes and words of the n numHashFunctions.
 */
void computeMinHashForSet(vector<string> &doc, vector<pair<string,unsigned int>> &hashSet ){
    hashSet = vector<pair<string,unsigned int>>(numHashFunctions, pair<string,unsigned int>(doc[0],numeric_limits<unsigned int>::max()));
    //sort(doc.begin(), doc.end()); //Ordenamos el documento BORRAR "&" SI SE DESCOMENTA ESTO, SI NO SE PASARÁ POR COPIA
    if (ComputeMinHashForSet_comments) cout << endl;
    for (int i = 0; i < numHashFunctions; i++){
        for (string word: doc) {
            double h = hashFunction(word, hashFunctionsPrimes[i]);
            if (hashSet[i].second > h) { 
                hashSet[i].first = word;
                hashSet[i].second = h; 
            }
        }
        if (ComputeMinHashForSet_comments) cout << hashSet[i].first << endl; 
    }
}

/*
 * Separate the hash sets into a hash matrix [numBands X rowsInBands].
 * @param hashSet Set of pairs wiht minhashes and words to hash again for LSH.
 * @param hashMatrix Hash matrix wiht the minHashes of the hashSet.
 */
void breakSetIntoBandRows(vector<pair<string,unsigned int>> &hashSet,  vector<vector<unsigned int>> &hashMatrix){
    hashMatrix = vector<vector<unsigned int>>(numBands, vector<unsigned int>(rowsInBands));
    
    int setIndex = 0;
    for (int band = 0; band < numBands; band++){
        //combine all 5 MH values and then hash get its hashcode
        //need not be sum        
        for (int row = 0; row < rowsInBands; row++){
            hashMatrix[band][row] = hashSet[setIndex].second;
            setIndex++;
        }
    }
}

/*
 * Compute the minHash for a matrix (LSH)
 * @param hashMatrix Matrix of hashes to Hash.
 * @param bucketSet Set of hashes of the hashMatrix ready to compare.
 */
void computeMinHashForMatrix(vector<vector<unsigned int>> &hashMatrix, vector<unsigned int> &bucketSet){
    bucketSet = vector<unsigned int>(rowsInBands,numeric_limits<unsigned int>::max());
    
    if (ComputeMinHashForSet_comments) cout << endl;
    for (int i = 0; i < rowsInBands; i++){
        for (unsigned int hash: hashMatrix[i]) {
            double h = hashFunction(hash);
            if (bucketSet[i] > h) { 
                bucketSet[i] = h;
            }
        }
        if (ComputeMinHashForSet_comments) cout << bucketSet[i] << endl; 
    }
}

/*
 * Calculate the similitud of two set comparate their components. They accept set of strings o set of integers.
 * The can calculate the similitude of the minHash or LSH.
 * @param a One of the sets to compare.
 * @param b One of the sets to compare.
 */
template <typename T>
double similitude(vector<T> &a, vector<T> &b){
    if (similitude_comments) cout << "[doc1, doc2]" << endl;
    double sim = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) sim += 1;
        if (similitude_comments) cout << (a[i] == b[i]) << " " << a[i] << " || " << b[i] << endl;
    }
    if (similitude_comments)  cout << "LSH Similitude finished: " 
            "\n Same words: " << sim <<
            "\n Has Functions:  " << ::numBands << endl;

    if (similitude_comments) cout << (double)sim << " " << a.size() << endl;
    return ((double)sim / (double)a.size());
}

/*
 * Calculate the similitud of two set using LSH.
 * @param doc1 First document to compare.
 * @param doc2 Second document to compare.
 * @param k Number of the hash Functions for minHash.
 * @param b Number of bands for LSH in the hashMatrix.
 */
double LSHSimilitude(vector<string> &doc1, vector<string> &doc2, unsigned int k, unsigned int b) {
    //Partition k hash functions into bands b bands
    ::numHashFunctions = k;
    
    if (comments) cout << "Calculating Min Hash Values... ";
    minHashPrimes(); //Declaramos un vector de hash índices para computar el hash de los documentos
    if (comments) cout << "done" << endl;
    
    if (comments) cout << "Computing MinHash of doc1... ";
    computeMinHashForSet(doc1, hashSet1);
    if (comments) cout << "done" << endl;
    
    if (comments) cout << "Computing MinHash of doc2... ";
    computeMinHashForSet(doc2, hashSet2);
    if (comments) cout << "done" << endl;

    vector<string> v1; for (pair<string,unsigned int> p: hashSet1) v1.push_back(p.first);
    
    vector<string> v2; for (pair<string,unsigned int> p: hashSet2) v2.push_back(p.first);
    
    //cout << similittude (v1, v2) << endl;

    ::numBands = b;
    ::rowsInBands = k/b;
    
    if (comments) cout << "Breaking hashSet1 into bands & rows... ";
    breakSetIntoBandRows(hashSet1, hashMatrix1);
    if (comments) cout << "done" << endl;
    
    if (comments) cout << "Breaking hashSet1 into bands & rows... ";
    breakSetIntoBandRows(hashSet2, hashMatrix2);   
    if (comments) cout << "done" << endl;
    
    
    if (comments) cout << "Computing MinHash of hashMatrix1... ";
    computeMinHashForMatrix(hashMatrix1, bucketSet1);
    if (comments) cout << "done" << endl;
    
    if (comments) cout << "Computing MinHash of hashMatrix2... ";
    computeMinHashForMatrix(hashMatrix2, bucketSet2);
    if (comments) cout << "done" << endl;
    
    cout << "Similitude (minHash): " << similitude(v1, v2) << endl;
    return similitude(bucketSet1, bucketSet2);
}
