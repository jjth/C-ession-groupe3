#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "readLines.h"

int main(int argc, char const *argv[]){
	
	ask_lines();
    return EXIT_SUCCESS;
}

void ask_lines(){
	bool run = true;
	int cpt = 1;
	int nbColumn = 0;
	int x = -1;
    
    int i = 0;
	printf("[-] Saisie de l'échéquier\n");
	printf("\t[-] Saisisez le nombre de colonnes de l'échéquier : ");
	scanf("%d", &nbColumn);
	printf("\t[-] Saisissez les lignes de l'échéquier : \n");
	
	char* line = malloc(sizeof(char)*nbColumn);
    char c = -1;

    // Clear input buffer
    c = getchar();

    while(run) {
        printf("\t\t[-] Ligne n°%d (ligne vide pour arrêter) : ", cpt);

        i = 0;
        do {
            c = getchar();

            if (i < nbColumn) {
                line[i] = c;
            }
            i=i+1;
        } while(c != EOF && c != '\n');

        i--;

        if (i == nbColumn) {
            send_to_network(line, cpt);
            cpt += 1;
        } else if (line[0] == '\n') {
            run = false;
        } else {
            printf("/!\\ Le nombre de colonne est mauvais veuillez recommencer. \n");
        }
    }
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