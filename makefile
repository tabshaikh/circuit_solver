CXX = g++

CFLAGS = -std=c++11 -w -fpermissive -lopenblas -llapack 

execute:
	mkdir click
	cd src && lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp solver.cpp $(CFLAGS) -o ../a.out
	./a.out $(input)
	firefox -new-tab ./Circuit.html &

debug:
	cd src && lex lex.l && yacc -d parser.y && g++ lex.yy.c y.tab.c main.cpp display.cpp solver.cpp $(CFLAGS) -o ../a.out	
	./test.sh

clean:
	rm -r ./a.out ./output.svg ./result.txt ./click