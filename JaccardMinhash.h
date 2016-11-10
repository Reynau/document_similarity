#ifndef JACCARD_MH   // To make sure you don't declare the function more than once by including the header multiple times.
#define JACCARD_MH

#include <iostream>
#include <vector>

using namespace std;

unsigned long hash_f(string str, int p);
double MinhashSimilitude(vector<string> &doc1, vector<string> &doc2, unsigned int k);

#endif