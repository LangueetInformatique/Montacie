all: testFor_each testString testCopyFichier testTriFichier testFind testBinary_Search testRemove_If
	
testFor_each: testFor_each.o Date.o
	g++ -w -g testFor_each.o Date.o -o testFor_each
	
testFor_each.o: testFor_each.cpp
	g++ -c -w -g testFor_each.cpp
	
Date.o: Date.cpp Date.h
	g++ -c -w -g Date.cpp
	
testCopyFichier: testCopyFichier.o Date.o
	g++ -w -g testCopyFichier.o Date.o -o testCopyFichier
	
testCopyFichier.o: testCopyFichier.cpp
	g++ -c -w -g testCopyFichier.cpp 
	
testTriFichier: testTriFichier.o Date.o
	g++ -w -g testTriFichier.o Date.o -o testTriFichier
	
testTriFichier.o: testTriFichier.cpp
	g++ -c -w -g testTriFichier.cpp 
	
testTransform.o: testTransform.cpp
	g++ -c -w -g testTransform.cpp 
	
testTransform: testTransform.o 
	g++ -w -g testTransform.o ../cours07/Complexe.o -o testTransform
	
testFind.o: testFind.cpp
	g++ -c -w -g testFind.cpp 
	
testFind: testFind.o 
	g++ -w -g testFind.o ../cours03/Animal.o -o testFind
	
testBinary_Search.o: testBinary_Search.cpp
	g++ -c -w -g testBinary_Search.cpp 
	
testBinary_Search: testBinary_Search.o 
	g++ -w -g testBinary_Search.o ../cours03/Animal.o -o testBinary_Search
	
testRemove_If: testRemove_If.cpp
	g++ -w -g testRemove_If.cpp -o testRemove_If
	
testString: testString.cpp
	g++ -w -g testString.cpp -o testString
		
clean: 
	rm -f *.o testFor_each testString testCopyFichier testTriFichier testFind testBinary_Search testRemove_If	