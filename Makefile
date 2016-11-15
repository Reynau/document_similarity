
main: main.cpp HashFunctions.cpp
	 g++ -std=c++11  -o main main.cpp HashFunctions.h JaccardKShingle.h JaccardMinhash.h LocalitySensitiveHashingV1.h LocalitySensitiveHashingV2.h sharedFunctions.h
	
clean:
	rm -f *.o *.exe