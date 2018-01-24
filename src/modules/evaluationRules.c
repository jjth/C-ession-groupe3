#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rulesParser.h"

int evaluation_rule_line(int x, int y, LogicStructure logicStructure, int numberOccurences, char charFounded, int distance);

int main(int argc, char const *argv[]){
	int res;
	res = evaluation_rule_line(1,1,OPERATOR_AT_LEAST, 3,'E',2);
	printf("%d", res);
	printf(" attendu : 1\n");
	res = evaluation_rule_line(1,1,OPERATOR_AT_LEAST, 1,'E',2);
	printf("%d", res);
	printf(" attendu : 0\n");
	res = evaluation_rule_line(1,1,OPERATOR_AT_MOST, 1,'E',2);
	printf("%d", res);
	printf(" attendu : 1\n");
	res = evaluation_rule_line(1,1,OPERATOR_AT_MOST, 3,'E',2);
	printf("%d", res);
	printf(" attendu : 0\n");
	res = evaluation_rule_line(1,1,OPERATOR_EXACTLY, 2,'E',2);
	printf("%d", res);
	printf(" attendu : 1\n");
	res = evaluation_rule_line(1,1,OPERATOR_EXACTLY, 3,'E',2);
	printf("%d", res);
	printf(" attendu : 0\n");
	res = evaluation_rule_line(1,1,OPERATOR_NONE, 3,'E',2);
	printf("%d", res);
	printf(" attendu : 0\n");
	
    return EXIT_SUCCESS;
}

int evaluation_rule_line(int x, int y, LogicStructure logicStructure, int numberOccurences, char charFounded, int distance){	
	//int resTab = get_scope(x,y,distance,charFounded);
	int resTab = 2;
	int eval = 0;
	switch (logicStructure) {
		case OPERATOR_AT_LEAST :
			if(numberOccurences >= resTab) eval = 1;
			else eval = 0;
			break;
		case OPERATOR_AT_MOST :
			if(numberOccurences <= resTab) eval = 1;
			else eval = 0;
			break;
		case OPERATOR_EXACTLY :
			if(numberOccurences == resTab) eval = 1;
			else eval = 0;
			break;
		case OPERATOR_NONE :
			if(0 == resTab) eval = 1;
			else eval = 0;
			break;
		}
	return eval;
}