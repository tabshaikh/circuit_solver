<<<<<<< HEAD
CXX = g++

CFLAGS = -std=c++11 -w -fpermissive -lopenblas -llapack 

execute:
	cd src && lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp solver.cpp $(CFLAGS) -o ../a.out
	./a.out $(input)
	firefox -new-tab ./Circuit.html &

debug:
	cd src && lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp -fpermissive -w -std=c++11 -o ../a.out
	./test.sh

clean:
	rm ./a.out ./output.svg
=======
execute: 
	lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp -fpermissive -w -std=c++11
	./a.out top.cir
	firefox ./Circuit.html
>>>>>>> master
