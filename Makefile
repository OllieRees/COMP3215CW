CC=gcc
FLAGS= -I/usr/include/freetype2 -I/usr/include/libpng16 -g -Wall
LIBS= -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl  -lglut
EXENAME=Scheduler
SRCS=$(wildcard src/*.c) 

build: $(SRCS) $(wildcard src/Graphics/*.c)
	$(CC) $(FLAGS) $^ -o $(EXENAME) $(LIBS)
