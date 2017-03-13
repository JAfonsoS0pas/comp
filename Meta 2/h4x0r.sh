clear
lex jac.l 
yacc -d jac.y 
cc -o jac y.tab.c lex.yy.c
clang -Wall -Wno-unused-function *.c
./a.out