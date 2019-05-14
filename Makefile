all: antialiasing

antialiasing: antialiasing.o forms.o programa_2.o
	g++ -std=c++14 -o cena antialiasing.o forms.o programa_2.o -lGL -lGLU -lglut `pkg-config --cflags --libs opencv`

programa_2.o: programa_2.cpp
	g++ -std=c++14 -c programa_2.cpp -lGL -lGLU -lglut

antialising.o: antialiasing.cpp
	g++ -std=c++14 -c antialiasing.cpp -lGL -lGLU -lglut

forms.o: forms.cpp
	g++ -std=c++14 -c forms.cpp -lGL -lGLU -lglut

clean:
	-rm -f *.o cena *~ *.png