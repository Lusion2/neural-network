# generic
SRC = src/
LIB = -Llib/
INC = -Iinclude/
libs = -lglfw3dll

UTIL = -Wextra -Wall

FILES = $(SRC)main.c $(SRC)graphics/graphics.c $(SRC)glad/glad.c

TARGET = network

all: main

main:
	gcc $(LIB) $(INC) $(UTIL) -o $(TARGET) $(FILES) $(libs)