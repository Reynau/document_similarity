//
// Created by arnito on 15/11/16.
//

#ifndef DOCUMENT_SIMILARITY_SHAREDFUNCTIONS_H
#define DOCUMENT_SIMILARITY_SHAREDFUNCTIONS_H
#include <string>
#include <vector>
#include <fstream>
#include <map>

std::map<std::string, int> kShingleSetMap(std::vector<std::string> &doc1, unsigned int k);


#endif //DOCUMENT_SIMILARITY_SHAREDFUNCTIONS_H
