all: forkin.o
	gcc -o forkin forkin.o

forkin.o: forkin.c 
	gcc -c forkin.c
	
run: 
	./forkin
clean:
	rm *.o