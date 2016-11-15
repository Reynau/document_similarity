#include "LocalitySensitiveHashingV1.h"

using namespace std;

map<string, int> doc1Shingles;
map<string, int> doc2Shingles;

vector<pair<string,unsigned int>> hashSet1; 
vector<pair<string,unsigned int>> hashSet2; 

vector<vector<pair<string,unsigned int>>> hashMatrix1;
vector<vector<pair<string,unsigned int>>> hashMatrix2;

vector<unsigned int> bucketSet1;
vector<unsigned int> bucketSet2;

bool comments = false;

/*
 * Compute the minHash for a set of strings (documento to compare).
 * @param doc Vector of strings to Hash.
 * @param hashSet Set of pairs wiht minHashes and words of the n numHashFunctions.
 */
void LocalitySensitiveHashing::computeMinHashForSet(map<string, int> &docShingles, vector<pair<string,unsigned int>> &hashSet, const vector<unsigned int> &primes){
    hashSet = vector<pair<string,unsigned int>>(this->numHashFunctions, pair<string,unsigned int>("",numeric_limits<unsigned int>::max()));
    
    for (int i = 0; i < numHashFunctions; i++){
        for (auto word: docShingles) {
            double h = this->hashFunctions.stringHash(word.first, primes[i]);
            if (hashSet[i].second > h) { 
                hashSet[i].first = word.first;
                hashSet[i].second = h; 
            }
        }
    }
}

/*
 * Separate the hash sets into a hash matrix [numBands X rowsInBands].
 * @param hashSet Set of pairs wiht minhashes and words to hash again for LSH.
 * @param hashMatrix Hash matrix wiht the minHashes of the hashSet.
 */
void LocalitySensitiveHashing::breakSetIntoBandRows(vector<pair<string,unsigned int>> &hashSet,  vector<vector<pair<string,unsigned int>>> &hashMatrix){
    hashMatrix = vector<vector<pair<string,unsigned int>>>(this->numBands, vector<pair<string,unsigned int>>(this->rowsInBands));
    
    int setIndex = 0;
    for (int band = 0; band < numBands; band++){
        //combine all 5 MH values and then hash get its hashcode
        //need not be sum        
        for (int row = 0; row < rowsInBands; row++){
            hashMatrix[band][row].first = hashSet[setIndex].first;
            hashMatrix[band][row].second = hashSet[setIndex].second;
            setIndex++;
        }
    }
}

/*
 * Compute the minHash for a matrix (LSH)
 * @param hashMatrix Matrix of hashes to Hash.
 * @param bucketSet Set of hashes of the hashMatrix ready to compare.
 */
void LocalitySensitiveHashing::computeMinHashForMatrix(vector<vector<pair<string,unsigned int>>> &hashMatrix, vector<unsigned int> &bucketSet, const vector<unsigned int> &primes){
    bucketSet = vector<unsigned int>(this->numBands,numeric_limits<unsigned int>::max());
    
    for (int i = 0; i < numBands; i++){
        for (auto hash: hashMatrix[i]) {
            double h = this->hashFunctions.stringHash(hash.first, primes[110]);
            if (bucketSet[i] > h) { 
                bucketSet[i] = h;
            }
        }
    }
}

/*
 * Calculate the similitud of two set comparate their components. They accept set of strings o set of integers.
 * The can calculate the similitude of the minHash or LSH.
 * @param a One of the sets to compare.
 * @param b One of the sets to compare.
 */
template <typename T>
double LocalitySensitiveHashing::similitude(vector<T> &a, vector<T> &b){
    double sim = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) sim += 1;
    }
    return (sim / (double)a.size());
}

/*
 * Calculate the similitud of two set using LSH.
 * @param set1 First document to compare.
 * @param set2 Second document to compare.
 * @param k Number of the hash Functions for minHash.
 * @param b Number of bands for LSH in the hashMatrix.
 */
double LocalitySensitiveHashing::LSHSimilitude() {
    vector<unsigned int> primes = this->hashFunctions.getPrimeNumbers();
    
    //SHINGLES
    int k1 = 2;
    if (doc1.size() > 9) k1 = 9;
    if (comments) cout << "Computing Shingles of set1... ";
    doc1Shingles = kShingleSetMap(doc1,k1);
    if (comments) cout << "done" << endl;
    
    int k2 = 2;
    if (doc2.size() > 9) k2 = 9;
    if (comments) cout << "Computing Shingles of set2... ";
    doc2Shingles = kShingleSetMap(doc2,k2);
    if (comments) cout << "done" << endl;
 
    //MINHASHES
    if (comments) cout << "Computing MinHash of set1... ";
    computeMinHashForSet(doc1Shingles, hashSet1, primes);
    if (comments) cout << "done" << endl;
    
    if (comments) cout << "Computing MinHash of set2... ";
    computeMinHashForSet(doc2Shingles, hashSet2, primes);
    if (comments) cout << "done" << endl;
    
    //BREAKING INTO BUCKETS
    if (comments) cout << "Breaking hashSet1 into bands & rows... ";
    breakSetIntoBandRows(hashSet1, hashMatrix1);
    if (comments) cout << "done" << endl;
    
    if (comments) cout << "Breaking hashSet1 into bands & rows... ";
    breakSetIntoBandRows(hashSet2, hashMatrix2);   
    if (comments) cout << "done" << endl;
    
    //MINHASHING BUCKETS
    if (comments) cout << "Computing MinHash of hashMatrix1... ";
    computeMinHashForMatrix(hashMatrix1, bucketSet1, primes);
    if (comments) cout << "done" << endl;
    
    if (comments) cout << "Computing MinHash of hashMatrix2... ";
    computeMinHashForMatrix(hashMatrix2, bucketSet2, primes);
    if (comments) cout << "done" << endl;

    return similitude(bucketSet1, bucketSet2);
}
