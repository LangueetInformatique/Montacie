all: testMinimum testTableauDyn testMaximumTableauIdentite Point testTableauDyn2Chat testSofstream testTableauDynQ

testMinimum: testMinimum.o 
	g++ -std=c++0x -g testMinimum.o -o testMinimum
	
testMinimum.o: testMinimum.cpp Minimum.h
	g++ -std=c++0x -c -g testMinimum.cpp
	
Point: Point.cpp
	g++ -std=c++0x -g Point.cpp -o Point

testTableauDyn: testTableauDyn.o ../cours01/Etudiant.o
	g++ -std=c++0x -g testTableauDyn.o ../cours01/Etudiant.o ../cours03/Identite.o -o testTableauDyn

testTableauDyn.o: testTableauDyn.cpp TableauDyn.h
	g++ -std=c++0x -c -g testTableauDyn.cpp
	
testMaximumTableauIdentite: testMaximumTableauIdentite.o
	g++ -std=c++0x -g testMaximumTableauIdentite.o ../cours03/Identite.o -o testMaximumTableauIdentite
	
testTableauDyn2Chat: testTableauDyn2Chat.cpp ../cours03/Chat.o ../cours03/Felin.o ../cours03/Animal.o
	g++ -std=c++0x -g testTableauDyn2Chat.cpp ../cours03/Chat.o ../cours03/Felin.o ../cours03/Animal.o -o testTableauDyn2Chat
	
testSofstream : testSofstream.cpp ../cours03/Animal.o
	g++ -std=c++0x -g testSofstream.cpp ../cours03/Animal.o -o testSofstream
	
testTableauDynQ : testTableauDynQ.cpp 
	g++ -std=c++0x -g testTableauDynQ.cpp ../tp01/date.o ../cours01/Etudiant.o -o testTableauDyn2

testMaximumTableauIdentite.o: testMaximumTableauIdentite.cpp MaximumTableau.h compareTo.h 
	g++ -std=c++0x -w -g -c testMaximumTableauIdentite.cpp

clean: 
	rm -f *.o testMinimum testTableauDyn testMaximumTableauIdentite Point testTableauDyn2Chat testSofstream testTableauDynQ
	