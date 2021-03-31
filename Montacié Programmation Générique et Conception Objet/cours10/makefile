all: testConstruction testSearch testLCSS
		
testConstruction: testConstruction.o
	g++ -w -g testConstruction.o  suds.a -o testConstruction.exe

testSearch: testSearch.o
	g++ -w -g testSearch.o  suds.a -o testSearch.exe
		
testLCSS: testLCSS.o
	g++ -w -g testLCSS.o  suds.a -o testLCSS.exe

testConstruction.o: testConstruction.cpp
	g++ -c -w -g testConstruction.cpp
	
testLCSS.o: testLCSS.cpp
	g++ -c -w -g testLCSS.cpp
	
testLCSS.o: testLCSS.cpp
	g++ -c -w -g testLCSS.cpp
					
clean: 
	-rm -f *.o *.exe