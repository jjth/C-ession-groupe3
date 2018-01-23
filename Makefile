CC	=	gcc
CFLAGS	=	-g -Wall
RM	=	rm -f
all:	Central Pair Impair

Central:	src/central.c
	$(CC) -o build/Central src/central.c $(CFLAGS)

Pair:		src/pair.c
	$(CC) -c src/dataStructure.c
	$(CC) -c src/pair.c
	$(CC) src/pair.o src/dataStructure.o -o build/Pair $(CFLAGS)

Impair:		src/impair.c
	$(CC) -o build/Impair src/impair.c $(CFLAGS)

clean:
	$(RM) build/Central
	$(RM) build/Pair
	$(RM) build/Impair

