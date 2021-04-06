
all: concordo

bin/canal.o: src/canal.cpp
	g++ -Ilib -o bin/canal.o src/canal.cpp -c -Wall -ansi -pedantic -O0 -std=c++11 -g

bin/mensagem.o: src/mensagem.cpp bin/canal.o
	g++ -Ilib -o bin/mensagem.o src/mensagem.cpp -c -Wall -ansi -pedantic -O0 -std=c++11 -g

bin/servidor.o: src/servidor.cpp bin/mensagem.o bin/canal.o
	g++ -Ilib -o bin/servidor.o src/servidor.cpp -c -Wall -ansi -pedantic -O0 -std=c++11 -g

bin/sistema.o: src/sistema.cpp bin/servidor.o bin/mensagem.o bin/canal.o
	g++ -Ilib -o bin/sistema.o src/sistema.cpp -c -Wall -ansi -pedantic -O0 -std=c++11 -g	

bin/usuario.o: src/usuario.cpp bin/sistema.o bin/servidor.o bin/mensagem.o bin/canal.o
	g++ -Ilib -o bin/usuario.o src/usuario.cpp -c -Wall -ansi -pedantic -O0 -std=c++11 -g	

bin/main.o: src/main.cpp bin/usuario.o bin/sistema.o bin/servidor.o bin/mensagem.o bin/canal.o
	g++ -Ilib -o bin/main.o src/main.cpp -c -Wall -ansi -pedantic -O0 -std=c++11 -g

concordo: bin/main.o bin/usuario.o bin/sistema.o bin/servidor.o bin/mensagem.o bin/canal.o 
	g++ bin/*.o -Ilib -o concordo -Wall -ansi -pedantic -O0 -std=c++11 -g  

clean:
	rm -rf *.o *~ concordo