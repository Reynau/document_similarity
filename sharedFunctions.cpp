//
// Created by arnito on 15/11/16.
//

#include "sharedFunctions.h"


std::map<std::string, int> kShingleSetMap(std::vector<std::string> &doc, unsigned int k){
    std::map<std::string, int> shingle_map;
    for(int i=0; i<doc.size()-k; i++){
        std::string s = "";
        for(int j=0; j<k; j++){
            s.append(doc[i+j]);
        }
        shingle_map[s] =1;
    }
    return shingle_map;
}

