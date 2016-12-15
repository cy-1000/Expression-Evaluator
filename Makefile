CC=gcc

stack_program: stack.o stack_program.o
	"${CC}" -g stack.c stack_program.c

eval: stack.o evaluator.o
	"${CC}" -g evaluator.c stack.c
