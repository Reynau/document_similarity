#ifndef JACCARD_KS   // To make sure you don't declare the function more than once by including the header multiple times.
#define JACCARD_KS

double KShingleSimilitude(std::vector<std::string> &doc1,std::vector<std::string> &doc2, unsigned int k);

#endif