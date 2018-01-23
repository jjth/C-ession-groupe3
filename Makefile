CC	=	gcc
CFLAGS	=	-g -Wall
RM	=	rm -f
all:	Central Pair Impair

Central:	src/central.c
	$(CC) -o build/Central lib/libini/ini.c src/modules/configparser.c src/central.c $(CFLAGS)

Pair:		src/pair.c
	$(CC) -o build/Pair src/pair.c $(CFLAGS)

Impair:		src/impair.c
	$(CC) -o build/Impair src/impair.c $(CFLAGS)

test:
	@$(CC) -o build/Test lib/libini/ini.c src/modules/configparser.c src/modules/colors.c tests/config.c tests/colors.c tests/main.c $(CFLAGS)
	@$(RM) config.ini
	@build/Test
	@$(RM) config.ini

clean:
	$(RM) build/Central
	$(RM) build/Pair
	$(RM) build/Impair
	$(RM) build/Test
	$(RM) config.ini
