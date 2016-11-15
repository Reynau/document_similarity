
main: main.cpp HashFunctions.cpp
	 g++ -std=c++11  -o main main.cpp JaccardKShingle.cpp JaccardMinhash.cpp LocalitySensitiveHashingV1.cpp LocalitySensitiveHashingV2.cpp HashFunctions.cpp sharedFunctions.cpp
	
clean:
	rm -f *.o *.exe