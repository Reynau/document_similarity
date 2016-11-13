#ifndef JACCARD_MH   // To make sure you don't declare the function more than once by including the header multiple times.
#define JACCARD_MH

#include <iostream>
#include <vector>

using namespace std;

double hash_f(string str, int p);
string calculateMinHash (vector<string> &doc, unsigned int i);
double MinhashSimilitude(vector<string> &doc1, vector<string> &doc2, unsigned int k);

#endif