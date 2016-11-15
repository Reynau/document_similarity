#include "LocalitySensitiveHashingV2.h"
#include "JaccardMinhash.h"

double LSH::generate() {
    divideKShingles(this->doc1);
    divideKShingles(this->doc2);

    vector<unsigned int> mhSignature1 = calculateMinhashSignature(this->doc1);
    vector<unsigned int> mhSignature2 = calculateMinhashSignature(this->doc2);

    vector<vector<unsigned int>> signMat = {mhSignature1, mhSignature2};

    map<unsigned long, pair<bool, bool>> bucketMap = generateBucketMap(signMat);

    return calculateJaccardSimilarity(bucketMap);
}

void LSH::divideKShingles(vector<string> &doc) {
    vector<string> sDoc;
    unsigned long final = doc.size() - this->k;
    for (int i = 0; i < final; i++){
        string s = doc[i];
        for(int j=1; j<k; j++) s.append(doc[i+j]);
    }
    doc = sDoc;
}

vector<unsigned int> LSH::calculateMinhashSignature(vector<string> &doc) {
    vector<unsigned int> primes = this->hashFunctions.getPrimeNumbers();
    vector<unsigned int> minhash = vector<unsigned int>(this->t);
    for (int i = 0; i < this->t; ++i)
        minhash[i] = calculateMinHash(doc, primes[i]);
    return minhash;
}

map<unsigned long, pair<bool, bool>> LSH::generateBucketMap(vector<vector<unsigned int>> signatureMatrix) {
    unsigned int sizeB = this->t / this->b;

    map<unsigned long, pair<bool, bool>> bucketMap;
    // DOC1
    for (int i = 0; i < this->t; ++i) { // Per cada funcio de hash
        vector<unsigned int> bucket = vector<unsigned int>(sizeB);
        for (int j = 0; j < sizeB; ++j) {
            unsigned int pos = i*sizeB + j;
            unsigned int hash = signatureMatrix[0][pos];
            bucket[j] = hash;
        }

        unsigned long hash = this->hashFunctions.HashVector(bucket);    // Generate hash for vector
        pair<bool, bool> mapElement = bucketMap[hash];                  // Get the pair of bools
        mapElement.first = true;                                        // Set a true for that doc
        bucketMap[hash] = mapElement;                                   //Saves changes
    }

    // DOC2
    for (int i = 0; i < this->t; ++i) { // Per cada funcio de hash
        vector<unsigned int> bucket = vector<unsigned int>(sizeB);
        for (int j = 0; j < sizeB; ++j) {
            unsigned int pos = i*sizeB + j;
            unsigned int hash = signatureMatrix[1][pos];
            bucket[j] = hash;
        }

        unsigned long hash = this->hashFunctions.HashVector(bucket);    // Generate hash for vector
        pair<bool, bool> mapElement = bucketMap[hash];                  // Get the pair of bools
        mapElement.second = true;                                       // Set a true for that doc
        bucketMap[hash] = mapElement;                                   //Saves changes
    }
    return bucketMap;
}

double LSH::calculateJaccardSimilarity(map<unsigned long, pair<bool, bool>> &bucketMap) {
    unsigned int intersection = 0;
    unsigned int unionn = 0;

    typedef map<unsigned long, pair<bool, bool>>::iterator it_type;
    for(it_type iterator = bucketMap.begin(); iterator != bucketMap.end(); iterator++) {
        pair<bool, bool> element = iterator->second;
        if(element.first and element.second) ++intersection;
        ++unionn;
    }

    return (double)intersection/(double)unionn;
}

unsigned int LSH::calculateMinHash (vector<string> &set, unsigned int prime) {
    double hmin1 = this->hashFunctions.stringHash(set[0], prime);
    string min1 = set[0];
    for (unsigned int w = 1; w < set.size(); ++w) {
        double h = this->hashFunctions.stringHash(set[w], prime);
        if (hmin1 > h) { min1 = set[w]; hmin1 = h; }
    }
    return hmin1;
}