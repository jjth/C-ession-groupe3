#include <stdlib.h>
#include <stdio.h>
#define LINE_SIZE 5
#define NB_LINE 5
int main(int argc, char const *argv[])
{
	char* fileName = "inputTest.txt";
	FILE* file = NULL;
	char currentLine[LINE_SIZE] = "";
	int lineCounter = 0;
	char* lineImpair[NB_LINE+1];
	char* linePair[NB_LINE+1];
	int counter = 0;

	
	file=fopen(fileName, "r");
	if(file != NULL){
		while (fscanf(file,"%s",currentLine)==1){
			lineCounter++;
			printf("%d %s\n",lineCounter,currentLine);
			if ((lineCounter%2) == 0){
				linePair[lineCounter]=currentLine;
			}else{
				lineImpair[lineCounter]=currentLine;
			}
		}
		
		
		fclose(file);
	}else{
		printf("Erreur d'ouverture du fichier : %s\n", fileName);
	}

	for (counter = 1; counter<NB_LINE+1; counter++){
		if((counter%2) == 0){
			printf("pair -> %d %s\n",counter,linePair[counter]);
		}else{
			printf("impair -> %d %s\n",counter,lineImpair[counter]);
		}
	}


	return 0;
}