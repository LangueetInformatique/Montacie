all: testMaximum testIdentite testChat testOmnivore

testMaximum: testMaximum.cpp 
	g++ -std=c++0x -g testMaximum.cpp -o testMaximum.exe
	
testIdentite: testIdentite.o Identite.o
	g++ -g testIdentite.o Identite.o -o testIdentite.exe

testIdentite.o: testIdentite.cpp Identite.h
	g++ -std=c++0x -c -g testIdentite.cpp

Identite.o: Identite.cpp Identite.h
	g++ -std=c++0x -c -g Identite.cpp
	
testChat: testChat.o Chat.o Felin.o Animal.o
	g++ -g testChat.o Chat.o Felin.o Animal.o -o testChat.exe
	
testChat.o: testChat.cpp Chat.h
	g++ -std=c++0x -c -g testChat.cpp
	
Chat.o: Chat.cpp Chat.h
	g++ -std=c++0x -c -g Chat.cpp
	
Felin.o: Felin.cpp Felin.h
	g++ -std=c++0x -c -g Felin.cpp

Animal.o: Animal.cpp Animal.h
	g++ -std=c++0x -c -g Animal.cpp
	
testOmnivore: testOmnivore.o Omnivore.o Herbivore.o Carnivore.o Animal.o
	g++ -g testOmnivore.o Omnivore.o Herbivore.o Carnivore.o Animal.o -o testOmnivore.exe
	
testOmnivore.o: testOmnivore.cpp Omnivore.h
	g++ -std=c++0x -c -g testOmnivore.cpp

Omnivore.o: Omnivore.cpp Omnivore.h
	g++ -std=c++0x -c -g Omnivore.cpp
	
Herbivore.o: Herbivore.cpp Herbivore.h
	g++ -std=c++0x -c -g Herbivore.cpp
	
Carnivore.o: Carnivore.cpp Carnivore.h
	g++ -std=c++0x -c -g Carnivore.cpp

clean: 
	-rm -f *.o *.exe

	
	