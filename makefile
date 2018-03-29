CXX = g++

CFLAGS = -std=c++11 -w -fpermissive 

execute:
	cd src && lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp -fpermissive -w -std=c++11 -o ../a.out
	./a.out $(input)
	firefox -new-tab ./Circuit.html &

debug:
	cd src && lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp -fpermissive -w -std=c++11 -o ../a.out
	./test.sh

clean:
	rm ./a.out ./output.svg