LIB=-Wall
CCPP=g++

all:
	assignment1

assignment1:
	make clean
	$(CCPP) -o assignment1 assignment1.cpp $(LIB)

clean:
	rm -f assignment1
