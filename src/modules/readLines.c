#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../globals.h"
#include "client.h"
#include "readLines.h"
#include "scanf.h"

int* ask_lines(NetworkClientConnection* conn_pair, NetworkClientConnection* conn_impair){
	int run = TRUE;
	int cpt = 1;
	int nbColumn = -1;
    int* matrixSize = malloc(sizeof(int)*2);

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
    NetworkClientConnection* conn_temp;
    while(run) {
        printf("\t\t[-] Ligne n°%d (ligne vide pour arrêter) : ", cpt);

        line = scanfLineWithMax(nbColumn);

        if (strlen(line) == nbColumn) {
            if ((cpt%2) == 0) {
                conn_temp = conn_pair;
            } else {
                conn_temp = conn_impair;
            }

            error err = send_line_to_network(*conn_temp, line);

            while (err.id != ERROR_NONE) {
                printf("Impossible d'envoyer cette ligne: %s\n", err.message);
                err = send_line_to_network(*conn_temp, line);
            }
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
