execute: 
	lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp -fpermissive -w -std=c++11
	./a.out top.cir
	firefox ./Circuit.html
