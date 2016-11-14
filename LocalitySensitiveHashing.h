#ifndef SENSITIVE_HASHING   // To make sure you don't declare the function more than once by including the header multiple times.
#define SENSITIVE_HASHING

#include <string>
#include <vector>

using namespace std;

double LSHSimilitude(vector<string> &doc1, vector<string> &doc2, unsigned int k, unsigned int b);

#endif