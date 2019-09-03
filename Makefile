OBJ = main.o
INC = -I "./"
THREAD = -lpthread
LIB = -lGLEW -lglfw -lGL

raytracer: build run

build: $(OBJ)
	g++ $(OBJ) -o raytracer.out $(LIB)
	rm -f $(OBJ)

render:
	./raytracer.out

run: render

debug:
	g++ -g -o raytracer-debug.out main.cpp $(LIB)

main.o:
	g++ -c main.cpp $(INC)

clean:
	rm -f $(OBJ) raytracer
