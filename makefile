execute: 
			g++ lex.yy.c y.tab.c main.cpp display.cpp -fpermissive -w -std=c++11
			./a.out
			firefox ./Circuit.html