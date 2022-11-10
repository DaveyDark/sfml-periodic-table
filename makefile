test: run
	rm bin/*

run: build
	export LD_LIBRARY_PATH=lib/ && ./chem-project

build: game.o main.o table.o popup.o
	g++ bin/game.o bin/popup.o bin/table.o bin/main.o -o chem-project -L./lib/ -I./include/ -lsfml-graphics -lsfml-window -lsfml-system

main.o: src/main.cpp bin
	g++ -c src/main.cpp -o bin/main.o -I./include

game.o: src/game.cpp bin
	g++ -c src/game.cpp -o bin/game.o -I./include

table.o: src/table.cpp bin
	g++ -c src/table.cpp -o bin/table.o -I./include

popup.o: src/popup.cpp bin
	g++ -c src/popup.cpp -o bin/popup.o -I./include

bin:
	mkdir -p bin/

clean:
	rm bin/*.o chem-project

