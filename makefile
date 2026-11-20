vm: src/main.c src/utils/abrirTexto.c src/utils/abrirTexto.h src/utils/dados.h src/utils/pagina.h src/utils/ram.h src/utils/alocar.c src/utils/alocar.h src/utils/tlb.h src/utils/tlbThread.h
	gcc src/utils/alocar.c src/utils/abrirTexto.c src/main.c -o vm

run: vm
	./vm
clean: 
	rm -f vm teste.txt

.PHONY: clean run