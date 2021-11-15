#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

struct stack {
	char *s;
	int sp, siz;
};

struct stack *stack_new();

int  stack_isempty(struct stack *s);

int  stack_isfull(struct stack *s);

int  stack_peek(struct stack *s);

void stack_push(struct stack *s, int item);

int  stack_pop(struct stack *s);

#endif
