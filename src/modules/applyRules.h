#include "../rulesParser.h"
typedef struct Ope Ope;
struct Ope {
    int ope1;
    int ope2;
    int operator;
};

void build_expression(int x, int y, rule* r, Ope* myOpe);
int check_rule(int x, int y, rule* r,Ope* myOpe);
char get_character(int x, int y);