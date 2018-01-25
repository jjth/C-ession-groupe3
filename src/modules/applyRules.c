#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "applyRules.h"



void build_expression(int x, int y, rule* r, Ope* myOpe){
    
    
    LogicStructure B;
    int C = 0;
    int E = 0;
    char D = ' ';

    int eval = 0;    
    
    B = r->logicStructureB[0];
    D = r->charD[0];
    E = r->numberE[0];

    if(B != OPERATOR_NONE){
        C = r->numberC[0];
    }
    //eval = evaluation_rule_line(x,y,B,C,D,E);
    eval = 1;
    myOpe->ope1 = eval;
    myOpe->operator = EMPTY;
    
    if (r->logicOperatorF != EMPTY){
        B = r->logicStructureB[1];
        D = r->charD[1];
        E = r->numberE[1];

        if(B != OPERATOR_NONE){
            C = r->numberC[1];
        }

        //eval = evaluation_rule_line(x,y,B,C,D,E);
        eval = 1;
        myOpe->ope2 = eval;
        myOpe->operator = r->logicOperatorF;
    }
}

int check_rule(int x, int y, rule* r,Ope* myOpe){    

    build_expression(x, y, r, myOpe);

    //parse_expression(expression, parsedExpression, expressionSize, numberLines);

    //printf("op1=%d ope2=%d operator=%d\n", myOpe->ope1,myOpe->ope2,myOpe->operator);

    int res = -1;
    switch(myOpe->operator){
        case EMPTY:
            res = myOpe->ope1;
            break;
        case OPERATOR_OR :
            res = (myOpe->ope1 || myOpe->ope2);
            break;
        case OPERATOR_AND:
            res = (myOpe->ope1 && myOpe->ope2);
            break;
        default :
            res = -1;
    }

    return res;
}

char get_character(int x, int y){
    
    /*char array[5][5] = {
        {'O','X','O','X','O'},
        {'X','O','X','O','X'},
        {'O','X','O','X','O'},
        {'X','O','X','O','X'},
        {'O','X','O','X','O'}
    };*/

    char array[2][2] = {{'O','X'},{'X','O'}};
    return array[x][y];
}


int main(int argc, char const *argv[]){
    
    Ope *myOpe = malloc(sizeof(*myOpe));
    int isApplied = 0;
    myOpe->ope1 = -1;
    myOpe->ope2 = -1;
    myOpe->operator = -1;

    llist* listRules = malloc(sizeof(llist));
    

    rule* current_rule = malloc(sizeof(rule));

     
    current_rule->logicStructureB = malloc(sizeof(LogicStructure)*2);
    current_rule->numberC = malloc(sizeof(int)*2);
    current_rule->charD = malloc(sizeof(char)*2);
    current_rule->numberE = malloc(sizeof(int)*2);
    //current_rule->logicOperatorF = malloc(sizeof(LogicOperator));

    current_rule->charA = 'X';  
    current_rule->logicStructureB[0] = OPERATOR_EXACTLY;
    current_rule->numberC[0] = 1;
    current_rule->charD[0] = 'O';
    current_rule->numberE[0] = 1;
    current_rule->logicOperatorF = EMPTY;
    current_rule->charG = 'O';

    rule* current_rule2 = malloc(sizeof(rule));
    
     
    current_rule2->logicStructureB = malloc(sizeof(LogicStructure)*2);
    current_rule2->numberC = malloc(sizeof(int)*2);
    current_rule2->charD = malloc(sizeof(char)*2);
    current_rule2->numberE = malloc(sizeof(int)*2);
    //current_rule2->logicOperatorF = malloc(sizeof(LogicOperator));

    current_rule2->charA = 'X';  
    current_rule2->logicStructureB[0] = OPERATOR_EXACTLY;
    current_rule2->numberC[0] = 1;
    current_rule2->charD[0] = 'O';
    current_rule2->numberE[0] = 1;
    current_rule2->logicOperatorF = EMPTY;
    current_rule2->charG = 'O';

    

    element* elem1 = malloc(sizeof(elem1));
    element* elem2 = malloc(sizeof(elem2));


    elem1->id = 1;
    elem1->rule = current_rule;
    elem1->color = "rouge";
    elem1->nxt = elem2;


    elem2->id = 2;
    elem2->rule = current_rule2;
    elem2->color = "rouge";
    elem2->nxt = NULL;

    
    listRules->first = elem1;

    element *tmp=listRules->first;
    //tmp = listRules->first;

    int X = 2;
    int Y = 2;



    for(int x = 1; x <= X; x = x + 1){
        for (int y = 0; y < Y; y = y + 1){
           if(current_rule->charA == get_character(x,y)){
                while(tmp->nxt != NULL){
                    if(check_rule(x,y,tmp->rule,myOpe) == 1){
                        printf("YES !\n");
                        isApplied = 1;
                    }
                    tmp = tmp->nxt;
                }
                printf("YES !\n");
            }
            printf("YES !\n");

        }
    }

    return 0;
}

