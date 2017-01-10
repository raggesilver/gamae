all:
	g++ -g -Wall -pedantic *.cpp -o GAMAE -lSDL2 -lSDL2_image -lSDL2_ttf
	./GAMAE
