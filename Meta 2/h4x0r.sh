#!/bin/bash
clear
lex jac.l
yacc -d -v jac.y
clang-3.8 -g -Wall -Wno-unused-function *.c
zip jac.zip jac.l jac.y arvo.h arvo.c 
./a.out < Echo.ja -t