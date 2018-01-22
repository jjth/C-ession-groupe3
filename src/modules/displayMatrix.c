#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "displayMatrix.h"


char *get_color_from_code(int code){
	switch(code){
		case 1 :
			return ANSI_COLOR_RED;
		case 2 :
			return ANSI_COLOR_GREEN;
		case 3 :
			return ANSI_COLOR_YELLOW;
		case 4 :
			return ANSI_COLOR_BLUE;
		case 5 :
			return ANSI_COLOR_MAGENTA;
		case 6 :
			return ANSI_COLOR_CYAN;
		default:
			return ANSI_COLOR_RESET;
	}
}

char *get_character(int x, int y){
	char array[3][5];
	char *res = malloc(sizeof(char) * 2);

	strcpy(array[0],"12349");
	strcpy(array[1],"56 78");
	strcpy(array[2],"ABCD ");
	
	res[0] = array[x][y];
	res[1] = '1';

	return res;
}

void display_line_separator(char separator, int number){
	for (int y = 0; y < number; ++y){
		printf("%c",separator);
	}
}

void display_matrix(int X, int Y){
	int lengthFullLine = (Y*4+1);
	int lengthMiddleLine = 3;
	char character[2];
	int colorCode;

	display_line_separator('-',lengthFullLine);
	printf("\n");
	for(int x = 0; x < X; x = x + 1){
		printf("|");
		for (int y = 0; y < Y; y = y + 1){

			strcpy(character,get_character(x,y));
			colorCode = strtol(&character[1],NULL,10);
			printf("%s",get_color_from_code(colorCode));
			printf(" %c ",character[0]);
			printf("%s",get_color_from_code(0));

			printf("|");
		}
		printf("\n");
		if( x == X-1){
			display_line_separator('-',lengthFullLine);
		}else{
			printf("|");
			for (int y = 0; y < Y; y = y + 1){
				display_line_separator('-',lengthMiddleLine);
				printf("|");
			}
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[])
{
	display_matrix(3,4);
	return 0;
}
