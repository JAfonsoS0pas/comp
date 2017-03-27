#!/bin/bash
clear
lex jac.l
yacc -d -v jac.y
clang-3.8 -Wall -Wno-unused-function *.c
valgrind --leak-check=yes ./a.out < Echo.ja -t