#include <stdio.h>
#include <stdarg.h>
#include "./modules/dataStructure.h"
#include "./modules/colors.h"
#include "./modules/configparser.h"
#include "./modules/server.h"

/*
void print_error(const char* format, ...) {
    va_list args;
    va_start(args, format);

    setColor(1); // 1 = RED (see ANSI color codes)
    printf(format, args);
    resetColor();

    va_end(args);
}

int main(int argc, char **argv){
	int conf_fatal_error = TRUE;
    configuration conf = load_config(MODULE_PAIR);

    // Try to load configuration and handle all use-cases
    if (conf.err.id == ERROR_NONE) {
        conf_fatal_error = FALSE; // Loading succeed
    } else if (conf.err.id == ERROR_FILE_NOT_FOUND) {
        printf("Fichier de configuration introuvable.");
        // File not found: create default configuration.
        error default_config_creation = create_default_config(MODULE_PAIR);

        if (default_config_creation.id == ERROR_NONE) { // config.ini file created successfully
            printf(" Utilisation de la configuration par défaut.\n");

            // Reload the configuration we've just created.
            conf = load_config(MODULE_PAIR);

            if (conf.err.id == ERROR_NONE) {
                conf_fatal_error = FALSE;
            } else {
                print_error("Impossible de charger la configuration par défaut: %s", conf.err.message);
            }
        } else { // Cannot create a file in this folder => insufficient rights.
            print_error("\nImpossible de créer le fichier de configuration, veuillez demander à un administrateur");
            print_error(" de vérifier que vous avez des droits suffisants sur ce dossier.\n");
        }
    } else {
        print_error("Impossible de charger la configuration: %s", conf.err.message);
    }

    if (conf_fatal_error == FALSE) {
        if (conf.client.port == 0) {
            conf_fatal_error = TRUE;
            print_error("La configuration est invalide, veuillez contacter un administrateur.\n");
        }
    }

    if (conf_fatal_error == TRUE) {
        return -1;
    }
	init();
	
	app(conf.client.port);

	end();

	return 0;
*/
int main(int argc, char const *argv[]){

    int line = 5; 
    int col = 3;
    int d = 3;
    char t = 'X';
    int nbLine = 5;
    int nbColunm = 4;
    int tmp1 = -100;
    int tmp2 = -100;
    ListingTi *myTi = initialisationTi();
	ListingLine *myListing = initialisationLine();
    
    addALine(myListing,4,1,"XXXX");
    addALine(myListing, 4, 2,"XXXX");
    addALine(myListing, 4, 3,"XXXX");
    addALine(myListing, 4, 4,"XXYY");
    addALine(myListing, 4, 5,"XXXY");
    //displayListingValue(myListing,4);
    /*deleteALine(myListing,0);
    displayListing(myListing,4);
    setCharacter(myListing, 2,3,'z');
    displayListing(myListing,4);
    printf("%c \n",getCharacter(myListing, 2,3));
    printf("%d \n",getCharacterColor(myListing, 2,3));
    setCharacterColor(myListing,2,3,2);
    displayListing(myListing,4);*/
    //printf("x: %d, y: %d [%c], d: %d, t: %c, result:%d \n",col,line,getCharacter(myListing,line,col),d,t,getNeighbors(myListing,nbLine,nbColunm,line,col,d,t));
    //displayListingValue(myListing,4);
    ListingLine *myListing2 = createCopy(myListing, 4);
    ListingLine *myListing3 = createCopy(myListing2, 4);
    setCharacter(myListing2,2,3,'Z');
    setCharacter(myListing3,2,3,'A');
    addTi(myTi, 0, myListing);
    addTi(myTi, 1, myListing2);
    addTi(myTi, 2, myListing3);
    
    displayListingValue(myListing,4);
    printf("\n");
    displayListingValue(myListing2,4);
    printf("\n");
    displayListingValue(myListing3,4);
    printf("\n");
    ListingLine *myListing5 = createCopy(myListing, 4);
    displayListingValue(myListing5,4);
    printf("\n");
    tmp1 = isCycle(myTi,myListing5);
    printf("%d\n", tmp1);
    ListingLine *myListing4 = createCopy(myListing, 4);
    setCharacter(myListing4,2,3,'E');
    tmp2 = isCycle(myTi,myListing4);
    printf("%d\n", tmp2);
     return 0;
}
