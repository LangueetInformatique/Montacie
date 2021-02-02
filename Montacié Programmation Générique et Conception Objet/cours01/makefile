all: boucle factorielle minimum factorielle2 testEtudiant testEperluette 

boucle: boucle.o
	g++ -g boucle.o -o boucle
	
boucle.o: boucle.cpp
	g++ -std=c++0x -g -c -w boucle.cpp

factorielle: factorielle.o
	g++ -g factorielle.o -o factorielle

factorielle.o: factorielle.cpp factorielle.h
	g++ -std=c++0x -g -c -w factorielle.cpp 
	
minimum: minimum.o
	g++ -g minimum.o -o minimum

minimum.o: minimum.cpp minimum.h
	g++ -std=c++0x -g -c -w minimum.cpp 
	
factorielle2: factorielle2.o
	g++ -g factorielle2.o -o factorielle2

factorielle2.o: factorielle2.cpp factorielle2.h
	g++ -std=c++0x -g -c -w factorielle2.cpp 
	
testEperluette: testEperluette.o
	g++ -g testEperluette.o -o testEperluette

testEperluette.o: testEperluette.cpp testEperluette.h
	g++ -std=c++0x -g -c -w testEperluette.cpp 
	
testEtudiant: testEtudiant.o Etudiant.o
	g++ -g testEtudiant.o Etudiant.o -o testEtudiant

testEtudiant.o: testEtudiant.cpp testEtudiant.h Etudiant.h
	g++ -std=c++0x -g -c -w testEtudiant.cpp
	
Etudiant.o: Etudiant.cpp Etudiant.h
	g++ -std=c++0x -g -c -w Etudiant.cpp 

clean: 
	rm -f *.o boucle factorielle minimum factorielle2 testEtudiant testEperluette
	

	
