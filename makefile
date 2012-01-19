LIB=-Wall
CCPP=g++

assignment1:
	make clean
	$(CCPP) -o assignment1 assignment1.cpp $(LIB)

all:
	assignment1
	
clean:
	rm -f assignment1
