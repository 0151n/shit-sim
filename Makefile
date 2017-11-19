all: main.o particle.o
	g++ main.o particle.o -o shit_sim -g -lsfml-graphics -lsfml-window -lsfml-system
	rm *.o
main.o:
	g++ -c main.cpp -o main.o -g -I /home/oisin/SFML-2.2/include
particle.o:
	g++ -c particle.cpp -o particle.o -g -I /home/oisin/SFML-2.2/include
clean:
	rm *.o
