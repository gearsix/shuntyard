#include "stack.h"

struct stack *stack_new()
{
	const size_t siz = 1024;

	struct stack *s = malloc(sizeof(struct stack *));
	s->s = malloc(siz);
	s->sp = -1;
	s->siz = siz;

	return s;
}

int stack_isempty(struct stack *s)
{
	return (s->sp == -1);
}

int stack_isfull(struct stack *s)
{
	return (s->sp == s->siz);
}

int stack_peek(struct stack *s)
{
	if (!stack_isempty(s))
		return s->s[s->sp];
	return 0;
}

void stack_push(struct stack *s, int item)
{
	if (!stack_isfull(s))
		s->s[++s->sp] = item;
}

int stack_pop(struct stack *s)
{
	if (!stack_isempty(s))
		return s->s[s->sp--];
	return 0;
}
