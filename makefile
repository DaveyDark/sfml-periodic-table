test: run
	rm bin/*

run: build
	./chem-project

build: game.o main.o table.o popup.o
	g++ bin/game.o bin/popup.o bin/table.o bin/main.o -o chem-project -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp -o bin/main.o

game.o: game.cpp
	g++ -c game.cpp -o bin/game.o

table.o: table.cpp
	g++ -c table.cpp -o bin/table.o

popup.o: popup.cpp
	g++ -c popup.cpp -o bin/popup.o

clean:
	rm bin/*.o chem-project

