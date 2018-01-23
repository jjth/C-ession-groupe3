/*
rulesParser.h
-----

By Julien Couillard

Role : prototypes of the functions of the parser of rules.
*/

typedef enum LogicStructure LogicStructure;
typedef enum LogicOperator LogicOperator;

enum LogicStructure {
    OPERATOR_AT_LEAST,
    OPERATOR_AT_MOST,
    OPERATOR_NONE,
    OPERATOR_EXACTLY
};

enum LogicOperator {
    OPERATOR_OR,
	OPERATOR_AND,
	EMPTY
};

typedef struct rule rule;
struct rule{
	char charA;
	LogicStructure* logicStructureB;
	int* numberC;
	char* charD;
	int* numberE;
	LogicOperator logicOperatorF;
	char charG;
}; 

typedef struct element element;
struct element{
	int id;
	rule* rule;
	char* color; 
	struct element *nxt;
}; 

typedef struct llist llist;
struct llist {
    element *first;
};

// main function
void ask_rules();

// list manipulation 
llist add_at_the_end(llist list, int id, rule* rule, char* color);
element* research_element(llist list, int id);
llist erase_list(llist list);
void print_list(llist liste);

// check rule 
LogicStructure parse_logic_structure(int response);
LogicOperator parse_logic_operator(int response);
void set_rule(rule* rule, llist list, int id);
bool check_new_rules(char* response);

// str manipulation 
char *str_strip (char* string);
char *str_lower (char* string);
void print_rule_fr(element *element);
char* translate_logic_struc(LogicStructure logicStructure);
char* translate_logic_operator(LogicOperator logicOperator);
