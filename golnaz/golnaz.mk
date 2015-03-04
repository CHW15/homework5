CC = g++

CFLAGS = -Wall

all: golnaz

golnaz: golnaz.cpp 
	${CC} ${CFLAGS} golnaz.cpp -o golnaz

clean:
	rm -rf golnaz