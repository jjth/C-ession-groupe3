#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rulesParser.h"
#include "dataStructure.h"
#include "evaluationRules.h"

int evaluation_rule_line(int x, int y, LogicStructure logicStructure, int numberOccurences, char charFounded, int distance, int totalNUMBERofLINES, int totalNUMBERofCOLUMNS){	
	int resTab = getNeighbors(totalNUMBERofLINES, totalNUMBERofCOLUMNS,x,y,distance,charFounded);
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