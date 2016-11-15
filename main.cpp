#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "JaccardKShingle.h"
#include "JaccardMinhash.h"
#include "LocalitySensitiveHashingV1.h"
#include "LocalitySensitiveHashingV2.h"

using namespace std;

vector<string> readFileAsArray(string file_name){
    string output = "";
    vector<string> vec_doc = vector<string>(); //Vector de strings con las palabras del archivo de entrada

    ifstream loadFile_libro;
    loadFile_libro.open((file_name).c_str());
    if (loadFile_libro.is_open()) {    //Si existe el archivo lo leemos
        while (!loadFile_libro.eof()) { //Mientras existan palabras
            loadFile_libro >> output;
            vec_doc.push_back(output);
        }
        cout << "Archivo " << file_name << " leido correctamente." << endl;
    } else {
        cout << "Archivo " << file_name << " no encontrado o no ha podido abrirse." << endl;
        exit(1);
    }

    loadFile_libro.close();    //Cerramos el archivo de lectura
    return vec_doc;
}

void usage(int argc){
    if (argc != 3 && argc != 1) {
        cout    << "Usage: main libro1 libro2 "
                "\n\tlibro1: nombre del primer documento a comparar."
                "\n\tlibro2: nombre del segundo documento a comparar."
                "\nNOTA: Los archivos deben encontrarse en la carpeta raíz."
                "\n(Si no se nombra ningun documento, el programa seleccionará dos archivos de forma aleatoria dentro de la carpeta 'randomDocs' de la carpeta raíz)"
                << endl;
    exit(1);
    }
}

//Al programa le entran dos parámetros o ninguno. En caso de tener dos, en argv[1] y argv[2] serán la ruta de los dos archivos a comparar
int main(int argc, char **argv) {
    usage(argc);
    
    srand(time(NULL));
    string nombre_libro1 = "./randomDocs/doc"+to_string(rand()%20+1)+".txt";
    string nombre_libro2 = "./randomDocs/doc"+to_string(rand()%20+1)+".txt";
    if (argc == 3) {
        nombre_libro1 = "./"+(string)argv[1];     //Pillamos el nobmre del primer libro
        nombre_libro2 = "./"+(string)argv[2];     //Pillamos el nombre del segundo libro
    }
    
    vector<string> doc1array = readFileAsArray(nombre_libro1);
    vector<string> doc2array = readFileAsArray(nombre_libro2);

    HashFunctions hashFunctions = HashFunctions();
    
    cout << endl;
    cout << "Jaccard similitude index for documents represented with k-shingle:" << endl;
    const clock_t begin_time = clock();
    cout << "Similitud: "<< KShingleSimilitude(doc1array, doc2array,5) << endl;
    cout << "Tiempo ejecución: "<< float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl << endl;

    cout << "Jaccard similitude index for documents represented with minhash:" << endl;
    const clock_t begin_time2 = clock();
    JaccardMinhash jaccardMinhash = JaccardMinhash(hashFunctions, doc1array, doc2array);
    cout << "Similitud: "<< jaccardMinhash.MinhashSimilitude(200) << endl;
    cout << "Tiempo ejecución: "<< float( clock () - begin_time2 ) /  CLOCKS_PER_SEC << endl << endl;
    
    cout << "Similitude index for documents with Locality-Sensitive Hashing (LSH) version 1:" << endl;
    const clock_t begin_time3 = clock();
    LocalitySensitiveHashing localitySensitiveHashing = LocalitySensitiveHashing(hashFunctions, doc1array, doc2array, 200, 100);
    cout << "Similitud: "<< localitySensitiveHashing.LSHSimilitude() << endl;
    cout << "Tiempo ejecución: "<< float( clock () - begin_time3 ) /  CLOCKS_PER_SEC << endl << endl;
    
    cout << "Similitude index for documents with Locality-Sensitive Hashing (LSH) version 2:" << endl;
    const clock_t begin_time4 = clock();
    LSH lsh = LSH(hashFunctions, doc1array, doc2array, 2, 200, 3);
    cout << "Similitud: "<< lsh.generate() << endl;
    cout << "Tiempo ejecución: "<< float( clock () - begin_time4 ) /  CLOCKS_PER_SEC << endl;

    return 0;
}