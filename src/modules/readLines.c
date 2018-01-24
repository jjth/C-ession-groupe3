#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../globals.h"
#include "readLines.h"
#include "scanf.h"

int* ask_lines(){
	int run = TRUE;
	int cpt = 1;
	int nbColumn = -1;
    int* matrixSize = malloc(sizeof(int)*2);
    int i = 0;
	printf("[-] Saisie de l'échéquier\n");
	printf("\t[-] Saisisez le nombre de colonnes de l'échéquier : ");
    
    while ((nbColumn = scanfInt()) < 1) {
        if (nbColumn == -1) {
            printf("Ceci n'est pas un nombre, veuillez réessayer : ");
        } else {
            printf("Le nombre minimal de colonnes est 1, veuillez réessayer : ");
        }
    }
	printf("\t[-] Saisissez les lignes de l'échéquier : \n");
	
	char* line = malloc(sizeof(char)*nbColumn);
    char c = -1;

    while(run) {
        printf("\t\t[-] Ligne n°%d (ligne vide pour arrêter) : ", cpt);

        line = scanfLineWithMax(nbColumn);

        if (strlen(line) == nbColumn) {
            send_to_network(line, cpt);
            cpt += 1;
        } else if (strlen(line) == 0) {
            run = FALSE;
        } else {
            printf("/!\\ Le nombre de colonne est mauvais veuillez recommencer. \n");
        }
    }

    matrixSize[0] = cpt;
    matrixSize[1] = nbColumn;

    return matrixSize;
}

void send_to_network(char* line, int id){
	// TODO : VINCENT SEND DATA TO CLIENT 
	if((id%2)==0){
		//send to pair 
		printf("Send line to pair client\n");
	}else{
		//send to impair 
		printf("Send line to impair client\n");
	}
}