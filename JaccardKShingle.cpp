#include "JaccardMinhash.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
double KShingleSimilitude(std::vector<string> &doc1,std::vector<string> &doc2, unsigned int k) {
    //Al principio ponemos todos shingles del primer documento en el map.
    map<string, int> union_map;
    double intersection_count = 0;

    for(int i=0; i<doc1.size(); i++){
        string s = "";
        for(int j=0; j<k; j++){
            if(i+j<doc1.size()){
                s.append(doc1[i+j]);
            }
        }
        union_map[s] =-1; //le ponemos el valor de "-1" para poder diferenciarlo de los shingles del segundo documento
    }
    for(int i=0; i<doc2.size(); i++){
        string s = "";
        for(int j=0; j<k; j++){
            if(i+j<doc2.size()){
                s.append(doc2[i+j]);
            }
        }
        std::map<string,int>::iterator it;
        it = union_map.find(s);
        if(it!=union_map.end()){
            //si el elemento ya formaba parte de los shingles del primer documento incrementamos el numero de elementos de interseccion
            if(it->second == -1) {
                it->second = 1;
                ++intersection_count;
            }
        }
        else union_map[s] = 0; //le ponemos el valor de "0" para poder diferenciarlo de los shingles del primer documento

    }
    double union_count = union_map.size();
    return intersection_count/union_count;

}
