all: testFor_each testString testCopyFichier testTriFichier testFind testBinary_Search testRemove_If
	
testFor_each: testFor_each.o
	g++ -w -g testFor_each.o ../tp03/Date.o -o testFor_each.exe
	
testFor_each.o: testFor_each.cpp
	g++ -c -w -g testFor_each.cpp
	
testCopyFichier: testCopyFichier.o 
	g++ -w -g testCopyFichier.o ../tp03/Date.o -o testCopyFichier.exe
	
testCopyFichier.o: testCopyFichier.cpp
	g++ -c -w -g testCopyFichier.cpp 
	
testTriFichier: testTriFichier.o 
	g++ -w -g testTriFichier.o ../tp03/Date.o -o testTriFichier.exe
	
testTriFichier.o: testTriFichier.cpp
	g++ -c -w -g testTriFichier.cpp 
	
testTransform.o: testTransform.cpp
	g++ -c -w -g testTransform.cpp 
	
testTransform: testTransform.o 
	g++ -w -g testTransform.o ../tp03/Complexe.o -o testTransform.exe
	
testFind.o: testFind.cpp
	g++ -c -w -g testFind.cpp 
	
testFind: testFind.o 
	g++ -w -g testFind.o ../Cours\ 03/Animal.o -o testFind.exe
	
testBinary_Search.o: testBinary_Search.cpp
	g++ -c -w -g testBinary_Search.cpp 
	
testBinary_Search: testBinary_Search.o 
	g++ -w -g testBinary_Search.o ../Cours\ 03/Animal.o -o testBinary_Search.exe
	
testRemove_If: testRemove_If.cpp
	g++ -w -g testRemove_If.cpp -o testRemove_If.exe
	
testString: testString.cpp
	g++ -w -g testString.cpp -o testString.exe
		
clean: 
	-del -f *.o *.exe	