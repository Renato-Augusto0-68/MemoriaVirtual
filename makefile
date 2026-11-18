vm: main.c src/abrirTexto.c src/abrirTexto.h src/dados.h src/pagina.h
	gcc src/abrirTexto.c main.c -o vm


run: vm
	./vm
clean: 
	rm -f vm

.PHONY: clean run