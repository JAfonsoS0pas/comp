#!/bin/bash
clear
lex jac.l
yacc -d jac.y
cc -o y.tab.c lex.yy.c