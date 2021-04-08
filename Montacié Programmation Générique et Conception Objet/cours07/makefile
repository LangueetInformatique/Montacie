all: testFoncteurSTL testMap testMultimap testPriorityQueue testSet testMultiset
	
testFoncteurSTL: testFoncteurSTL.o Complexe.o
	g++ -w -g testFoncteurSTL.o Complexe.o -o testFoncteurSTL
	
testFoncteurSTL.o: testFoncteurSTL.cpp
	g++ -c -w -g testFoncteurSTL.cpp
	
Complexe.o: Complexe.cpp Complexe.h
	g++ -c -w -g Complexe.cpp 
	
testMap: testMap.cpp
	g++ -w -g testMap.cpp -o testMap
	
testMultimap: testMultimap.cpp 
	g++ -w -g testMultimap.cpp -o testMultimap
	
testPriorityQueue: testPriorityQueue.o Patient.o
	g++ -w -g testPriorityQueue.o Patient.o -o testPriorityQueue
	
Patient.o: Patient.cpp Patient.h
	g++ -c -w -g Patient.cpp
	
testPriorityQueue.o: testPriorityQueue.cpp Patient.h
	g++ -c -w -g testPriorityQueue.cpp
	
testSet: testSet.o Patient.o
	g++ -w -g testSet.o Patient.o -o testSet 
	
testSet.o: testSet.cpp Patient.h
	g++ -c -w -g testSet.cpp
	
testMultiset: testMultiset.cpp
	g++ -w -g testMultiset.cpp -o testMultiset
	
clean: 
	rm -f *.o *testFoncteurSTL testMap testMultimap testPriorityQueue testSet testMultiset	