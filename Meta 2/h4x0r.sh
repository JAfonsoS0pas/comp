#!/bin/bash
clear
lex jac.l
yacc -d -v jac.y
cc -O0 -g -Wall -Wno-unused-function y.tab.c lex.yy.c
valgrind --leak-check=yes ./a.out < Echo.ja -t