all: all1 all2 

all1: LectureRobuste LectureNonRobuste LectureFTexte EcritureFTexte FormatSortie 

LectureFTexte.o: LectureFTexte.cpp 
	g++ -c -g LectureFTexte.cpp

LectureFTexte: LectureFTexte.o
	g++ -g LectureFTexte.o -o LectureFTexte

EcritureFTexte.o: EcritureFTexte.cpp 
	g++ -c -g EcritureFTexte.cpp

EcritureFTexte: EcritureFTexte.o
	g++ -g EcritureFTexte.o -o EcritureFTexte
	
LectureNonRobuste.o: LectureNonRobuste.cpp 
	g++ -c -g LectureNonRobuste.cpp

LectureNonRobuste: LectureNonRobuste.o
	g++ -g LectureNonRobuste.o -o LectureNonRobuste

LectureRobuste.o: LectureRobuste.cpp 
	g++ -c -g LectureRobuste.cpp

LectureRobuste: LectureRobuste.o
	g++ -g LectureRobuste.o -o LectureRobuste
	
FormatSortie.o: FormatSortie.cpp 
	g++ -c -g FormatSortie.cpp

FormatSortie: FormatSortie.o
	g++ -g FormatSortie.o -o FormatSortie
	
all2: EcritureFBinaire LectureFBinaire ModificationFBinaire

EcritureFBinaire: EcritureFBinaire.o 
	g++ -g EcritureFBinaire.o -o EcritureFBinaire

EcritureFBinaire.o: EcritureFBinaire.cpp
	g++ -g -c EcritureFBinaire.cpp
	
LectureFBinaire: LectureFBinaire.o 
	g++ -g LectureFBinaire.o -o LectureFBinaire

LectureFBinaire.o: LectureFBinaire.cpp 
	g++ -g -c LectureFBinaire.cpp

ModificationFBinaire: ModificationFBinaire.o 
	g++ -g ModificationFBinaire.o -o ModificationFBinaire

ModificationFBinaire.o: ModificationFBinaire.cpp 
	g++ -g -c ModificationFBinaire.cpp
	
clean: 
	-rm -f *.o LectureRobuste LectureNonRobuste LectureFTexte EcritureFTexte FormatSortie EcritureFBinaire LectureFBinaire ModificationFBinaire
	