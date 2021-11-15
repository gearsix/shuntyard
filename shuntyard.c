#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

char isop(char c);
int  op_isleft(char c); // associativity (left/right)
int  op_prec(char c);   // precendence

int main(int argc, char *argv[])
{
	size_t len = 0;
	for (int i = 1; i < argc; ++i) {
		if (argv[i])
		len += strlen(argv[i]);
	}
	char *input = calloc(1, len+1);
	for (int i = 1; i < argc; ++i) {
		strcat(input, argv[i]);
	}
	puts(input);

	struct stack *ops = stack_new();
	struct stack *out = stack_new();

	int tok;
	for (size_t i = 0; i < len+1; ++i) {
		tok = input[i];
		if (isop(tok)) {
			while (!stack_isempty(ops)) {
				int assoc = op_isleft(tok);
				int prec = op_prec(tok);
				if ((assoc && prec <= op_prec(stack_peek(ops))) ||
					(!assoc && prec < op_prec(stack_peek(ops)))) {
					stack_push(out, stack_pop(ops));
				} else {
					break;
				}
			}
			stack_push(ops, tok);
		} else if (tok == '(') {
			stack_push(ops, tok);
		} else if (tok == ')') {
			while (stack_peek(ops) != '(')
				stack_push(out, stack_pop(ops));
			stack_pop(ops);
		} else {
			stack_push(out, tok);
		}
	}

	while (!stack_isempty(ops))
		stack_push(out, stack_pop(ops));

	for (int i = 0; i <= out->sp; ++i)
		putchar(out->s[i]);
	puts("");

	return 0;
}

char isop(char c)
{
	char ret = 0;
	switch (c) {
		case '*':
		case '/':
		case '-':
		case '+':
		case '^':
			ret = c;
			break;
	}
	return ret;
}

int op_isleft(char op)
{
	int ret = 0;
	switch (op) {
		case '*':
		case '/':
		case '+':
		case '-':
			ret = 1;
			break;
		case '^':
			break;
	}
	return ret;
}

int op_prec(char op)
{
	int ret = 0;
	switch (op) {
		case '^':
			ret = 4;
			break;
		case '*':
		case '/':
			ret = 3;
			break;
		case '+':
		case '-':
			ret = 2;
			break;
	}
	return ret;
}
