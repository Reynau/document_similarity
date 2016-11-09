#include "JaccardMinihash.h"
#include <iostream>

using namespace std;

double MinhashSimilitude(vector<string> &doc1, vector<string> &doc2) {
    unsigned long val = hash('Holi');
    unsigned long val2 = hash('oHil');
    cout << val << " " << val << endl;
    return 0;
}

unsigned long hash(string str)
{
    unsigned long hash = 5381;
    int c;

    for (int i = 0; i < str.size(); ++i) {
        c = str[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}
