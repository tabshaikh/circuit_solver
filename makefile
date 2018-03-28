execute: 
			cd src && lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp -fpermissive -w -std=c++11
			./a.out $(input)
			firefox ./Circuit.html