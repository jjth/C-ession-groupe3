#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include "displayMatrix.h"
#include "client.h"

void display_line_separator(char separator, int number){
	for (int y = 0; y < number; ++y){
		printf("%c",separator);
	}
}

void display_matrix(int X, int Y){
	printf("DISPLAYMATRIX\n");
	int lengthFullLine = (Y*4+1);
	int lengthMiddleLine = 3;

	display_line_separator('-',lengthFullLine);
	printf("\n");
	for(int x = 0; x < X; x = x + 1){
		printf("|");
		for (int y = 0; y < Y; y = y + 1){
			setColor((get_color_from(conn_pair, x,y)));
			printf(" %c ", get_char_from(conn_pair, x,y));
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
