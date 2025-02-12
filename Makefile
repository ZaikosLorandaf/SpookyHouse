main.exe: main.o init.o display.o
	gcc -o $@ -O2 $^

main.o: main.c headers/init.h headers/display.h headers/coord.h
	gcc -c -o $@ -O2 main.c

init.o: headers/init.h init.c
	gcc -c -o $@ -O2 init.c

display.o: headers/display.h headers/coord.h display.c
	gcc -c -o $@ -O2 display.c

.PHONY: clean

clean:
	rm -rf *.o
