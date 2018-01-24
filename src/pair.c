#include "modules/dataStructure.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[]){
    int line = 5; 
    int col = 3;
    int d = 3;
    char t = 'X';
    int nbLine = 5;
    int nbColunm = 4;
	ListingLine *myListing = initialisationLine();
    addALine(myListing,4,1,"XXXX");
    addALine(myListing, 4, 2,"XXXX");
    addALine(myListing, 4, 3,"XXXX");
    addALine(myListing, 4, 4,"XXYY");
    addALine(myListing, 4, 5,"XXXY");
    displayListingValue(myListing,4);
    /*deleteALine(myListing,0);
    displayListing(myListing,4);
    setCharacter(myListing, 2,3,'z');
    displayListing(myListing,4);
    printf("%c \n",getCharacter(myListing, 2,3));
    */printf("%d \n",getCharacterColor(myListing, 2,3));
    /*setCharacterColor(myListing,2,3,2);
    displayListing(myListing,4);*/
    printf("x: %d, y: %d [%c], d: %d, t: %c, result:%d \n",col,line,getCharacter(myListing,line,col),d,t,getNeighbors(myListing,nbLine,nbColunm,line,col,d,t));
    return 0;
}
    
