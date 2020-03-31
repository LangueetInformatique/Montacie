all: testFoncteurSTL testMap testMultimap testPriorityQueue testSet testMultiset
	
testFoncteurSTL: testFoncteurSTL.o
	g++ -w -g testFoncteurSTL.o ../Cours\ 03/Complexe.o -o testFoncteurSTL.exe
	
testFoncteurSTL.o: testFoncteurSTL.cpp
	g++ -c -w -g testFoncteurSTL.cpp
	
testMap: testMap.cpp
	g++ -w -g testMap.cpp -o testMap.exe
	
testMultimap: testMultimap.cpp 
	g++ -w -g testMultimap.cpp -o testMultimap.exe
	
testPriorityQueue: testPriorityQueue.o Patient.o
	g++ -w -g testPriorityQueue.o Patient.o -o testPriorityQueue.exe 
	
Patient.o: Patient.cpp Patient.h
	g++ -c -w -g Patient.cpp
	
testPriorityQueue.o: testPriorityQueue.cpp Patient.h
	g++ -c -w -g testPriorityQueue.cpp
	
testSet: testSet.o Patient.o
	g++ -w -g testSet.o Patient.o -o testSet.exe 
	
testSet.o: testSet.cpp Patient.h
	g++ -c -w -g testSet.cpp
	
testMultiset: testMultiset.cpp
	g++ -w -g testMultiset.cpp -o testMultiset.exe
	
clean: 
	-del -f *.o *.exe	