vm: main.c functions/abrirTexto.c functions/abrirTexto.h functions/dados.h
	gcc functions/abrirTexto.c main.c -o vm


run: vm
	./vm
clean: 
	rm -f vm

.PHONY: clean run