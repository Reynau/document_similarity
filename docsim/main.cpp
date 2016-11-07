#include <fstream>
#include <iostream>
#include <string>
#include "JaccardKShingle.h"
#include "JaccardMinihash.h"
#include "LocalitySensitiveHashing.h"

using namespace std;

int main(int argc, char** argv) {       //Al programa le entran dos parámetros en argv[1] y argv[2] que son los nombres de los dos archivos a comparar
    string nombre_libro1 = argv[1];     //Pillamos el nobmre del primer libro
    string nombre_libro2 = argv[2];     //Pillamos el nombre del segundo libro
    
    string output = ""; //string que usaremos apra ir guardando las palabras
    
    ifstream loadFile_libro1;   //Archivo de entrada del primer libro
    loadFile_libro1.open(nombre_libro1.c_str()); //Cargamos un archivo de entrada con el nombre assignado (hace falta covnersion de string a char)
    output = "";
    if (loadFile_libro1.is_open()) {    //Si existe un archuivo llamado como el primer libro lo leemos
        while (!loadFile_libro1.eof()) { //Mientras existan palabras
            loadFile_libro1 >> output;
            cout << output << " "; // <- borrar
            //AQUI HABRIA QUE GUARDAR LAS PALABRAS EN UN HASH MAP
        }
        cout << endl; // <- borrar
    } else cout << "El libro " << nombre_libro1 <<" no ha podido abrirse." << endl;
    loadFile_libro1.close();    //Cerramos el archivo de lectura
    
    //Repetimos para el segundo libro
    ifstream loadFile_libro2;
    loadFile_libro2.open(nombre_libro2.c_str());
    output = "";
    if (loadFile_libro2.is_open()) {
        while (!loadFile_libro2.eof()) {
            loadFile_libro2 >> output;
            cout << output << " "; // <- borrar
            //AQUI HABRIA QUE GUARDAR LAS PALABRAS EN UN HASH MAP
        }
        cout << endl; // <- borrar
    } else cout << "El libro " << nombre_libro2 <<" no ha podido abrirse." << endl;
    loadFile_libro2.close();
    
    cout << "Jaccard similitude index for documents represented with k-shingle:" << endl;
    cout << KShingleSimilitude() << endl;
    
    cout << "Jaccard similitude index for documents represented with minhash:" << endl;
    cout << MinihashSimilitude() << endl;
    
    cout << "Similitude index for documents with Locality-Sensitive Hashing (LSH):" << endl;
    cout << LSHSimilitude() << endl;
    
    return 0;
}

