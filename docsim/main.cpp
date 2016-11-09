#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "JaccardKShingle.h"
#include "JaccardMinihash.h"
#include "LocalitySensitiveHashing.h"
#include <map>

using namespace std;




vector<string> readFileAsArray(string file_name){
    vector<string> vec_doc;

    ifstream loadFile_libro;
    loadFile_libro.open(file_name.c_str());
    string output = "";
    if (loadFile_libro.is_open()) {    //Si existe el archivo lo leemos
        while (!loadFile_libro.eof()) { //Mientras existan palabras
            loadFile_libro >> output;
            cout << output << " "; // <- borrar
            vec_doc.push_back(output);
        }
        cout << endl; // <- borrar
    } else cout << "El libro " << file_name << " no ha podido abrirse." << endl;
    loadFile_libro.close();    //Cerramos el archivo de lectura
    return vec_doc;
}
int main(int argc,
         char **argv) {       //Al programa le entran dos parámetros en argv[1] y argv[2] que son los nombres de los dos archivos a comparar

    if (argc != 3) {
        cout
                << "Usage: main libro1 libro2 \n libro1: nombre del primer archivo a comparar. \n libro2: nombre del segundo archivo a comparar."
                << endl;
        return 1;
    }

    string nombre_libro1 = argv[1];     //Pillamos el nobmre del primer libro
    string nombre_libro2 = argv[2];     //Pillamos el nombre del segundo libro

    vector<string> doc1array = readFileAsArray(nombre_libro1);
    vector<string> doc2array = readFileAsArray(nombre_libro2);


    cout << endl;

    cout << "Jaccard similitude index for documents represented with k-shingle:" << endl;
    cout << KShingleSimilitude(doc1array, doc2array,2) << endl << endl;

    cout << "Jaccard similitude index for documents represented with minhash:" << endl;
    cout << MinihashSimilitude() << endl << endl;

    cout << "Similitude index for documents with Locality-Sensitive Hashing (LSH):" << endl;
    cout << LSHSimilitude() << endl << endl;





    return 0;
}