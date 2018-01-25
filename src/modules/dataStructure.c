#include "dataStructure.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
ListingLine *initialisationLine() {
    ListingLine *listingLine = malloc(sizeof(*listingLine));
    listingLine->first = NULL;
    return listingLine;
}

ListingTi *initialisationTi() {
    ListingTi *listingTi = malloc(sizeof(*listingTi));
    listingTi->first = NULL;
    return listingTi;
}
void addTi(ListingTi *myListingTi, int id, ListingLine* matrix){
    Ti *new = malloc(sizeof(*new));
    if (myListingTi == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }else {
        
        new->id = id;
        new->matrix = matrix;
        
    }
    if(myListingTi->first == NULL){
        new->next = NULL;
    }else{
        new->next = myListingTi->first;
        
    }
    myListingTi->first = new;
}
void addALine(ListingLine *listingLine, int size, int id, char *str){
    int cnt;
    Line *new = malloc(sizeof(*new));
    if (listingLine == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }else {
        if(listingLine == NULL){
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
void AddLineQueue(ListingLine *listingLine, int size, int id, char *str){
    int cnt;
    Line *new = malloc(sizeof(*new));
    Line *tmp = malloc(sizeof(*tmp));
    if (listingLine == NULL || new == NULL)
    {
        exit(EXIT_FAILURE);
    }else {
        new->next = NULL;
        new->id = id;
        new->colors = malloc(sizeof(int)*size);
        for (cnt = 0; cnt < size; cnt++){
            new->colors[cnt]= RESET;
        }
        new->line = malloc(sizeof(char)*size);
        new->line = strdup(str);
        /*for (cnt = 0; cnt < size; cnt++){
           new->line[cnt] = str[cnt];
        }*/
        
        if(listingLine->first == NULL){
            listingLine->first = new;
        }else {
            tmp = listingLine->first;
            while(tmp->next != NULL){
                tmp = tmp->next;
            }
        }
        tmp->next = new;
    }
}
ListingLine *createCopy(ListingLine *oldLine, int size){
    ListingLine *newListing = malloc(sizeof(*newListing));
    if (oldLine == NULL){
        exit(EXIT_FAILURE);
    }
    Line *current = oldLine->first;
    while (current != NULL){
        //printf("%d\n",current->id );
        AddLineQueue(newListing, size, current->id, current->line);
        current = current->next;
    }
    return newListing;
}
int compare2matrix(ListingLine *myList1,ListingLine *myList2){
    Line *tmp1 = malloc(sizeof(*tmp1));
    Line *tmp2 = malloc(sizeof(*tmp2));
    if (myList1 == NULL || myList2 == NULL){
        exit(EXIT_FAILURE);
    }else{
        tmp1=myList1->first;
        tmp2=myList2->first;
        while(tmp1->next != NULL){
            if(strcmp(tmp1->line,tmp2->line) != 0){
                //printf("%s %s\n", tmp1->line,tmp2->line);
                return 0;
            }
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }
    }
    return 1;
}
int isCycle(ListingTi *myListTi, ListingLine *myListingLine){
    int cnt = -11;
    Ti *tmp = malloc(sizeof(*tmp));
    if(myListTi == NULL || myListingLine == NULL){
        exit(EXIT_FAILURE);
    }else{
        tmp=myListTi->first;
        while(tmp != NULL){
            cnt = compare2matrix(tmp->matrix,myListingLine);
            if(cnt){
                return tmp->id;
            }
            tmp = tmp->next;
        }
    }
    return -1;
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
    int compteurLine = 0;
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
