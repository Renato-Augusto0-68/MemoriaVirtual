vm: src/main.c src/utils/abrirTexto.c src/utils/abrirTexto.h src/utils/dados.h src/utils/pagina.h
	gcc src/utils/abrirTexto.c src/main.c -o vm


run: vm
	./vm
clean: 
	rm -f vm

.PHONY: clean run