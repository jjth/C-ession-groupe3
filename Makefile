CC	=	gcc
CFLAGS	=	-g -Wall
RM	=	rm -f
all:	Central Pair Impair

Central:	src/central.c
	$(CC) -o build/Central src/central.c $(CFLAGS)

Pair:		src/pair.c
	$(CC) -c src/modules/dataStructure.c -o src/modules/dataStructure.o
	$(CC) -c src/pair.c -o src/pair.o
	$(CC) src/pair.o src/modules/dataStructure.o -o build/Pair $(CFLAGS)

Impair:		src/impair.c
	$(CC) -o build/Impair src/impair.c $(CFLAGS)

clean:
	$(RM) build/Central
	$(RM) build/Pair
	$(RM) build/Impair

