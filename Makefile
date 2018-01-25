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
	$(CC) -o build/Central lib/libini/ini.c src/modules/configparser.c src/modules/dataStructure.c src/modules/colors.c src/globals.c src/modules/client.c src/modules/readLines.c src/modules/rulesParser.c src/modules/readFile.c src/modules/scanf.c src/central.c $(CFLAGS)

Pair:		src/pair.c
	$(CC) -o build/pair/Pair lib/libini/ini.c src/modules/configparser.c src/modules/dataStructure.c src/modules/colors.c src/modules/server.c src/pair.c  $(CFLAGS)

Impair:		src/impair.c
	$(CC) -o build/impair/Impair lib/libini/ini.c src/modules/configparser.c src/modules/dataStructure.c src/modules/colors.c src/modules/server.c src/impair.c  $(CFLAGS)

test:
	@$(CC) -o build/Test lib/libini/ini.c src/modules/configparser.c src/modules/dataStructure.c src/modules/colors.c tests/config.c tests/colors.c tests/main.c $(CFLAGS)
	@$(RM) config.ini
	@$(TEST)
	@$(RM) config.ini

clean:
	$(RM) build/Central
	$(RM) build/Pair
	$(RM) build/Impair
	$(RM) build/Test
	$(RM) config.ini