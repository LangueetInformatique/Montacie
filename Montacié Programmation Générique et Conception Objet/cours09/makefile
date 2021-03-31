all: testRule testEntity testSymbol testConst_Edge testNode2 testNode

testNode: testNode.cpp
	g++ -w -g testNode.cpp -o testNode.exe
	
testNode2: testNode2.cpp
	g++ -w -g testNode2.cpp -o testNode2.exe
	
testConst_Edge: testConst_Edge.cpp
	g++ -w -g testConst_Edge.cpp -o testConst_Edge.exe
	
testSymbol: testSymbol.cpp
	g++ -w -g testSymbol.cpp -o testSymbol.exe
	
testEntity: testEntity.cpp
	g++ -w -g testEntity.cpp -o testEntity.exe
	
testRule: testRule.cpp
	g++ -w -g testRule.cpp  -o testRule.exe

clean: 
	-rm -f *.o *.exe	