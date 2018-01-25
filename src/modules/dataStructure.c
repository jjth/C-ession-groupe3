#include "dataStructure.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
ListingLine *initialisationLine() {
    ListingLine *listingLine = malloc(sizeof(*listingLine));
    return listingLine;
}

void addALine(ListingLine *listingLine, int size, int id, char *str){
    int cnt;
    Line *new = malloc(sizeof(*new));
    if (listingLine == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }else {
        if(id == 1){
            new->next = NULL;
        }else{
            new->next = listingLine->first;
        }
	    new->id = id;
	    new->colors = malloc(sizeof(int)*size);
        for (cnt = 0; cnt < size; cnt++){
            new->colors[cnt]= RESET;
        }
    	new->line = malloc(sizeof(char)*size);
        for (cnt = 0; cnt < size; cnt++){
	       new->line[cnt] = str[cnt];
        }
	    listingLine->first = new;    	
    }
    if(listingLine->first == NULL){
        new->next = NULL;
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

void displayListingValue(ListingLine *listingLine, int size){
	int compteur = 0;
    int compteurLine = 0;
    int compteurColor = 0;
    int i = 0;
    char **tabLine = malloc(sizeof(*tabLine)*SIZE_STACK);
    if (listingLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = listingLine->first;
    while (current != NULL){
        //printf("%d-> ", current->id);
        tabLine[compteurLine]=current->line;
        // printf("%s\n", current->line);
        /*for (compteur = 0;compteur<size;compteur++){
            push(st,current->line[compteur]);
        	printf("[%c]",current->line[compteur]);
        }
        printf("\n");*/
        current = current->next;
        compteurLine += 1;
    }
    
    for(compteur =  compteurLine-1; compteur >= 0 ; compteur--){
        for (i = 0 ; i <size ; i++){
            printf("[%c]",tabLine[compteur][i] );
        }
        printf("\n");
    }
}
void displayListingColor(ListingLine *listingLine, int size){
    int compteur = 0;
    int compteurLine = 0;
    int i = 0;
    int **tabLine = malloc(sizeof(*tabLine)*SIZE_STACK);
    if (listingLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = listingLine->first;
    while (current != NULL){
        tabLine[compteurLine]=current->colors;
        /*for (compteur = 0;compteur<size;compteur++){
            printf("%d, ",current->colors[compteur]);
        }
        printf("\n");*/
        current = current->next;
        compteurLine += 1;
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
int getNeighbors(ListingLine *mylist,int nbLine,int nbColunmTotal,int yValue,int xValue,int distance,char target){
    // TODO DÉPLACER DANS CENTRAL
    // VIRER MYLIST NBLINE CONNU DANS CENTRAL COLUMN AUSSI 
    // RESTE PROVIENS DE LA REGLE 
    int x = 0;
    int y = 0;
    int cptT = 0;
    char tmp = ' ';

    for (y=distance; y > 0 ;y--){ 
        for (x = distance; x > 0 ; x--){ 
            //printf("loop %d %d \n",x,y);
            //  TODO COMPARER XVALUE + X  / -X À MODULO 2 POUR SAVOIR A QUI ENVOYÉ 
            if((xValue+x < nbColunmTotal) && (yValue+y <= nbLine)){
                //printf("1-> %d %d %d %d %c\n",x,y,xValue+x, yValue+y,getCharacter(mylist,yValue+y,xValue+x));
                //TODO ENVOI MSG
                tmp = getCharacter(mylist,yValue+y,xValue+x);
                if(tmp == target){ cptT++; }
            }
            if((xValue-x >= 0) && (yValue+y <= nbLine)){
                //printf("2-> %d %d %c\n",xValue-x, yValue+y,getCharacter(mylist,yValue+y,xValue-y));
                tmp = getCharacter(mylist,yValue+y,xValue-x);
                if(tmp == target){ cptT++; }
            }
            if((xValue+x < nbColunmTotal) && (yValue-y > 0)){
                //printf("3-> %d %d %c\n",xValue+x, yValue-x,getCharacter(mylist,yValue-y,xValue+x));
                tmp = getCharacter(mylist,yValue-y,xValue+x);
                if(tmp == target){ cptT++; }
            }
            if((xValue-x >= 0) && (yValue-y > 0)){
                //printf("4-> %d %d %c\n",xValue-x, yValue-y,getCharacter(mylist,yValue-y,xValue-x));
                tmp = getCharacter(mylist,yValue-y,xValue-x);
                if(tmp == target){ cptT++; }
            }
        }
    }
    //printf("debug -> %d distance: %d \n",cptT, distance );
    for(x=distance;x > 0;x--){
        if((xValue+x < nbColunmTotal) && (xValue+x <= xValue+distance)){
            //printf("55-> %d %d %c\n",xValue+x,yValue,getCharacter(mylist,yValue,xValue+x) );
            tmp = getCharacter(mylist,yValue,xValue+x);
            if(tmp == target){ cptT += 1; }
        }
        
        if((xValue-x >= 0) && (xValue-x >= xValue-distance)){
            //printf("555-> %d %d %c\n",xValue-x,yValue,getCharacter(mylist,yValue,xValue-x) );
            tmp = getCharacter(mylist,yValue,xValue-x);
            if(tmp == target){ cptT += 1; }
        }

    }
    //printf("debug1 -> %d distance: %d \n",cptT, distance );
    //printf("test\n");
    for(y=distance;y> 1;y--){
        if((yValue-y > 0) && (yValue-y >= yValue-y)){
            //printf("66-> %d %d %c\n",xValue,yValue-y,getCharacter(mylist,yValue-y,xValue) );
            tmp = getCharacter(mylist,yValue-y,xValue);
            if(tmp == target){ cptT += 1; }
        }
        
        if((yValue+y <= nbLine) && (yValue+y <= yValue+y)){
            //printf("666-> %d %d %c\n",xValue,yValue-y,getCharacter(mylist,yValue-y,xValue) );
            tmp = getCharacter(mylist,yValue+y,xValue);        
            if(tmp == target){ cptT += 1; }
        }

    }
    //printf("debug2 -> %d distance: %d \n",cptT, distance );
    return cptT;
}
struct stack* create_stack(int size){
    struct stack* st = (struct stack*) malloc(sizeof(struct stack));
    st->size = size;
    st->top = -1;
    st->array = (char*)malloc(st->size * sizeof(char));
    return st;
}

int isFull(struct stack* st){
    return st->top == st->size -1;
}

int isEmpty(struct stack* st){
    return st->top == -1;
}

void push(struct stack* st, char element){
    if(isFull(st)){
        return;
    }
    st->array[++st->top] = element;
    //printf("%d pushed !\n", element);
}

char pop(struct stack* st){
    if (isEmpty(st)){
        return -1;
    }
    return st->array[st->top--];
}
