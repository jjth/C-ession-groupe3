#include "modules/dataStructure.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[]){
	ListingLine *myListing = initialisationLine(4,0,'X','X','X','X');
    addALine(myListing, 4, 1,'X','X','X','Y');
    addALine(myListing, 4, 2,'X','X','Y','Y');
    addALine(myListing, 4, 3,'X','Y','Y','Y');
    addALine(myListing, 4, 4,'Y','Y','Y','Y');
    displayListing(myListing,4);
    deleteALine(myListing,0);
    displayListing(myListing,4);
    setCharacter(myListing, 2,3,'z');
    displayListing(myListing,4);
    printf("%c \n",getCharacter(myListing, 2,3));
    printf("%d \n",getCharacterColor(myListing, 2,3));
    setCharacterColor(myListing,2,3,2);
    displayListing(myListing,4);
    return 0;
}
    
