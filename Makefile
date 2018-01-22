CC	=	gcc
CFLAGS	=	-g -Wall
RM	=	rm -f
all:	Central Pair Impair

Central:	src/central.c
	$(CC) -o build/Central src/central.c $(CFLAGS)

Pair:		src/pair.c
	$(CC) -o build/Pair src/pair.c $(CFLAGS)

Impair:		src/impair.c
	$(CC) -o build/Impair src/impair.c $(CFLAGS)

clean:
	$(RM) build/Central
	$(RM) build/Pair
	$(RM) build/Impair

