#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "displayMatrix.h"


void setColor(int code){
	if(code == 1){
		printf("%s", ANSI_COLOR_RED);
	}else if(code == 2){
		printf("%s",ANSI_COLOR_GREEN);
	}else if(code == 3){
		printf("%s",ANSI_COLOR_YELLOW);
	}else if(code == 4){
		printf("%s",ANSI_COLOR_BLUE);
	}else if(code == 5){
		printf("%s",ANSI_COLOR_MAGENTA);
	}else if(code == 6){
		printf("%s",ANSI_COLOR_CYAN);
	}
}
void resetColor(){
	printf("%s",ANSI_COLOR_RESET);
}

char get_character(int x, int y){
	char array[3][5] = {{'1','2','3','4','9'},{'5','6',' ','7','8'},{'A','B','C','D','5'}};
	return array[x][y];
}

int get_character_color(int x, int y){
	int array[3][5] = {{1,2,3,4,5},{5,6,4,3,2},{1,3,2,6,3}};
	return array[x][y];
}


void display_line_separator(char separator, int number){
	for (int y = 0; y < number; ++y){
		printf("%c",separator);
	}
}


void display_matrix(int X, int Y){
	int lengthFullLine = (Y*4+1);
	int lengthMiddleLine = 3;

	display_line_separator('-',lengthFullLine);
	printf("\n");
	for(int x = 0; x < X; x = x + 1){
		printf("|");
		for (int y = 0; y < Y; y = y + 1){
			setColor((get_character_color(x,y)));
			printf(" %c ", get_character(x,y));
			resetColor();
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
