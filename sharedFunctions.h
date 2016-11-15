#ifndef DOCUMENT_SIMILARITY_SHAREDFUNCTIONS_H
#define DOCUMENT_SIMILARITY_SHAREDFUNCTIONS_H

#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, int> kShingleSetMap(vector<string> &doc1, unsigned int k);

#endif
