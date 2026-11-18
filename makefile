vm: main.c
	gcc main.c -o vm

run: vm
	./vm
clean: 
	rm -f vm

.PHONY: clean run