#include <stdlib.h>
#include <stdio.h>


struct stack{
	int top;
	int size;
	int* array;
};
typedef struct stack stack;

struct stack* create_stack(int size){
	struct stack* st = (struct stack*) malloc(sizeof(struct stack));
	st->size = size;
	st->top = -1;
	st->array = (int*)malloc(st->size * sizeof(int));
	return st;
}

int isFull(struct stack* st){
	return st->top == st->size -1;
}

int isEmpty(struct stack* st){
	return st->top == -1;
}

void push(struct stack* st, int element){
	if(isFull(st)){
		return;
	}
	st->array[++st->top] = element;
	printf("%d pushed !\n", element);
}

int pop(struct stack* st){
	if (isEmpty(st)){
		return -1;
	}
	return st->array[st->top--];
}


int evaluate(int* expression, int size,  int numberOperands){
	struct stack* st = create_stack(size);

	for (int i = 0; i < size; ++i){
		if(i <= (numberOperands - 1)){
			push(st,expression[i]);
		}else{
			//if it's an operator
			int operand1 = pop(st);
			int operand2 = pop(st);
			printf("op1=%d,  op2=%d\n", operand1,operand2);

			// 1 = ET  0 = OU
			if(expression[i] == 1){
				push(st,(operand2 && operand1));
			}else if (expression[i] == 0){
				push(st,(operand2 || operand1));
			}
		}
	}
	return pop(st);
}

int main(int argc, char const *argv[]){
    
    int expresion[7] = {1,0,1,0,0,0,1};
    printf("Le résultat est : %d\n",evaluate(expresion,7,4));
	return 0;
}
