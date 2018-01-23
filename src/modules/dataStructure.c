#include "dataStructure.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
ListingLine *initialisationLine(int size,int id, char c0, char c1, char c2, char c3) {
    ListingLine *listingLine = malloc(sizeof(*listingLine));
    Line *line = malloc(sizeof(*line));

    if (listingLine == NULL || line == NULL)
    {
        exit(EXIT_FAILURE);
    }else{
    	line->id = id;
    	line->colors = malloc(sizeof(int)*size);
    	line->colors[0] = RESET;
    	line->colors[1] = RESET;
    	line->colors[2] = RESET;
    	line->colors[3] = RESET;
    	line->line = malloc(sizeof(char)*size);
    	line->line[0] = c0;
    	line->line[1] = c1;
    	line->line[2] = c2;
    	line->line[3] = c3;
    	line->next = NULL;
    	listingLine->first = line;
    	return listingLine;
    }
}

void addALine(ListingLine *listingLine, int size, int id, char c0, char c1, char c2, char c3){
    Line *new = malloc(sizeof(*new));
    if (listingLine == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }else {
	    new->id = id;
	    new->colors = malloc(sizeof(int)*size);
	    new->colors[0] = RESET;
    	new->colors[1] = RESET;
    	new->colors[2] = RESET;
    	new->colors[3] = RESET;
    	new->line = malloc(sizeof(char)*size);
	    new->line[0] = c0;
    	new->line[1] = c1;
    	new->line[2] = c2;
    	new->line[3] = c3;
	    new->next = listingLine->first;
	    listingLine->first = new;    	
    }
}

int deleteALine(ListingLine *listingLine, int id){
	Line *previous = NULL;
    Line *current = NULL;
	if (listingLine->first->next != NULL && listingLine->first->id != id){
        previous = listingLine->first;
        current = previous->next;
        while(current->id != id && current != NULL){
        	previous = current;
        	current = previous->next;
        }
        if(current != NULL){
        	previous->next=current->next;
        	free(current);
        	return 0;
        }else{
        	return -1;
        }
    }else{
    	if(listingLine->first->next == NULL){
    		return -1;
    	}
    	if(listingLine->first->id == id){
    		current=listingLine->first;
    		current=current->next;
    		free(listingLine->first);
    		listingLine->first = current;
    		return 0;
    	}
    }
    return -1;
}

void displayListing(ListingLine *listingLine, int size){
	int compteur = 0;
    if (listingLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = listingLine->first;
    while (current != NULL){
        printf("%d\n",current->id);
        for (compteur = 0;compteur<size;compteur++){
        	printf("%d, ",current->colors[compteur]);
        }
        printf("\n");
        for (compteur = 0;compteur<size;compteur++){
        	printf("%c, ",current->line[compteur]);
        }
        printf("\n");
        current = current->next;
    }
}

char getCharacter(ListingLine *listingLine, int idLine,int idCharacter){
	if (listingLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = listingLine->first;
    while(current != NULL){
    	if(current->id == idLine){
    		return current->line[idCharacter];
    	}
    	current = current->next;
    }
    return -1;
}
int getCharacterColor(ListingLine *listingLine, int idLine,int idColor){
    if (listingLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = listingLine->first;
    while(current != NULL){
        if(current->id == idLine){
            return current->colors[idColor];
        }
        current = current->next;
    }
    return -1;
}
void setCharacter(ListingLine *listingLine, int idLine,int idCharacter,char c){
	int size = 0;
	if (listingLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = listingLine->first;
    while(current != NULL){
    	if(current->id == idLine){
    		current->line[idCharacter] = c;
    	}
    	current = current->next;
    }
}
void setCharacterColor(ListingLine *listingLine, int idLine,int idColor,int c){
    int size = 0;
    if (listingLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = listingLine->first;
    while(current != NULL){
        if(current->id == idLine){
            current->colors[idColor] = c;
        }
        current = current->next;
    }
}
