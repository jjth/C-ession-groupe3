CC	=	gcc
CFLAGS	=	-g -Wall
RM	=	rm -f

ifdef SYSTEMROOT
	TEST = build/Test.exe
else
	TEST = build/Test
endif

all:	Central Pair Impair

Central:	src/central.c
	$(CC) -o build/Central lib/libini/ini.c src/modules/configparser.c src/modules/colors.c src/modules/readLines.c src/modules/rulesParser.c src/modules/readFile.c src/central.c $(CFLAGS)

Pair:		src/pair.c
	$(CC) -c src/modules/dataStructure.c -o src/modules/dataStructure.o
	$(CC) -c src/pair.c -o src/pair.o
	$(CC) src/pair.o src/modules/dataStructure.o -o build/Pair $(CFLAGS)

Impair:		src/impair.c
	$(CC) -o build/Impair src/impair.c $(CFLAGS)

test:
	@$(CC) -o build/Test lib/libini/ini.c src/modules/configparser.c src/modules/colors.c tests/config.c tests/colors.c tests/main.c $(CFLAGS)
	@$(RM) config.ini
	@$(TEST)
	@$(RM) config.ini

clean:
	$(RM) build/Central
	$(RM) build/Pair
	$(RM) build/Impair
	$(RM) build/Test
	$(RM) config.ini
