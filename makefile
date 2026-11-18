vm: main.c functions
	gcc main.c -o vm
functions: abrirTexto.c 
			gcc abrirTexto.c abrirTexto.h

run: vm
	./vm
clean: 
	rm -f vm

.PHONY: clean run