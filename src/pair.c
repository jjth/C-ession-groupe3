#include "dataStructure.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[]){
	ListingLine *myListing = initialisationLine(0,'X','X','X','X');
    addALine(myListing, 1,'X','X','X','Y');
    addALine(myListing, 2,'X','X','Y','Y');
    addALine(myListing, 3,'X','Y','Y','Y');
    addALine(myListing, 4,'Y','Y','Y','Y');
    displayListing(myListing);
    deleteALine(myListing,0);
    displayListing(myListing);
    setCharacter(myListing, 2,3,'z');
    displayListing(myListing);
    printf("%c \n",getCharacter(myListing, 2,3));
    return 0;
}
    