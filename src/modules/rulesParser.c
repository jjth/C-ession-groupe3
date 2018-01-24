#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>
#include "../globals.h"
#include "rulesParser.h"
#include "scanf.h"

#define STR(s) #s
#define XSTR(s) STR(s)


void ask_rules(){
	// intean to enter multiple rules
	int enterRules = TRUE;
	// int logicOperatorUse = FALSE;
	// size of each lines of the rules 
	const int sizeNewRules = 4;
	// variable for user input 
	char* strNewRules = malloc(sizeof(char)*sizeNewRules);

	int valueLogicStructure;
	int valueLogicOperator;
	// list of rules 
	llist* listRules = malloc(sizeof(llist));
	listRules->first = NULL;

	int cptRules = 0;

	printf("[-] Saisie des règles : \n");

	while(enterRules){
		printf("\t[-] Saisie d'une nouvelle règle : \n");

		rule* current_rule = malloc(sizeof(rule));
		current_rule->charA = '0';	
		current_rule->logicStructureB = malloc(sizeof(LogicStructure)*2);
		current_rule->numberC = malloc(sizeof(int)*2);
		current_rule->charD = malloc(sizeof(char)*2);
		current_rule->numberE = malloc(sizeof(int)*2);
		current_rule->logicOperatorF = EMPTY;
		current_rule->charG = '0';

		int cptCondition = 0;
		int logicOperatorUse = FALSE;

		printf("\t\t[-] Caractère à modifier : ");
		current_rule->charA = scanfChar();
		
		// ask for the differents conditions
		do{
			do{
				logicOperatorUse = FALSE;

				printf("\t\t[-] Structure logique : \n");
				printf("\t\t\t[-] 1 - \"au moins\"\n");
				printf("\t\t\t[-] 2 - \"au plus\"\n");
				printf("\t\t\t[-] 3 - \"exactement\"\n");
				printf("\t\t\t[-] 4 - \"aucun\"\n");
				printf("\t\t[-] Valeur choisie : ");

				valueLogicStructure = scanfInt();

				current_rule->logicStructureB[cptCondition] = parse_logic_structure(valueLogicStructure);

			}while (current_rule->logicStructureB[cptCondition] == -1);

			if (current_rule->logicStructureB[cptCondition] != OPERATOR_NONE ){
				printf("\t\t[-] Valeur souhaité : ");
        
				while ((current_rule->numberC[cptCondition] = scanfInt()) < 1) {
					if (current_rule->numberC[cptCondition] == -1) {
						printf("Ceci n'est pas un nombre, veuillez réessayer : ");
					} else {
						printf("Le nombre minimal est 1, veuillez réessayer : ");
					}
				}
			}

			printf("\t\t[-] Caractère environnant : ");
			current_rule->charD[cptCondition] = scanfChar();

			printf("\t\t[-] Nombre de cases à distance : ");
			while ((current_rule->numberE[cptCondition] = scanfInt()) < 1) {
				if (current_rule->numberE[cptCondition] == -1) {
					printf("Ceci n'est pas un nombre, veuillez réessayer : ");
				} else {
					printf("Le nombre minimal est 1, veuillez réessayer : ");
				}
			}

			if (cptCondition < 1){
				do{
					printf("\t\t[-] Opérateur logique : \n");
					printf("\t\t\t[-] 1 - \"ou\"\n");
					printf("\t\t\t[-] 2 - \"et\"\n");
					printf("\t\t\t[-] 3 - \"aucun\"\n");
					printf("\t\t[-] Valeur choisie : ");
					valueLogicOperator = scanfInt();
					current_rule->logicOperatorF = parse_logic_operator(valueLogicOperator);

				}while (current_rule->logicOperatorF == -1);
				
				if(current_rule->logicOperatorF != EMPTY) logicOperatorUse = TRUE;
			}
			cptCondition++;
			
		}while(logicOperatorUse && (cptCondition < 2));

		printf("\t\t[-] Nouveau caractère souhaité : ");
		current_rule->charG = scanfChar();

		set_rule(current_rule, listRules, cptRules);

		printf("[/!\\] Souhaitez-vous ajouter une nouvelle règle (oui/non) ? ");

		strNewRules = scanfLineWithMax(3);
		if(!check_new_rules(strNewRules)) enterRules = FALSE;

		cptRules++;
	}
}

LogicStructure parse_logic_structure(int response){
	switch (response) {
		case 1 :
			return OPERATOR_AT_LEAST;
			break;

		case 2 :
			return OPERATOR_AT_MOST;
			break;

		case 3 :
			return OPERATOR_EXACTLY;
			break;
		case 4 :
			return OPERATOR_NONE;
			break;

		default:
			printf("[/!\\] Erreur mauvaise saisie pour la structure logique. Veuillez recommencer : \n");
			return -1;
	}
}

LogicOperator parse_logic_operator(int response){
	switch (response) {
		case 1 :
			return OPERATOR_OR;
			break;

		case 2 :
			return OPERATOR_AND;
			break;

		case 3 :
			return EMPTY;
			break;

		default:
			printf("[/!\\] Erreur mauvaise saisie pour l'opérateur logique. Veuillez recommencer : \n");
			return -1;
	}
}

void set_rule(rule* rule, llist* list, int id){
	// TODO : Jean set color here 
	add_at_the_end(list, id, rule, "blue");
	printf("[-] Affichage des règles enregistrées : \n");
	print_list(list);
	
}

int check_new_rules(char* response ){
	response = str_strip(response);
	response = str_lower(response);
	if(strcmp(response, "oui") == 0) return TRUE;
	else return FALSE;
}

char *str_lower (char* string){
   int i = 0;
   while( string[i] ) {
      string[i] = tolower(string[i]);
      i++;
   }
   return string;
}

char *str_strip (char* string){
   char *strip = NULL;

   if (string != NULL)
   {
      strip = malloc (sizeof (*strip) * (strlen (string) + 1));
      if (strip != NULL)
      {
         int i, j;
         int ps = 0;

         for (i = 0, j = 0; string[i]; i++)
         {
            if (string[i] == ' ')
            {
               if (ps == 0)
               {
                  strip[j] = string[i];
                  ps = 1;
                  j++;
               }
            }
            else
            {
               strip[j] = string[i];
               ps = 0;
               j++;
            }
         }
         strip[j] = '\0';
      }
      else
      {
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
   }
   return strip;
}

element* research_element(llist* list, int id){
    element *tmp=list->first;
    // loop of element in list
    while(tmp != NULL){
        if(tmp->id == id){
            // if element found return address 
            return tmp;
        }
        tmp = tmp->nxt;
    }
	element *element = NULL;
    return element;
}

llist* erase_list(llist* list){
    if(list == NULL){
        // If list is null nothing to erase
        return NULL;
    }else{
        // Erase first element and return rest of the list 
        element *tmp = list->first;
        list->first = tmp->nxt;
        free(tmp);
        return erase_list(list);
    }
}

void add_at_the_end(llist* list, int id, rule* rule, char* color){
    // Create new element
    element* newElement = malloc(sizeof(element));
    // add values to the new element 
    newElement->id = id;
    newElement->rule = rule;
    newElement->color = color;	
    newElement->nxt = NULL;
    if(list->first == NULL){
        /* if list is NULL return element */
		list->first = newElement;
    }else{
        /* Otherwise loop through the list and add the element at the end when the last element is null */
		element* tmp=list->first;
        while(tmp->nxt != NULL){
            tmp = tmp->nxt;
        }
        tmp->nxt = newElement;
		
    }
}

void print_list(llist* list){
    element *tmp = list->first;
    /* while not end of the list */
    while(tmp != NULL){
    	printf("test--->\n");
        /* print element  */
		print_rule_fr(tmp);
        /* switch to next element  */
        tmp = tmp->nxt;
    }
}

void print_rule_fr(element *element){
	int cpt = 0;
	char* logicStructFr = "";
	char* logicOperatorFr = "";

	int logicOperatorUse = FALSE;

	//TODO : Jean ajouté la couleur
	
	if(element != NULL){
		printf("\t[-] Règles n°%d \n", element->id);
		printf("\t\t[-] Pour chaque case de type \"%c\" \n", element->rule->charA);
	
		do{
			logicOperatorUse = FALSE;

			logicStructFr = translate_logic_struc(element->rule->logicStructureB[cpt]);
			if(element->rule->logicStructureB[cpt] != OPERATOR_NONE){
				printf("\t\t[-] \tS'il y a \"%s\" \"%d\" caractère(s) de type \"%c\" à \"%d\" de distance \n", logicStructFr, element->rule->numberC[cpt], element->rule->charD[cpt], element->rule->numberE[cpt]);
			}else{
				printf("\t\t[-] \tS'il y a \"%s\" caractère de type \"%c\" à \"%d\" de distance \n", logicStructFr, element->rule->charD[cpt], element->rule->numberE[cpt]);
			}

			if(element->rule->logicOperatorF != EMPTY && cpt < 1)
			{
				logicOperatorFr = translate_logic_operator(element->rule->logicOperatorF);
				printf("\t\t[-] \t\"%s\" \n",logicOperatorFr);
				logicOperatorUse = TRUE;
			}
			cpt++;
		}while(logicOperatorUse && (cpt < 2));

		printf("\t[-] alors la case devient de type \"%c\" \n", element->rule->charG);
	}
}

char* translate_logic_struc(LogicStructure logicStructure){
		switch (logicStructure) {
		case OPERATOR_AT_LEAST :
			return "au moins";
			break;

		case OPERATOR_AT_MOST :
			return "au plus";
			break;

		case OPERATOR_EXACTLY :
			return "exactement";
			break;
		case OPERATOR_NONE :
			return "aucun";
			break;
		default :
			return "";
			break;
		}
}

char* translate_logic_operator(LogicOperator logicOperator){
	switch (logicOperator) {
		case OPERATOR_OR :
			return "ou";
			break;

		case OPERATOR_AND :
			return "et";
			break;

		case EMPTY :
		default :
			return "";
			break;
	}
}